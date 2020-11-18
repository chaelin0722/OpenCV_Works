
#include <stdio.h>
#include <iostream>
#include "opencv2/core.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/calib3d.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/xfeatures2d.hpp"
#include <vector>
#include <cmath>


using namespace std;
using namespace cv;
using namespace cv::xfeatures2d;


const double THRESHOLD = 400;

//SIFT IMAGE FILES
void readme()
{
	cout << " Usage: CVapp.exe <img1> <img2>" << endl;
}

double euclidDistance(Mat& vec1, Mat& vec2) {
	double sum = 0.0;
	int dim = vec1.cols;
	for (int i = 0; i < dim; i++) {
		sum += (vec1.at<uchar>(0, i) - vec2.at<uchar>(0, i)) * (vec1.at<uchar>(0, i) - vec2.at<uchar>(0, i));
	}
	return sqrt(sum);
}

/**
 * Find the index of nearest neighbor point from keypoints.
 */
int nearestNeighbor(Mat& vec, vector<KeyPoint>& keypoints, Mat& descriptors) {
	int neighbor = -1;
	double minDist = 1e6;

	printf("===> Finding nearest neighbor point from keypoints....!! \n");

	for (int i = 0; i < descriptors.rows; i++) {
		KeyPoint pt = keypoints[i];
		Mat v = descriptors.row(i);
		double d = euclidDistance(vec, v);
		//printf("%d %f\n", v.cols, d);
		if (d < minDist) {
			minDist = d;
			neighbor = i;
		}
	}

	printf("===> Finished finding nearest neighbor point from keypoints....!! \n");

	if (minDist < THRESHOLD) {
		return neighbor;
	}

	return -1;
}

/**
 * Find pairs of points with the smallest distace between them
 */
void findPairs(vector<KeyPoint>& keypoints1, Mat& descriptors1,
	vector<KeyPoint>& keypoints2, Mat& descriptors2,
	vector<Point2f>& srcPoints, vector<Point2f>& dstPoints) {

	printf("===> Finding Keypoints pairs....!! \n");

	for (int i = 0; i < descriptors1.rows; i++) {
		KeyPoint pt1 = keypoints1[i];
		Mat desc1 = descriptors1.row(i);
		int nn = nearestNeighbor(desc1, keypoints2, descriptors2);
		if (nn >= 0) {
			KeyPoint pt2 = keypoints2[nn];
			srcPoints.push_back(pt1.pt);
			dstPoints.push_back(pt2.pt);
		}
	}

	printf("===> Finished finding Keypoints pairs....!! \n");
}

