#include "opencv2/opencv.hpp"

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <stdint.h>
#include <math.h>
#include <chrono>
#include<omp.h>

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
#define CHUNK 1
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*----Prototipuri de functii----*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void copy_values_from_previous_step(float* in, float* ct);
void update_values(float* out, float* in);
unsigned char value(float n1, float n2, int hue);
void float_to_color(Mat ptr_out, float* out);
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


std::chrono::time_point<std::chrono::system_clock> start; 
std::chrono::time_point<std::chrono::system_clock> finish;
std::chrono::duration<double> elapsed_seconds;


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

	start = std::chrono::system_clock::now();

	pix_out = pix;

	//Verifica daca imaginea a putut fi deschisa 
	if (pix.empty())
		std::cout << "Fail to open!" << std::endl;
	else
		std::cout << "Image opened fine!" << std::endl;

	//Aloca spatiu pentru bufere
	picture_in = (float*)malloc(DIM * DIM * sizeof(float));
	picture_out = (float*)malloc(DIM * DIM * sizeof(float));
	picture_ct = (float*)malloc(DIM * DIM * sizeof(float));

	//Citeste valorile din imagine
	int i, j;
#pragma omp parallel for schedule(dynamic,CHUNK) private(i,j)
	for (i = 0; i < DIM; i++) {
		for (j = 0; j < DIM; j++) {
			picture_ct[DIM * i + j] = picture_in[DIM * i + j] = (pix.at<cv::Vec3b>(i, j)[0] == 0) ? T_MAX : T_MIN;
		}
	}

	//Creeaza filmuletul
	VideoWriter video("outcpp.avi", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 10, Size(DIM, DIM));

	bool out_pic = true;
	for (int i = 0; i < 1000; i++) {
		for (int i = 0; i < CONDUCTIVITY; i++) {
			if (out_pic) {
				copy_values_from_previous_step(picture_in, picture_ct);
				update_values(picture_out, picture_in);
			}
			else {
				copy_values_from_previous_step(picture_out, picture_ct);
				update_values(picture_in, picture_out);
			}
			out_pic = !out_pic;
		}
		float_to_color(pix_out, picture_out);
		video.write(pix_out);
	}
	video.release();

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
#pragma omp parallel for schedule(dynamic,CHUNK)
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

#pragma omp parallel 
	for (long long i = omp_get_thread_num() * DIM * DIM / omp_get_num_threads(); i < omp_get_thread_num() * DIM * DIM / omp_get_num_threads() + DIM * DIM / omp_get_num_threads(); ++i) {
		long long left = (i % DIM == 0) ? i : i - 1;
		long long right = (i % DIM == DIM - 1) ? i : i + 1;
		long long top = (i < DIM) ? i : i - DIM;
		long long bottom = (i >= DIM * (DIM - 1)) ? i : i + DIM;
		out[i] = in[i] + 0.1f * (in[top] + in[left] + in[right] + in[bottom] - in[i] * 4);
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
	int i, j;
#pragma omp parallel for schedule(dynamic,CHUNK) private(i,j)
	for (i = 0; i < DIM; i++)
		for (j = 0; j < DIM; j++) {
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
