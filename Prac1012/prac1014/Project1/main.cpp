#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/ximgproc.hpp"
#include <iostream>
#include <stdio.h>
using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	//--OpenCV 2.x ±¸Çö --//
	Mat src, dst, tmp;
	char window_name[20] = "Pyramids Demo";
	//image = imread("Desert.bmp", IMREAD_COLOR); // Read the file
	src = imread(argv[1]); // Read the file
	/// Threshold the input image
	Mat img_grayscale, img_binary;
	cvtColor(src, img_grayscale, COLOR_BGR2GRAY);
	threshold(img_grayscale, img_binary, 0, 255, THRESH_OTSU | THRESH_BINARY);

	namedWindow("binary");
	imshow("binary", img_binary);


	/// Apply thinning to get a skeleton
	Mat img_thinning_ZS, img_thinning_GH;
	ximgproc::thinning(img_binary, img_thinning_ZS, ximgproc::THINNING_ZHANGSUEN);
	ximgproc::thinning(img_binary, img_thinning_GH, ximgproc::THINNING_GUOHALL);
	/// Make 3 channel images from thinning result
	Mat result_ZS(src.rows, src.cols, CV_8UC3), result_GH(src.rows, src.cols, CV_8UC3);
	Mat in[] = { img_thinning_ZS, img_thinning_ZS, img_thinning_ZS };
	Mat in2[] = { img_thinning_GH, img_thinning_GH, img_thinning_GH };
	int from_to[] = { 0,0, 1,1, 2,2 };
	mixChannels(in, 3, &result_ZS, 1, from_to, 3);
	mixChannels(in2, 3, &result_GH, 1, from_to, 3);
	/// Combine everything into a canvas
	Mat canvas(src.rows, src.cols * 3, CV_8UC3);
	src.copyTo(canvas(Rect(0, 0, src.cols, src.rows)));
	result_ZS.copyTo(canvas(Rect(src.cols, 0, src.cols, src.rows)));
	result_GH.copyTo(canvas(Rect(src.cols * 2, 0, src.cols, src.rows)));
	/// Visualize result

	namedWindow("skeleton");
	imshow("Skeleton", canvas); waitKey(0);
	return 0;
}