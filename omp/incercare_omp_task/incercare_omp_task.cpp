#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <fstream>
#include <vector>
#include <omp.h>
#include <chrono>

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*----Definirea Constantelor----*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#define DIM 1024
#define PI 3.1415926535897932f
#define T_MAX 1.0f
#define T_MIN 0.0001f
#define CONDUCTIVITY 4

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

using namespace std;
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*----Prototipuri de functii----*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void copy_values_from_previous_step(float* in, float* ct);
void update_values(float* out, float* in);
unsigned char value(float n1, float n2, int hue);
void float_to_color(vector<uint8_t>& ptr_out, float* out);
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


#pragma pack(push,1)
struct BMPFileHeader {
	uint16_t file_type{ 0x4D42 };          // BMP file always have first 2 bytes 4D42
	uint32_t file_size{ 0 };               // Size of the file (in bytes)
	uint16_t reserved1{ 0 };
	uint16_t reserved2{ 0 };
	uint32_t offset_data{ 0 };             // Start position of pixel data
};
struct BMPInfoHeader {
	uint32_t size{ 0 };                      // Size of BMP Info Header
	int32_t width{ 0 };                      // width of bitmap in pixels
	int32_t height{ 0 };                     // width of bitmap in pixels
	//       (if positive, bottom-up, with origin in lower left corner)
	//       (if negative, top-down, with origin in upper left corner)
	uint16_t planes{ 1 };                    // No. of planes for the target device, this is always 1
	uint16_t bit_count{ 0 };                 // No. of bits per pixel
	uint32_t compression{ 0 };               // 0 or 3 - uncompressed. THIS PROGRAM CONSIDERS ONLY UNCOMPRESSED BMP images
	uint32_t size_image{ 0 };                // 0 - for uncompressed images
	int32_t x_pixels_per_meter{ 0 };
	int32_t y_pixels_per_meter{ 0 };
	uint32_t colors_used{ 0 };               // No. color indexes in the color table. Use 0 for the max number of colors allowed by bit_count
	uint32_t colors_important{ 0 };          // No. of colors used for displaying the bitmap. If 0 all colors are required
};
struct BMPColorHeader {
	uint32_t red_mask{ 0x00ff0000 };         // Bit mask for the red channel
	uint32_t green_mask{ 0x0000ff00 };       // Bit mask for the green channel
	uint32_t blue_mask{ 0x000000ff };        // Bit mask for the blue channel
	uint32_t alpha_mask{ 0xff000000 };       // Bit mask for the alpha channel
	uint32_t color_space_type{ 0x73524742 }; // Default "sRGB" (0x73524742)
	uint32_t unused[16]{ 0 };                // Unused data for sRGB color space
};
#pragma pack(pop)


struct BMP
{
	// Header imagine BMP
	BMPFileHeader  file_header;
	BMPInfoHeader  bmp_info_header;
	BMPColorHeader bmp_color_header;

	//Image dimensions
	int h;  //Input image height
	int w;  //Input image weight
	int ch; //Input image number of channels

	//Image data
	vector<uint8_t> data;

	void readBMP(const char* filename)
	{
		//Read BMP file
		ifstream inp{ filename, ios_base::binary };

		//Check if BMP file exist
		check(inp);

		//Look for start pixel
		inp.seekg(file_header.offset_data, inp.beg);

		//Make output header
		prepare_output_header(inp);

		//Get image dimensions
		ch = bmp_info_header.bit_count / 8;
		h = bmp_info_header.height;
		w = bmp_info_header.width;

		//Prepare vector for load data
		data.resize(w * h * ch);

		//Row padding and load data
		load_data(inp);
	}

