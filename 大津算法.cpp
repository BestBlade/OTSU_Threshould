#include <iostream>
#include<opencv2/core/core.hpp>  
#include<opencv2/highgui/highgui.hpp>  
#include"opencv2/imgproc/imgproc.hpp"
#include <stdio.h>
#include <math.h>																				/*	exp()函数	*/
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int myOtsu(Mat img) {
	if (img.channels() != 1) {
		cerr<<"please input the gray picture"<<endl;
	}

	float pixel_porb[256] = { 0 };
	for (int x = 0; x < img.rows; x++) {
		for (int y = 0; y < img.cols; y++) {
			pixel_porb[img.at<uchar>(x, y)]++;
		}
	}
	for (int i = 0; i < 256; i++) {
		pixel_porb[i] /= img.rows * img.cols;
	}

	float gmax = 0;
	int threshould = 0;
	for (int i = 0; i < 256; i++) {
		float w0 = 0;
		float w1 = 0;
		float u0 = 0;
		float u1 = 0;
		for (int j = 0; j < 256; j++) {
			if (i <= j) {								
				w0 += pixel_porb[j];
				u0 += j * pixel_porb[j];
			}
			else {
				w1 += pixel_porb[j];
				u1 += j * pixel_porb[j];
			}
		}
		//平均灰度
		float u = u0 + u1;
		u0 /= w0;
		u1 /= w1;
		float g = w0 * pow((u - u0), 2) + w1 * pow((u - u1), 2);
		if (g > gmax) {
			gmax = g;
			threshould = i;
		}
	}
	return threshould;
}

Mat mythreshould(Mat img, int threshould) {
	if (img.channels() != 1) {
		cerr << "please input the gray picture" << endl;
	}

	Mat bw(img.rows, img.cols, img.type());
	for (int x = 0; x < img.rows; x++) {
		for (int y = 0; y < img.cols; y++) {
			if (img.at<uchar>(x, y) <= threshould) {
				bw.at<uchar>(x, y) = 0;
			}
			else {
				bw.at<uchar>(x, y) = 255;
			}
		}
	}
	return bw;
}



int main() {
	Mat img = imread("C://Users//Chrysanthemum//Desktop//1.PNG",0);

	int threshould = myOtsu(img);

	Mat res = mythreshould(img, threshould);

	Mat dst;
	threshold(img, dst, 0, 255, THRESH_OTSU);

	imshow("原图", img);
	imshow("结果图", res);
	imshow("OPENCV结果图", dst);

	waitKey(0);
}