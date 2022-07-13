#include "opencv2/opencv.hpp"

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <stdint.h>
#include <math.h>

using namespace std;
using namespace cv;


int main(int argv, char** argc) {

	VideoCapture cap1("outcpp1.avi");
	VideoCapture cap2("outcpp2.avi");

	while (1) {
		Mat frame1, gray1, frame2, gray2, dst;

		cap1 >> frame1;
		cap2 >> frame2;

		// If the frame is empty, break immediately
		if (frame1.empty())
			break;
		if (frame2.empty())
			break;

		cvtColor(frame1, gray1, CV_BGR2GRAY);
		cvtColor(frame2, gray2, CV_BGR2GRAY);

		compare(gray1, gray2, dst, cv::CMP_EQ);

		int threshold = (double)(frame1.rows * frame1.cols) * 0.7;

		int percentage = countNonZero(dst);

		if (percentage <  threshold)
			cout << percentage << endl;
	}

	return 0;
}