	void writeBMP(const char* fname)
	{
		ofstream of{ fname, ios_base::binary };
		if (of) {
			if (bmp_info_header.bit_count == 32)
			{
				write_headers_and_data(of);
			}
			else if (bmp_info_header.bit_count == 24)
			{
				if (bmp_info_header.width % 4 == 0)
				{
					write_headers_and_data(of);
				}
				else {
					uint32_t new_stride = row_stride;
					vector<uint8_t> padding_row(new_stride - row_stride);

					write_headers(of);
					int y, i;
					for (y = 0; y < bmp_info_header.height; ++y)
					{
						of.write((const char*)(data.data() + row_stride * y), row_stride);
						of.write((const char*)padding_row.data(), padding_row.size());
					}
				}
			}
			else
			{
				throw runtime_error("! (T-T) ! ERROR ! Programul nu poate deschide si salva imagini BMP 24 sau BMP 32");
			}
		}
		else
			throw runtime_error("! (T-T) ! ERROR ! Imaginea nu a putut fi salvata");
	}

private:
	uint32_t row_stride{ 0 };

	void check(ifstream& inp) {
		if (inp) {
			inp.read((char*)&file_header, sizeof(file_header));
			//Check if image is BMP
			if (file_header.file_type != 0x4D42) {
				throw runtime_error("! (T-T) ! ERROR ! This is not a BMP image!");
			}
			inp.read((char*)&bmp_info_header, sizeof(bmp_info_header));

			if (bmp_info_header.bit_count == 32) {
				// Check if image has info about RGB mask
				if (bmp_info_header.size >= (sizeof(BMPInfoHeader) + sizeof(BMPColorHeader))) {
					inp.read((char*)&bmp_color_header, sizeof(bmp_color_header));
					// Check if RGB space is RGBA
					BMPColorHeader expected_color_header;
					if (expected_color_header.red_mask != bmp_color_header.red_mask ||
						expected_color_header.blue_mask != bmp_color_header.blue_mask ||
						expected_color_header.green_mask != bmp_color_header.green_mask ||
						expected_color_header.alpha_mask != bmp_color_header.alpha_mask) {
						throw runtime_error("! (T-T) ! ERROR ! RGB space is not RGBA!");
					}
				}
				else {
					throw runtime_error("! (T-T) ! ERROR ! Image has no info about RGB!");
				}
			}
		}
		else
			throw runtime_error("! (T-T) ! ERROR ! Image could not be open!");
	};

	void prepare_output_header(ifstream& inp) {
		if (bmp_info_header.bit_count == 32) {
			bmp_info_header.size = sizeof(BMPInfoHeader) + sizeof(BMPColorHeader);
			file_header.offset_data = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + sizeof(BMPColorHeader);
		}
		else {
			bmp_info_header.size = sizeof(BMPInfoHeader);
			file_header.offset_data = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader);
		}
		file_header.file_size = file_header.offset_data;
	}

	void load_data(ifstream& inp)
	{
		if (bmp_info_header.width % 4 == 0)
		{
			inp.read((char*)data.data(), data.size());
			file_header.file_size += static_cast<uint32_t>(data.size());
		}
		else
		{
			row_stride = bmp_info_header.width * bmp_info_header.bit_count / 8;
			uint32_t new_stride = row_stride;
			vector<uint8_t> padding_row(new_stride - row_stride);
#pragma omp parallel for
			for (int y = 0; y < bmp_info_header.height; ++y)
			{
				inp.read((char*)(data.data() + row_stride * y), row_stride);
				inp.read((char*)padding_row.data(), padding_row.size());
			}
			file_header.file_size += static_cast<uint32_t>(data.size()) + bmp_info_header.height * static_cast<uint32_t>(padding_row.size());
		}
	}

	void write_headers(ofstream& of)
	{
		of.write((const char*)&file_header, sizeof(file_header));
		of.write((const char*)&bmp_info_header, sizeof(bmp_info_header));
		if (bmp_info_header.bit_count == 32)
			of.write((const char*)&bmp_color_header, sizeof(bmp_color_header));

	}

	void write_headers_and_data(ofstream& of)
	{
		write_headers(of);
		of.write((const char*)data.data(), data.size());
	}
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*----Buffere pentru imagini si frame-uri----*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
float* picture_in;
float* picture_out;
float* picture_ct;
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

std::chrono::time_point<std::chrono::system_clock> start;
std::chrono::time_point<std::chrono::system_clock> finish;
std::chrono::duration<double> elapsed_seconds;


