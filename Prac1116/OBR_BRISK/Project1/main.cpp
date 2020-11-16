#include <stdio.h>
#include <iostream>
#include <stdio.h>
#include <iostream>
#include "opencv2/core.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/calib3d.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/xfeatures2d.hpp"


using namespace std;
using namespace cv;
using namespace cv::xfeatures2d;
using namespace cv::xfeatures2d;
void readme()
{
	cout << " Usage: CVapp.exe <source img1> <target img2>" << endl;
}
//BRISK
// Find the homographic relationship.....!
/*
inline void findKeyPointsHomography(vector<KeyPoint>& kpts1, vector<KeyPoint>& kpts2,
	vector<DMatch>& matches, vector<char>& match_mask) {
	if (static_cast<int>(match_mask.size()) < 3) {
		return;
	}
	vector<Point2f> pts1;
	vector<Point2f> pts2;
	for (int i = 0; i < static_cast<int>(matches.size()); ++i) {
		pts1.push_back(kpts1[matches[i].queryIdx].pt);
		pts2.push_back(kpts2[matches[i].trainIdx].pt);
	}
	findHomography(pts1, pts2, cv::RANSAC, 4, match_mask);
}

int main(int argc, char** argv)
{
	if (argc != 3)
	{
		readme(); return -1;
	}

	Mat img_object = imread(argv[1], IMREAD_COLOR);
	Mat img_scene = imread(argv[2], IMREAD_COLOR);
	Mat img_gray_object, img_gray_scene;

	cvtColor(img_object, img_gray_object, COLOR_BGR2GRAY);
	cvtColor(img_scene, img_gray_scene, COLOR_BGR2GRAY);

	//BRISK Keypoint implementation for feature extraction
	Ptr<BRISK> brisk = BRISK::create(50);

	// Compute keypoints and descriptor from the source image in advance
	vector<KeyPoint> keypoints2, keypoints1;
	Mat descriptors2, descriptors1;

	// detecting and computing keypoints and descriptors
	brisk->detectAndCompute(img_gray_object, Mat(), keypoints2, descriptors2);
	brisk->detectAndCompute(img_gray_scene, Mat(), keypoints1, descriptors1);

	printf(" ==> original image:%d keypoints are found.\n", (int)keypoints2.size());
	printf(" ==> scene image:%d keypoints are found.\n", (int)keypoints1.size());

	for (int i = 0; i < keypoints2.size(); i++) {
		KeyPoint kp = keypoints2[i];
		circle(img_object, kp.pt, cvRound(kp.size * 0.25), Scalar(255, 255, 0), 1, 8, 0);
	}
	for (int i = 0; i < keypoints1.size(); i++) {
		KeyPoint kp = keypoints1[i];
		circle(img_scene, kp.pt, cvRound(kp.size * 0.25), Scalar(0, 0, 255), 1, 8, 0);
	}

	namedWindow("BRISK Keypoints-orignal");
	imshow("BRISK Keypoints-orignal", img_object);

	namedWindow("BRISK Keypoints-scene");
	imshow("BRISK Keypoints-scene", img_scene);

	// KNN matching implementation
	vector<DMatch> matches;
	BFMatcher desc_matcher(cv::NORM_L2, true);
	vector< vector<DMatch> > vmatches;
	desc_matcher.knnMatch(descriptors2, descriptors1, vmatches, 1);
	for (int i = 0; i < static_cast<int>(vmatches.size()); ++i) {
		if (!vmatches[i].size()) {
			continue;
		}
		matches.push_back(vmatches[i][0]);
	}

	vector<char> match_mask(matches.size(), 1);
	findKeyPointsHomography(keypoints2, keypoints1, matches, match_mask);

	Mat matchedimage;
	cv::drawMatches(img_object, keypoints2, img_scene, keypoints1, matches, matchedimage, Scalar::all(-1),
		Scalar::all(-1), match_mask, DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

	cv::imshow("Detected Result", matchedimage);

	waitKey(0);

	return 0;

}


*/

// ORB
inline void findKeyPointsHomography(vector<KeyPoint>& kpts1, vector<KeyPoint>& kpts2,
	vector<DMatch>& matches, vector<char>& match_mask) {
	if (static_cast<int>(match_mask.size()) < 3) {
		return;
	}
	vector<Point2f> pts1;
	vector<Point2f> pts2;
	for (int i = 0; i < static_cast<int>(matches.size()); ++i) {
		pts1.push_back(kpts1[matches[i].queryIdx].pt);
		pts2.push_back(kpts2[matches[i].trainIdx].pt);
	}
	findHomography(pts1, pts2, cv::RANSAC, 4, match_mask);
}

int main(int argc, char** argv)
{
	if (argc != 3)
	{
		readme(); return -1;
	}

	Mat img_object = imread(argv[1], IMREAD_COLOR);
	Mat img_scene = imread(argv[2], IMREAD_COLOR);
	Mat img_gray_object, img_gray_scene;

	cvtColor(img_object, img_gray_object, COLOR_BGR2GRAY);
	cvtColor(img_scene, img_gray_scene, COLOR_BGR2GRAY);

	//ORB Keypoint implementation for feature extraction
	Ptr<ORB> orb = ORB::create(500);

	// Compute keypoints and descriptor from the source image in advance
	vector<KeyPoint> keypoints2, keypoints1;
	Mat descriptors2, descriptors1;

	// detecting and computing keypoints and descriptors
	orb->detectAndCompute(img_gray_object, Mat(), keypoints2, descriptors2);
	orb->detectAndCompute(img_gray_scene, Mat(), keypoints1, descriptors1);

	printf(" ==> original image:%d keypoints are found.\n", (int)keypoints2.size());
	printf(" ==> scene image:%d keypoints are found.\n", (int)keypoints1.size());

	for (int i = 0; i < keypoints2.size(); i++) {
		KeyPoint kp = keypoints2[i];
		circle(img_object, kp.pt, cvRound(kp.size * 0.25), Scalar(255, 255, 0), 1, 8, 0);
	}
	for (int i = 0; i < keypoints1.size(); i++) {
		KeyPoint kp = keypoints1[i];
		circle(img_scene, kp.pt, cvRound(kp.size * 0.25), Scalar(0, 0, 255), 1, 8, 0);
	}

	namedWindow("ORB Keypoints-orignal");
	imshow("ORB Keypoints-orignal", img_object);

	namedWindow("ORB Keypoints-scene");
	imshow("ORB Keypoints-scene", img_scene);

	// KNN matching implementation
	vector<DMatch> matches;
	BFMatcher desc_matcher(cv::NORM_L2, true);
	vector< vector<DMatch> > vmatches;
	desc_matcher.knnMatch(descriptors2, descriptors1, vmatches, 1);
	for (int i = 0; i < static_cast<int>(vmatches.size()); ++i) {
		if (!vmatches[i].size()) {
			continue;
		}
		matches.push_back(vmatches[i][0]);
	}

	vector<char> match_mask(matches.size(), 1);
	findKeyPointsHomography(keypoints2, keypoints1, matches, match_mask);

	Mat matchedimage;
	cv::drawMatches(img_object, keypoints2, img_scene, keypoints1, matches, matchedimage, Scalar::all(-1),
		Scalar::all(-1), std::vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

	cv::imshow("Detected Result", matchedimage);

	waitKey(0);

	return 0;

}