int main(int argc, char** argv) {

	if (argc != 3)
	{
		readme(); return -1;
	}

	Mat img_object = imread(argv[1], IMREAD_GRAYSCALE);
	Mat img_scene = imread(argv[2], IMREAD_GRAYSCALE);

	if (!img_object.data || !img_scene.data)
	{
		std::cout << " --(!) Error reading images " << std::endl; return -1;
	}


	cv::Ptr<cv::SIFT> sift;
	sift = cv::SIFT::create(0, 4, 0.04, 10, 1.6);

	// Compute keypoints and descriptor from the source image in advance
	vector<KeyPoint> keypoints1, keypoints2;
	Mat descriptors1, descriptors2;


	sift->detect(img_object, keypoints1);
	sift->compute(img_object, keypoints1, descriptors1);

	printf("original image:%d keypoints are found.\n", (int)keypoints1.size());

	for (int i = 0; i < keypoints1.size(); i++) {
		KeyPoint kp = keypoints1[i];
		circle(img_object, kp.pt, cvRound(kp.size * 0.25), Scalar(255, 255, 0), 1, 8, 0);
	}

	namedWindow("SIFT Keypoints-src");
	imshow("SIFT Keypoints-src", img_object);

	sift->detect(img_scene, keypoints2);
	sift->compute(img_scene, keypoints2, descriptors2);

	printf("original image:%d keypoints are found.\n", (int)keypoints2.size());

	for (int i = 0; i < keypoints2.size(); i++) {
		KeyPoint kp = keypoints2[i];
		circle(img_scene, kp.pt, cvRound(kp.size * 0.25), Scalar(255, 255, 0), 1, 8, 0);
	}

	namedWindow("SIFT Keypoints-tgt");
	imshow("SIFT Keypoints-tgt", img_scene);

	//-- Step 3: Matching descriptor vectors using FLANN matcher
	FlannBasedMatcher matcher;
	std::vector< DMatch > matches;
	matcher.match(descriptors1, descriptors2, matches);

	double max_dist = 0; double min_dist = 100;

	//-- Quick calculation of max and min distances between keypoints
	for (int i = 0; i < descriptors1.rows; i++)
	{
		double dist = matches[i].distance;
		if (dist < min_dist) min_dist = dist;
		if (dist > max_dist) max_dist = dist;
	}

	printf("-- Max dist : %f \n", max_dist);
	printf("-- Min dist : %f \n", min_dist);

	//-- Draw only "good" matches (i.e. whose distance is less than 3*min_dist )
	std::vector< DMatch > good_matches;

	for (int i = 0; i < descriptors1.rows; i++)
	{
		if (matches[i].distance < 3 * min_dist)
		{
			good_matches.push_back(matches[i]);
		}
	}

	Mat img_matches;
	drawMatches(img_object, keypoints1, img_scene, keypoints2,
		good_matches, img_matches, Scalar::all(-1), Scalar::all(-1),
		std::vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

	imshow("Matched Image", img_matches);
	waitKey(0);

	//-- Localize the object
	std::vector<Point2f> obj;
	std::vector<Point2f> scene;

	for (int i = 0; i < good_matches.size(); i++)
	{
		//-- Get the keypoints from the good matches
		obj.push_back(keypoints1[good_matches[i].queryIdx].pt);
		scene.push_back(keypoints2[good_matches[i].trainIdx].pt);
	}
	Mat H = findHomography(obj, scene, RANSAC);

	//-- Get the corners from the image_1 ( the object to be "detected" )
	std::vector<Point2f> obj_corners(4);
	obj_corners[0] = Point(0, 0); obj_corners[1] = Point(img_object.cols, 0);
	obj_corners[2] = Point(img_object.cols, img_object.rows); obj_corners[3] = Point(0, img_object.rows);
	std::vector<Point2f> scene_corners(4);

	perspectiveTransform(obj_corners, scene_corners, H);

	//-- Draw lines between the corners (the mapped object in the scene - image_2 )
	line(img_matches, scene_corners[0] + Point2f(img_object.cols, 0), scene_corners[1] + Point2f(img_object.cols, 0), Scalar(0, 255, 0), 4);
	line(img_matches, scene_corners[1] + Point2f(img_object.cols, 0), scene_corners[2] + Point2f(img_object.cols, 0), Scalar(0, 255, 0), 4);
	line(img_matches, scene_corners[2] + Point2f(img_object.cols, 0), scene_corners[3] + Point2f(img_object.cols, 0), Scalar(0, 255, 0), 4);
	line(img_matches, scene_corners[3] + Point2f(img_object.cols, 0), scene_corners[0] + Point2f(img_object.cols, 0), Scalar(0, 255, 0), 4);

	//-- Show detected matches
	imshow("Good Matches & Object detection", img_matches);

	waitKey(0);

	return 0;
}


//SIFT WEBCAM


//calculate uclidean distance
/*
double euclidDistance(Mat& vec1, Mat& vec2) {
	double sum = 0.0;
	int dim = vec1.cols;
	for (int i = 0; i < dim; i++) {
		//printf("vector: %d  %d \n", vec1.at<int>(0, i), vec2.at<int>(0, i));
		sum += (vec1.at<int>(0, i) - vec2.at<int>(0, i)) * (vec1.at<int>(0, i) - vec2.at<int>(0, i));
	}
	return sqrt(sum);
}

// Find the index of nearest neighbor point from keypoints.

int nearestNeighbor(Mat& vec, vector<KeyPoint>& keypoints, Mat& descriptors) {
	int neighbor = -1;
	double minDist = 1e6;

	printf("===> Finding nearest neighbor point from keypoints....!! \n");

	for (int i = 0; i < descriptors.rows; i++) {
		KeyPoint pt = keypoints[i];
		Mat v = descriptors.row(i);
		double d = euclidDistance(vec, v);
		//printf("%d %f\n", v.cols, d);
		if (d < minDist) {
			minDist = d;
			neighbor = i;
		}
	}

	printf("===> Finished finding nearest neighbor point from keypoints....!! \n");

	if (minDist < THRESHOLD) {
		return neighbor;
	}

	return -1;
}

// Find pairs of points with the smallest distace between them

void findPairs(vector<KeyPoint>& keypoints1, Mat& descriptors1,
	vector<KeyPoint>& keypoints2, Mat& descriptors2,
	vector<Point2f>& srcPoints, vector<Point2f>& dstPoints) {

	printf("===> Finding Keypoints pairs....!! \n");

	for (int i = 0; i < descriptors1.rows; i++) {
		KeyPoint pt1 = keypoints1[i];
		Mat desc1 = descriptors1.row(i);
		int nn = nearestNeighbor(desc1, keypoints2, descriptors2);
		printf("nn = %d\n", nn);
		if (nn >= 0) {
			KeyPoint pt2 = keypoints2[nn];
			srcPoints.push_back(pt1.pt);
			dstPoints.push_back(pt2.pt);
		}
	}

	printf("===> Finished finding Keypoints pairs....!! \n");
}

int main(int argc, char** argv) {

	if (argc < 2) {
		cerr << "Too few arguments" << endl;
		return -1;
	}

	const char* filename = argv[1];

	printf("load file:%s\n", filename);

	// initialize detector and extractor
	//cv::Ptr<cv::xfeatures2d::SIFT> sift;			//OpenCV 4.1.1 version
	//sift = cv::xfeatures2d::SIFT::create(0, 4, 0.04, 10, 1.6);
	cv::Ptr<cv::SIFT> sift;
	sift = cv::SIFT::create(0, 4, 0.04, 10, 1.6);

	// Compute keypoints and descriptor from the source image in advance
	vector<KeyPoint> keypoints_src;
	Mat descriptors_src;

	Mat originalGrayImage = imread(filename, IMREAD_GRAYSCALE);

	if (!originalGrayImage.data) {
		cerr << "gray image load error" << endl;
		return -1;
	}
	Mat originalColorImage = imread(filename, IMREAD_ANYCOLOR | IMREAD_ANYDEPTH);
	if (!originalColorImage.data) {
		cerr << "color image open error" << endl;
		return -1;
	}

	sift->detect(originalGrayImage, keypoints_src);
	sift->compute(originalGrayImage, keypoints_src, descriptors_src);

	printf("original image:%d keypoints are found.\n", (int)keypoints_src.size());

	for (int i = 0; i < keypoints_src.size(); i++) {
		KeyPoint kp = keypoints_src[i];
		circle(originalColorImage, kp.pt, cvRound(kp.size * 0.25), Scalar(255, 255, 0), 1, 8, 0);
	}

	namedWindow("SIFT Keypoints");
	imshow("SIFT Keypoints", originalColorImage);

	waitKey(0);

	VideoCapture capture(0);
	capture.set(cv::CAP_PROP_FRAME_WIDTH, 640);
	capture.set(cv::CAP_PROP_FRAME_HEIGHT, 480);

	namedWindow("mywindow");
	Mat frame;
	while (true) {
		capture >> frame;

		// load gray scale image from camera
		Size size = frame.size();
		Mat grayFrame(size, CV_8UC1);
		cvtColor(frame, grayFrame, COLOR_BGR2GRAY);
		if (!grayFrame.data) {
			cerr << "cannot find image file1" << endl;
			exit(-1);
		}

		// Create a image for displaying mathing keypoints
		Size sz = Size(size.width + originalColorImage.size().width, size.height + originalColorImage.size().height);
		Mat matchingImage = Mat::zeros(sz, CV_8UC3);

		// Draw camera frame
		Mat roi1 = Mat(matchingImage, Rect(0, 0, size.width, size.height));
		frame.copyTo(roi1);
		// Draw original image
		Mat roi2 = Mat(matchingImage, Rect(size.width, size.height, originalColorImage.size().width, originalColorImage.size().height));
		originalColorImage.copyTo(roi2);

		vector<KeyPoint> keypoints_dst;
		Mat descriptors_dst;
		vector<DMatch> matches;

		// Detect keypoints
		sift->detect(grayFrame, keypoints_dst);
		sift->compute(grayFrame, keypoints_dst, descriptors_dst);

		printf("image1:%zd keypoints are found.\n", keypoints_dst.size());

		//-- Step 3: Matching descriptor vectors using FLANN matcher
		FlannBasedMatcher matcher;
		matcher.match(descriptors_src, descriptors_dst, matches);

		double max_dist = 0; double min_dist = 100;

		//-- Quick calculation of max and min distances between keypoints
		for (int i = 0; i < descriptors_src.rows; i++)
		{
			double dist = matches[i].distance;
			if (dist < min_dist) min_dist = dist;
			if (dist > max_dist) max_dist = dist;
		}

		printf("-- Max dist : %f \n", max_dist);
		printf("-- Min dist : %f \n", min_dist);

		//-- Draw only "good" matches (i.e. whose distance is less than 3*min_dist )
		vector< DMatch > good_matches;

		for (int i = 0; i < descriptors_src.rows; i++)
		{
			if (matches[i].distance < 3 * min_dist)
			{
				good_matches.push_back(matches[i]);
			}
		}

		Mat img_matches;
		drawMatches(originalColorImage, keypoints_src, frame, keypoints_dst,
			good_matches, img_matches, Scalar::all(-1), Scalar::all(-1),
			vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

		imshow("Matched Image", img_matches);

		//waitKey(0);

		//-- Localize the object
		vector<Point2f> obj;
		vector<Point2f> scene;

		for (int i = 0; i < good_matches.size(); i++)
		{
			//-- Get the keypoints from the good matches
			obj.push_back(keypoints_src[good_matches[i].queryIdx].pt);
			scene.push_back(keypoints_dst[good_matches[i].trainIdx].pt);
		}

		Mat H = findHomography(obj, scene, RANSAC);

		//-- Get the corners from the image_1 ( the object to be "detected" )
		vector<Point2f> obj_corners(4);
		obj_corners[0] = Point(0, 0); obj_corners[1] = Point(originalGrayImage.cols, 0);
		obj_corners[2] = Point(originalGrayImage.cols, originalGrayImage.rows); obj_corners[3] = Point(0, originalGrayImage.rows);
		vector<Point2f> scene_corners(4);

		perspectiveTransform(obj_corners, scene_corners, H);

		//-- Draw lines between the corners (the mapped object in the scene - image_2 )
		line(img_matches, scene_corners[0] + Point2f(originalGrayImage.cols, 0), scene_corners[1] + Point2f(originalGrayImage.cols, 0), Scalar(0, 255, 0), 4);
		line(img_matches, scene_corners[1] + Point2f(originalGrayImage.cols, 0), scene_corners[2] + Point2f(originalGrayImage.cols, 0), Scalar(0, 255, 0), 4);
		line(img_matches, scene_corners[2] + Point2f(originalGrayImage.cols, 0), scene_corners[3] + Point2f(originalGrayImage.cols, 0), Scalar(0, 255, 0), 4);
		line(img_matches, scene_corners[3] + Point2f(originalGrayImage.cols, 0), scene_corners[0] + Point2f(originalGrayImage.cols, 0), Scalar(0, 255, 0), 4);

		//-- Show detected matches
		imshow("Good Matches & Object detection", img_matches);


		int c = waitKey(2);
		if (c == 27)	// Exit when "Esc" key is pressed....!!!
			break;
	}

	return 0;
}


void readme()
{
	cout << " Usage by webcam: CVapp.exe <img1>" << endl;
}
*/


//SURF
/*
void readme();
//practice.exe ../../../../images/church01.jpg ../../../../images/church02.jpg
int main(int argc, char** argv)
{
	if (argc != 3)
	{
		readme(); return -1;
	}

	Mat img_object = imread(argv[1], IMREAD_GRAYSCALE);
	Mat img_scene = imread(argv[2], IMREAD_GRAYSCALE);

	if (!img_object.data || !img_scene.data)
	{
		cout << " --(!) Error reading images " << endl; 
		return -1;
	}

	//-- Step 1: Detect the keypoints using SURF Detector
	int minHessian = 400;

	Ptr<SURF> detector = SURF::create(minHessian);// detector(minHessian);

	vector<KeyPoint> keypoints_object, keypoints_scene;

	detector->detect(img_object, keypoints_object);
	detector->detect(img_scene, keypoints_scene);

	//-- Step 2: Calculate descriptors (feature vectors)
	Ptr<SURF> extractor = SURF::create();

	Mat descriptors_object, descriptors_scene;

	extractor->compute(img_object, keypoints_object, descriptors_object);
	extractor->compute(img_scene, keypoints_scene, descriptors_scene);

	//-- Step 3: Matching descriptor vectors using FLANN matcher
	FlannBasedMatcher matcher;
	vector< DMatch > matches;
	matcher.match(descriptors_object, descriptors_scene, matches);

	double max_dist = 0; double min_dist = 100;

	//-- Quick calculation of max and min distances between keypoints
	for (int i = 0; i < descriptors_object.rows; i++)
	{
		double dist = matches[i].distance;
		if (dist < min_dist) min_dist = dist;
		if (dist > max_dist) max_dist = dist;
	}

	printf("-- Max dist : %f \n", max_dist);
	printf("-- Min dist : %f \n", min_dist);

	//-- Draw only "good" matches (i.e. whose distance is less than 3*min_dist )
	vector< DMatch > good_matches;

	for (int i = 0; i < descriptors_object.rows; i++)
	{
		if (matches[i].distance < 3 * min_dist)
		{
			good_matches.push_back(matches[i]);
		}
	}

	Mat img_matches;
	drawMatches(img_object, keypoints_object, img_scene, keypoints_scene,
		good_matches, img_matches, Scalar::all(-1), Scalar::all(-1),
		vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

	imshow("Matched Image", img_matches);
	waitKey(0);

	//-- Localize the object
	vector<Point2f> obj;
	vector<Point2f> scene;

	for (int i = 0; i < good_matches.size(); i++)
	{
		//-- Get the keypoints from the good matches
		obj.push_back(keypoints_object[good_matches[i].queryIdx].pt);
		scene.push_back(keypoints_scene[good_matches[i].trainIdx].pt);
	}

	Mat H = findHomography(obj, scene, RANSAC);

	//-- Get the corners from the image_1 ( the object to be "detected" )
	vector<Point2f> obj_corners(4);
	obj_corners[0] = Point(0, 0); obj_corners[1] = Point(img_object.cols, 0);
	obj_corners[2] = Point(img_object.cols, img_object.rows); obj_corners[3] = Point(0, img_object.rows);
	vector<Point2f> scene_corners(4);

	perspectiveTransform(obj_corners, scene_corners, H);

	//-- Draw lines between the corners (the mapped object in the scene - image_2 )
	line(img_matches, scene_corners[0] + Point2f(img_object.cols, 0), scene_corners[1] + Point2f(img_object.cols, 0), Scalar(0, 255, 0), 4);
	line(img_matches, scene_corners[1] + Point2f(img_object.cols, 0), scene_corners[2] + Point2f(img_object.cols, 0), Scalar(0, 255, 0), 4);
	line(img_matches, scene_corners[2] + Point2f(img_object.cols, 0), scene_corners[3] + Point2f(img_object.cols, 0), Scalar(0, 255, 0), 4);
	line(img_matches, scene_corners[3] + Point2f(img_object.cols, 0), scene_corners[0] + Point2f(img_object.cols, 0), Scalar(0, 255, 0), 4);

	//-- Show detected matches
	imshow("Good Matches & Object detection", img_matches);

	waitKey(0);
	return 0;

}

*/