int main(int argv, char** argc) {

	//Citeste imaginea pentru simulare
	BMP bmp;
	BMP out;

	start = std::chrono::system_clock::now();
	bmp.readBMP("mems.bmp");

	bmp.readBMP("mems.bmp");

	//Aloca spatiu pentru bufere
	picture_in = (float*)malloc(DIM * DIM * sizeof(float));
	picture_out = (float*)malloc(DIM * DIM * sizeof(float));
	picture_ct = (float*)malloc(DIM * DIM * sizeof(float));

	//Citeste valorile din imagine
	int i, j;
#pragma omp parallel for private(i,j)
	for (i = 0; i < DIM; i++) {
		for (j = 0; j < DIM; j++) {
			picture_ct[DIM * i + j] = picture_in[DIM * i + j] = (bmp.data[3 * (DIM * i + j)] == 0) ? T_MAX : T_MIN;
		}
	}

	bool out_pic = true;
	int frame = 0;
	char str[20];

	for (int i = 0; i < 100; i++) {

		for (int j = 0; j < CONDUCTIVITY; j++) {
			if (out_pic) {
#pragma omp task shared (picture_in)
				copy_values_from_previous_step(picture_in, picture_ct);
#pragma omp task shared (picture_out)
				update_values(picture_out, picture_in);
			}
			else {
#pragma omp task shared (picture_out)
				copy_values_from_previous_step(picture_out, picture_ct);
#pragma omp task shared (picture_in)
				update_values(picture_in, picture_out);
			}
#pragma omp taskwait
			out_pic = !out_pic;
		}
#pragma omp taskwait

#pragma omp task depend(in:picture_out)
		float_to_color(bmp.data, picture_out);
#pragma omp task depend(in:bmp.data)
		bmp.writeBMP("Final.bmp");
	}

	finish = std::chrono::system_clock::now();
	elapsed_seconds = finish - start;
	cout << "Time: " << elapsed_seconds.count() << " seconds." << endl;

	//Elibereaza spatiul utilizat
	free(picture_in);
	free(picture_out);
	free(picture_ct);

	return 0;
}


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*----Copiaza temperatura de la pasul anterior----*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void copy_values_from_previous_step(float* in, float* ct) {
	int i;
	for (i = 0; i < DIM * DIM; i++) {
		if (ct[i] != T_MIN)
			in[i] = ct[i];
	}
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*----Calculeaza temperatura----*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void update_values(float* out, float* in) {
	long long left, right, top, bottom;

	for (long long i = 0; i < DIM * DIM; i++) {

		left = (i % DIM == 0) ? i : i - 1;
		right = (i % DIM == DIM - 1) ? i : i + 1;
		top = (i < DIM) ? i : i - DIM;
		bottom = (i >= DIM * (DIM - 1)) ? i : i + DIM;

		out[i] = in[i] + 0.1 * (in[top] + in[left] + in[right] + in[bottom] - in[i] * 4);
	}
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*---- Conversie HSL -> RGB ----*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
unsigned char value(float n1, float n2, int hue)
{
	hue = (hue > 360) ? (hue - 360) : ((hue < 0) ? hue + 360 : hue);

	if (hue < 60)
		return (unsigned char)(255 * (n1 + (n2 - n1) * hue / 60));
	if (hue < 180)
		return (unsigned char)(255 * n2);
	if (hue < 240)
		return (unsigned char)(255 * (n1 + (n2 - n1) * (240 - hue) / 60));

	return (unsigned char)(255 * n1);
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*----Converteste valorile din float -> HSL -> RGB ----*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void float_to_color(vector<uint8_t>& ptr_out, float* out)
{
	// Find pixel position
	int i, j;
	for (i = 0; i < DIM; i++)
		for (j = 0; j < DIM; j++) {
			int pos = DIM * i + j;
			float lightness = out[pos];
			float saturation = 1;
			int   hue = (180 + (int)(360.0f * lightness)) % 360;
			float m1, m2;

			m2 = (lightness <= 0.5f) ? lightness * (1 + saturation) : lightness + saturation - lightness * saturation;
			m1 = 2 * lightness - m2;

			ptr_out[3 * pos + 2] = value(m1, m2, hue + 120);
			ptr_out[3 * pos + 1] = value(m1, m2, hue);
			ptr_out[3 * pos] = value(m1, m2, hue - 120);
		}
}
/*********************************************************************/