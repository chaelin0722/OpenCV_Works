/*
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


// FAST KEYPOINT를 찾고 MATCH 해주기 -> 연습! googling 하래
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
*/
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

/*
int main(int argc, char** argv){
	// image read
	Mat img_object = cv::imread(argv[1], 1);
	Mat img_scene = cv::imread(argv[1], 1);
	if (!img_object.data || !img_scene.data) {
	std::cout << " --(!) Error reading images " << std::endl;
		return -1;
	}
	// SIFT feature detector and feature extractor
	cv::Ptr<cv::xfeatures2d::SIFT> sift;
	sift = cv::xfeatures2d::SIFT::create(0, 4, 0.04, 10, 1.6);

	// Compute keypoints and descriptor from the source image in advance
	vector<KeyPoint> keypoints1, keypoints2;
	Mat descriptors1, descriptors2;
	sift->detect(img_object, keypoints1);   // keypoint 찾기 
	sift->compute(img_object, keypoints1, descriptors1);  //keypoint 기반으로 descript 생성
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
	for (int i = 0; i < descriptors1.rows; i++) {
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
		if (matches[i].distance < 3 * min_dist) {
			good_matches.push_back(matches[i]);
		}
	}

	Mat img_matches;
	drawMatches(img_object, keypoints1, img_scene, keypoints2,
		good_matches, img_matches, Scalar::all(-1), Scalar::all(-1),
		std::vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
	imshow("Matched Image", img_matches);
	waitKey(0);
	return 0;
}
*/
/*
int main(int argc, char** argv)
{
	Mat img_1 = imread(argv[1], 0);
	Mat img_2 = imread(argv[2], 0);
	if (!img_1.data || !img_2.data)
	{
		std::cout << " --(!) Error reading images " << std::endl; return -1;
	}
	if (argc != 3)
	{
		return -1;
	}
	Mat img_1 = imread(argv[1], IMREAD_GRAYSCALE);
	Mat img_2 = imread(argv[2], IMREAD_GRAYSCALE);
	if (!img_1.data || !img_2.data)
	{
		std::cout << " --(!) Error reading images " << std::endl; return -1;
	}
	//-- Step 1: Detect the keypoints using SURF Detector
	int minHessian = 400;
	Ptr<SURF> detector = SURF::create(minHessian);// detector(minHessian);
	std::vector<KeyPoint> keypoints_1, keypoints_2;
	detector->detect(img_1, keypoints_1);
	detector->detect(img_2, keypoints_2);
	//-- Draw keypoints
	Mat img_keypoints_1; Mat img_keypoints_2;
	drawKeypoints(img_1, keypoints_1, img_keypoints_1, Scalar::all(-1),
		DrawMatchesFlags::DEFAULT);
	drawKeypoints(img_2, keypoints_2, img_keypoints_2, Scalar::all(-1),
		DrawMatchesFlags::DEFAULT);
	//-- Show detected (drawn) keypoints
	imshow("Keypoints 1", img_keypoints_1);
	imshow("Keypoints 2", img_keypoints_2);

	Ptr<SURF> extractor = SURF::create();
	// Extraction of the SURF descriptors
	Mat descriptors1, descriptors2;
	extractor->compute(img_1, keypoints_1, descriptors1);
	extractor->compute(img_2, keypoints_2, descriptors2);
	cout << "descriptor matrix size: " << descriptors1.rows << " by "
		<< descriptors1.cols << std::endl;
	// Construction of the matcher
	BFMatcher matcher(cv::NORM_L2, false);
	// Match the two image descriptors
	vector<cv::DMatch> matches;
	matcher.match(descriptors1, descriptors2, matches);
	cout << "Number of matched points: " << matches.size() << std::endl;
	//-- Draw matches---//
	cv::Mat img_matches;
	cv::drawMatches(img_1, keypoints_1, img_2, keypoints_2, matches, img_matches);
	//-- Show detected matches
	imshow("Matches", img_matches);
	//--- Filtering loop ---//
	std::nth_element(matches.begin(), // initial position
		matches.begin() + 24, // position of the sorted element
		matches.end()); // end position
		// remove all elements after the 25th
	matches.erase(matches.begin() + 25, matches.end());
	cv::Mat imageMatches1;
	cv::drawMatches(img_1, keypoints_1, // 1st image and its keypoints
		img_2, keypoints_2, // 2nd image and its keypoints
		matches,// the matches
		imageMatches1,// the image produced
		cv::Scalar(255, 255, 255)); // color of the lines
	cv::namedWindow("Filtered Matches");
	cv::imshow("Filtered Matches", imageMatches1);
	
	waitKey(0); 
	return 0;

}

*/
