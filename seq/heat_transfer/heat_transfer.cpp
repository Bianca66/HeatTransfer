#include "opencv2/opencv.hpp"

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <stdint.h>
#include <math.h>

using namespace std;
using namespace cv;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*----Definirea Constantelor----*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#define DIM 1024
#define PI 3.1415926535897932f
#define T_MAX 1.0f
#define T_MIN 0.0001f
#define CONDUCTIVITY 4
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*----Prototipuri de functii----*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void update_values(float* out, float* in);
unsigned char value(float n1, float n2, int hue);
void float_to_color(Mat ptr_out, float* out);
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*----Buffere pentru imagini si frame-uri----*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
cv::Mat pix, pix_out;
float* picture_in;
float* picture_out;
float* picture_ct;
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


int main(int argv, char** argc) {

	//Citeste imaginea pentru simulare
	pix = cv::imread("mems.bmp", 1);
	pix_out = pix;

	//Verific[ dac[ imaginea a putut fi deschisa 
	if (pix.empty())
		std::cout << "Fail to open!" << std::endl;
	else
		std::cout << "Image opened fine!" << std::endl;

	//Aloca spatiu pentru bufere
	picture_in = (float*)malloc(DIM*DIM * sizeof(float));
	picture_out = (float*)malloc(DIM*DIM * sizeof(float));
	picture_ct = (float*)malloc(DIM*DIM * sizeof(float));

	//Citeste valorile din imagine
	for (int i = 0; i < DIM; i++) {
		for (int j = 0; j < DIM; j++) {
			picture_in[DIM * i + j] = (pix.at<cv::Vec3b>(i, j)[0] == 0) ? T_MAX : T_MIN;
		}
	}

	//Creeaza filmuletul
	VideoWriter video("outcpp.avi", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 10, Size(DIM, DIM));

	for (int i = 0; i < 100; i++) {
		for (int i = 0; i < CONDUCTIVITY; i++) {
			update_values(picture_out, picture_in);
			swap(picture_in, picture_out);
		}
		float_to_color(pix_out, picture_out);
		video.write(pix_out);
	}
	video.release();

	//Elibereaza spatiul utilizat
	free(picture_in);
	free(picture_out);
	free(picture_ct);

	destroyAllWindows();
	return 0;
}


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*----Calculeaza temperatura----*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void update_values(float* out, float* in){
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
void float_to_color(Mat ptr_out, float* out)
{
	// Find pixel position
	for (int i = 0; i < DIM; i++)
		for (int j = 0; j < DIM; j++) {
			float lightness = out[DIM * i + j];
			float saturation = 1;
			int   hue = (180 + (int)(360.0f * lightness)) % 360;
			float m1, m2;

			m2 = (lightness <= 0.5f) ? lightness * (1 + saturation) : lightness + saturation - lightness * saturation;
			m1 = 2 * lightness - m2;

			ptr_out.at<cv::Vec3b>(i, j)[2] = value(m1, m2, hue + 120);
			ptr_out.at<cv::Vec3b>(i, j)[1] = value(m1, m2, hue);
			ptr_out.at<cv::Vec3b>(i, j)[0] = value(m1, m2, hue - 120);
		}
}
/********************************************************************************/