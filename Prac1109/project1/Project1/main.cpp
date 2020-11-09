#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include <string>

using namespace cv;
using namespace std;

int main(int argc, char** argv){
	Mat image;
	image = imread(argv[1], 0);
	if (!image.data)
		return 0;
	namedWindow("Binary Image");
	imshow("Binary Image", image);
	// Get the contours of the connected components
	vector<std::vector<cv::Point>> contours;
	findContours(image,	contours, RETR_EXTERNAL,CHAIN_APPROX_NONE); // retrieve all pixels of each

	Mat result(image.size(), CV_8U, cv::Scalar(255));
	drawContours(result, contours, -1, Scalar(0), 2); // with a thickness of 2
	cv::namedWindow("Contours");
	cv::imshow("Contours", result);
	// Eliminate too short or too long contours
	int cmin = 100; // minimum contour length
	int cmax = 1000; // maximum contour length

	vector<vector<Point>>::const_iterator itc = contours.begin();
	while (itc != contours.end() - 1) {
		if (itc->size() - 1 < cmin || itc->size() - 1 > cmax)
			itc = contours.erase(itc);
		else
			++itc;
	}
	// draw contours on the original image
	Mat original = cv::imread(argv[2], 1);
	drawContours(original, contours,-1,Scalar(255, 255, 255), 2); // with a thickness of 2
	cv::namedWindow("Contours on Animals");
	cv::imshow("Contours on Animals", original);

//<< 새로운 descriptor 삽입 >> (다음 ppt)
	cout << " Step-2) Press any key to detect shape descriptor...!! " << endl;
	waitKey(0);
	
	image = imread(argv[3], 0);
	// testing the bounding box
	Rect r0 = cv::boundingRect(cv::Mat(contours[0]));
	rectangle(result, r0, cv::Scalar(0), 2);
	// testing the enclosing circle
	float radius;
	Point2f center;
	minEnclosingCircle(cv::Mat(contours[1]), center, radius);
	circle(result, cv::Point(center), static_cast<int>(radius), cv::Scalar(0), 2);
	// testing the approximate polygon
	vector<cv::Point> poly;
	approxPolyDP(cv::Mat(contours[2]), poly, 5, true);
	cout << "Polygon size: " << poly.size() << std::endl;
	// Iterate over each segment and draw it
	vector<cv::Point>::const_iterator itp = poly.begin();
	while (itp != (poly.end() - 1)) {
		cv::line(result, *itp, *(itp + 1), cv::Scalar(0), 2);
		++itp;
	}
	// last point linked to first point
	cv::line(result, *(poly.begin()), *(poly.end() - 1), cv::Scalar(20), 2);
		
	// testing the convex hull
	std::vector<cv::Point> hull;
	cv::convexHull(cv::Mat(contours[3]), hull);
	// Iterate over each segment and draw it
	std::vector<cv::Point>::const_iterator it = hull.begin();
	while (it != (hull.end() - 1)) {
		cv::line(result, *it, *(it + 1), cv::Scalar(0), 2);
		++it;
	}
	// last point linked to first point
	cv::line(result, *(hull.begin()), *(hull.end() - 1), cv::Scalar(20), 2);
	// 스타트 포인트랑 엔드 포인트를 잇기 위해 마지막에 line을 해준다.

	itc = contours.begin();
	while (itc != contours.end()) {
		// compute all moments
		cv::Moments mom = cv::moments(cv::Mat(*itc++));
		// draw mass center
		circle(result,Point(mom.m10 / mom.m00, mom.m01 / mom.m00),
			2, Scalar(0), 2); // draw black dot
	}
	namedWindow("Some Shape descriptors");
	imshow("Some Shape descriptors", result);
	waitKey(0);
	return 0;
}