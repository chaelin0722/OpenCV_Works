#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include <string>

using namespace cv;
using namespace std;
//practice.exe ../../../../images/binaryGroup.bmp ../../../../images/group.jpg ../../../../images/group.jpg 
// ���� �����̹��� ���� argv ���� �޾ƾ� ��

int main(int argc, char** argv){
	Mat image;
	image = imread(argv[1], 0);
	if (!image.data)
		return 0;
	namedWindow("Binary Image");
	imshow("Binary Image", image);
	// Get the contours of the connected components
	vector<vector<Point>> contours;
	findContours(image,	contours, RETR_EXTERNAL,CHAIN_APPROX_NONE); //������ ����

	Mat result(image.size(), CV_8U, Scalar(255));
	drawContours(result, contours, -1, Scalar(0), 2); // with a thickness of 2 ������ ����Ȱ� �׸���

	namedWindow("Contours");
	imshow("Contours", result);
	
	//min max �����ؼ� �����
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
	Mat original = imread(argv[2], 1);
	drawContours(original, contours,-1,Scalar(255, 255, 255), 2); // with a thickness of 2
	namedWindow("Contours on Animals");
	imshow("Contours on Animals", original);

		// �ƹ� Ű ������ ������ �������� shape�� �����Ѵ�
	cout << " Step-2) Press any key to detect shape descriptor...!! " << endl;
	waitKey(0);
	
	image = imread(argv[3], 0);
	// testing the bounding box
	Rect r0 = boundingRect(Mat(contours[0]));
	rectangle(result, r0, Scalar(0), 2);

	// testing the enclosing circle
	float radius;
	Point2f center;
	minEnclosingCircle(Mat(contours[1]), center, radius);
	circle(result, Point(center), static_cast<int>(radius), Scalar(0), 2);
	// testing the approximate polygon
	vector<Point> poly;
	approxPolyDP(Mat(contours[2]), poly, 5, true);
	cout << "Polygon size: " << poly.size() << endl;
	// Iterate over each segment and draw it
	vector<Point>::const_iterator itp = poly.begin();
	while (itp != (poly.end() - 1)) {
		line(result, *itp, *(itp + 1), cv::Scalar(0), 2);
		++itp;
	}
	// last point linked to first point
	line(result, *(poly.begin()), *(poly.end() - 1), cv::Scalar(20), 2);
		
	// testing the convex hull
	vector<Point> hull;
	convexHull(Mat(contours[3]), hull);
	// Iterate over each segment and draw it
	vector<Point>::const_iterator it = hull.begin();
	while (it != (hull.end() - 1)) {
		cv::line(result, *it, *(it + 1), cv::Scalar(0), 2);
		++it;
	}
	// last point linked to first point
	line(result, *(hull.begin()), *(hull.end() - 1), cv::Scalar(20), 2);
	// ��ŸƮ ����Ʈ�� ���� ����Ʈ�� �ձ� ���� �������� line�� ���ش�.

	itc = contours.begin();
	//moment �� �߽��� ��� 
	while (itc != contours.end()) {
		Moments mom = cv::moments(cv::Mat(*itc++));
		circle(result,Point(mom.m10 / mom.m00, mom.m01 / mom.m00),2, Scalar(0), 2); 
	}
	namedWindow("Some Shape descriptors");
	imshow("Some Shape descriptors", result);
	waitKey(0);
	return 0;
}