/*
	HLS 를 이용해서 피부색을 검출하는 방식..!
*/
/*
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {

	if (argc != 2) {
		cout << "provide image name to read" << endl;
		return -1;
	}

	Mat inputImg;
	Mat hlsImg;
	Mat skinImg;

	inputImg = imread(argv[1]);
	skinImg = inputImg.clone();

	cvtColor(inputImg, hlsImg, COLOR_BGR2HLS);
	vector<Mat> hls_image(3);

	for (int row = 0; row < hlsImg.rows; row++) {
		for (int col = 0; col < hlsImg.cols; col++) {
			uchar H = hlsImg.at<Vec3b>(row, col)[0];
			uchar L = hlsImg.at<Vec3b>(row, col)[1];
			uchar S = hlsImg.at<Vec3b>(row, col)[2];

			double LS_ratio = ((double)L) / ((double)S);
			bool skin_pixel = (S >= 50) && (LS_ratio > 0.5) && (LS_ratio < 3.0) &&
				((H <= 14) || (H >= 165));
			// 피부색 외에는 다 검정!
			if (skin_pixel == false) {  
				skinImg.at<Vec3b>(row, col)[0] = 0;
				skinImg.at<Vec3b>(row, col)[1] = 0;
				skinImg.at<Vec3b>(row, col)[2] = 0;
			}
		}
	}
	namedWindow("original");
	moveWindow("original", 100, 100);
	imshow("original", inputImg);

	namedWindow("skinDetected");
	moveWindow("skinDetected", 120, 120);
	imshow("skinDetected", skinImg);

	waitKey(0);
	return 0;
}

*/
/*

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	Mat frame,ret;
	int count = 0;
	int avg_time = 0;
	
	Mat hsv, hue, binary, hand;


	VideoCapture cap;
	cap.open(0);
	if (!cap.isOpened()) {
		cout << "ERROR! Unable to open camera\n";
		return -1;
	}

	for (;;) {
		cap.read(frame);
		cap.read(ret);
		if (frame.empty()|| ret.empty()) {
			cout << "error! blank frame grabbed\n";
			break;
		}
		
		cvtColor(frame, hsv, COLOR_BGR2HLS);
		vector<Mat> hls_image(3);

		for (int row = 0; row < hsv.rows; row++) {
			for (int col = 0; col < hsv.cols; col++) {
				uchar H = hsv.at<Vec3b>(row, col)[0];
				uchar L = hsv.at<Vec3b>(row, col)[1];
				uchar S = hsv.at<Vec3b>(row, col)[2];

				double LS_ratio = ((double)L) / ((double)S);
				bool skin_pixel = (S >= 50) && (LS_ratio > 0.5) && (LS_ratio < 3.0) &&
					((H <= 14) || (H >= 165));
				// 피부색 외에는 다 검정!
				if (skin_pixel == false) {
					hsv.at<Vec3b>(row, col)[0] = 0;
					hsv.at<Vec3b>(row, col)[1] = 0;
					hsv.at<Vec3b>(row, col)[2] = 0;
				}
			}
		}



		







		imshow("Live", frame);
		if (waitKey(5) >= 0)
			break;
	}
	return 0;
}
*/


#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

Point getHandCenter(cv::Mat& mask, double& radius);
float fingerEnd(float p1, float p2, float t1, float t2, float q1, float q2);

vector<Point> saveLine;

int erosion_value = 0;
int const max_erosion = 2;
int erosion_size = 0;
int const ersion_max_size = 21;
int dilation_value = 0;
int dilation_size = 0;
int erosion_type = 0;
int drawX, drawY;

