#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include <string>

using namespace cv;
using namespace std;


int main(int argc, char** argv) {
	Mat image = imread(argv[1], 0);
	if (!image.data){
		cout<< "no image" <<endl;
		return -1;
	}

	namedWindow("binary");
	imshow("binary", image);

	vector<vector<Point>> contours;
	findContours(image, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);

	Mat result(image.size(), CV_8U, Scalar(255));
	drawContours(result, contours, -1, Scalar(0), 2);

	namedWindow("contours");
	imshow("contours", result);


	Mat original = imread(argv[1], 1);
	drawContours(original, contours, -1, Scalar(255, 255, 255), 2);

	namedWindow("contours on animals");
	imshow("contours on animals", original);

	waitKey(0);
	return 0;
}

//Á¦´ë·Î ¾ÈµÊ..!