
#include <stdio.h>
#include <iostream>
#include <opencv2/core.hpp>
#include "opencv2/opencv.hpp"
#include "opencv2/calib3d.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/xfeatures2d.hpp>
using namespace std;
using namespace cv;

int main(int argc, char** argv) {
	if (argc != 2) {
		cout << "less than 1 argument!" << endl;
		return -1;
	}
	Mat img_object = imread(argv[1], IMREAD_COLOR);
	Mat img_gray;
	cvtColor(img_object, img_gray, COLOR_BGR2GRAY);
	//FAST Keypoint implementation for extraction
	Ptr<FastFeatureDetector> detector = FastFeatureDetector::create(50, true);
	// Compute keypoints and descriptor from the source image in advance
	vector<KeyPoint> keypoints2;
	Mat descriptors2;
	// detecting and computing keypoints and descriptors
	detector->detect(img_gray, keypoints2);
	printf(" ==> original image:%d keypoints are found.\n", (int)keypoints2.size());
	for (int i = 0; i < keypoints2.size(); i++) {
		KeyPoint kp = keypoints2[i];
		circle(img_object, kp.pt, cvRound(kp.size * 0.25), Scalar(255, 255, 0), 1, 8, 0);
	}
	namedWindow("FAST Keypoints");
	imshow("FAST Keypoints", img_object);
	waitKey(0);
	return 0;
}