int main()
{
	Mat element;
	Mat frame, tmpImg;
	Mat handImg, mask, mask1;
	Point dst;

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	double radius = 5;
	VideoCapture video(0);

	if (!video.isOpened()) {
		cout << "video not open error!" << endl;
		return 0;
	}

	namedWindow("change_image");
	namedWindow("original_image");
	createTrackbar("ele_erosion", "original_image", &erosion_value, max_erosion);
	createTrackbar("erosion_size", "original_image", &erosion_size, ersion_max_size);
	createTrackbar("ele_dilation", "original_image", &dilation_value, max_erosion);
	createTrackbar("dilation_size", "original_image", &dilation_size, ersion_max_size);

	while (true)
	{
		tmpImg = video.clone();
		//video >> tmpImg;

		if (tmpImg.empty()) break;

		if (erosion_value == 0) erosion_type = MORPH_RECT;
		else if (erosion_value == 1) erosion_type = MORPH_CROSS;
		else if (erosion_value == 2) erosion_type = MORPH_ELLIPSE;

		element = getStructuringElement(erosion_type, Size(2 * erosion_size + 1, 2 * erosion_size + 1), Point(erosion_size, erosion_size));

		//피부색이 가지는 Cb,Cr의 영역은 
		//Cb: 77 ~ 127 / Cr: 133 ~ 173

		//먼저 영상을 YCrCB로 변경한다.
		cvtColor(tmpImg, handImg, COLOR_BGR2YCrCb);
		inRange(handImg, Scalar(0, 133, 77), Scalar(255, 173, 127), handImg);
		//열림으로 처리해줘 좀더 깔끔하게 분리
		erode(handImg, handImg, element);
		dilate(handImg, handImg, element);

		mask = handImg.clone();


		findContours(mask, contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE, Point(0, 0));


		int largestContour = 0;

		for (int i = 0; i < contours.size(); i++) {
			if (contourArea(contours[i]) > contourArea(contours[largestContour])) {
				largestContour = i;
			}
		}
		//컨투어 그리기 
		drawContours(tmpImg, contours, largestContour, Scalar(0, 255, 255), 1, 8, std::vector < Vec4i>(), 0, Point());	

		if (!contours.empty()) {
			vector<vector<Point>>hull(1);

			convexHull(Mat(contours[largestContour]), hull[0], false);
			drawContours(tmpImg, hull, 0, Scalar(0, 255, 0), 1, 8, vector<Vec4i>(), 0, Point());		//점 잇기

			if (hull[0].size() > 2) {

				Rect boundingBox = cv::boundingRect(hull[0]);
				Point center = cv::Point(boundingBox.x + boundingBox.width / 2, boundingBox.y + boundingBox.height / 2);

				vector<cv::Point> validPoints;

				vector<int> hullIndex;
				convexHull(cv::Mat(contours[largestContour]), hullIndex);
				vector<cv::Vec4i> convexityDefects;

				cv::convexityDefects(cv::Mat(contours[largestContour]), hullIndex, convexityDefects);

				for (int i = 0; i < convexityDefects.size(); i++) {
					cv::Point p1 = contours[largestContour][convexityDefects[i][0]];
					cv::Point p2 = contours[largestContour][convexityDefects[i][1]];
					cv::Point p3 = contours[largestContour][convexityDefects[i][2]];
					//cv::line(tmpImg, p1, p3, cv::Scalar(255, 0, 0), 2);
					//cv::line(tmpImg, p3, p2, cv::Scalar(255, 0, 0), 2);

					double angle = std::atan2(center.y - p1.y, center.x - p1.x) * 180 / CV_PI;
					double inA = fingerEnd(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y);
					double length = std::sqrt(std::pow(p1.x - p3.x, 2) + std::pow(p1.y - p3.y, 2));

					if (angle > -30 && angle < 160 && std::abs(inA) > 20 && std::abs(inA) < 120 && length > 0.1 * boundingBox.height)
					{
						validPoints.push_back(p1);
					}
				}

				int maxY = 0, maxX = 0;

				if (validPoints.size() != 0) {
					maxY = validPoints[0].y, maxX = validPoints[0].x;

					for (int i = 0; i < validPoints.size(); i++)
					{
						if (validPoints[i].y < maxY) {
							maxY = validPoints[i].y;
							maxX = validPoints[i].x;
						}
						cv::circle(tmpImg, cv::Point(maxX, maxY), 9, cv::Scalar(255, 0, 0), 2);

						saveLine.push_back(cv::Point(maxX, maxY));

						for (std::vector<int>::size_type i = 0; i < saveLine.size(); i++) {
							cv::line(tmpImg, saveLine[i], saveLine[i], cv::Scalar(255, 5, 222), 5);
						}

						if (cv::waitKey(10) == 32) {
							saveLine.clear();
						}
						maxY = 0; maxX = 0;
					}
				}
			}
		}

		line(tmpImg, cv::Point(drawX, drawY), cv::Point(drawX, drawY), cv::Scalar(0, 0, 0), 3, 8, 0);

		flip(handImg, handImg, 1);	//영상 반전
		flip(tmpImg, tmpImg, 1);	//영상 반전

		imshow("change_image", handImg);
		imshow("original_image", tmpImg);

		if (waitKey(10) == 27) {
			break;
		}
	}


	video.release();
	tmpImg.release();
	frame.release();

	destroyAllWindows();

	return 0;
}

Point getHandCenter(Mat& mask, double& radius)
{
	int maxDst[2];

	Mat dst;	//행렬 저장
	distanceTransform(mask, dst, DIST_L2, 5);

	//최솟값 필요 없음
	minMaxIdx(dst, NULL, &radius, NULL, maxDst, mask);

	return Point(maxDst[1], maxDst[0]);
}

float fingerEnd(float p1, float p2, float t1, float t2, float q1, float q2)
{
	//두점 사이 거리 계산하기 위해. 제곱근 계산하는 sqrt
	float dist1 = std::sqrt((p1 - q1) * (p1 - q1) + (p2 - q2) * (p2 - q2));
	float dist2 = std::sqrt((t1 - q1) * (t1 - q1) + (t2 - q2) * (t2 - q2));

	float aX, aY;
	float bX, bY;
	float cX, cY;

	cX = q1;
	cY = q2;

	if (dist1 < dist2) {
		bX = p1;
		bY = p2;
		aX = t1;
		aY = t2;
	}
	else {
		bX = t1;
		bY = t2;
		aX = p1;
		aY = p2;
	}

	float r1 = cX - aX;
	float r2 = cY - aY;
	float z1 = bX - aX;
	float z2 = bY - aY;

	float result = std::acos((z1 * r1 + z1 * r2) / (std::sqrt(z1 * z1 + z2 * z2) * std::sqrt(r1 * r1 + r2 * r2)));

	result =(result * 180 )/ CV_PI;

	return result;
}