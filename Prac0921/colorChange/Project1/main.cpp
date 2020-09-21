#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>

using namespace std;  
using namespace cv;   


void salt(Mat& img, int n); // 잡음 추가 함수 선언
int main(int argc, char** argv)
{
	//--OpenCV 2.x 구쐼?현o --//
	Mat image, result;
	image = imread("../../../../images/moose.jpg", IMREAD_COLOR); // Read the file
	if (image.empty()) { // Check for invalid input
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}
	namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("Display window", image); // Show our image inside it.
	result = image.clone();
	salt(result, 3000);
	namedWindow("Processed image"); // Create a window for display.
	imshow("Processed image", result);// Show our image inside it.
	waitKey(0); // Wait for a keystroke in the window
	destroyAllWindows();
	return 0;
}

void salt(Mat& img, int n)
{
	for (int k = 0; k < n; k++) {
		int i = rand() % img.cols;
		int j = rand() % img.rows;
		if (img.channels() == 1) { // Gray scale image
			img.at<uchar>(j, i) = 255;
		}
		else if (img.channels() == 3) { // Color image
			img.at<Vec3b>(j, i)[0] = 255;
			img.at<Vec3b>(j, i)[1] = 255;
			img.at<Vec3b>(j, i)[2] = 255;
		}
	}
}

/*
int main(int argc, char** argv) {
	Mat image;
	char* imageName = argv[1];
	image = imread(imageName, 1);
	//--1) Mat bgr[3] 기반 color 분할
	Mat bgr[3]; //destination array
	split(image, bgr);//split source //Note: OpenCV uses BGR color order
	//-- Show each color channel image
	namedWindow("Color Image");
	imshow("Color Image", image);
	namedWindow("Blue channel");
	namedWindow("Green channel");
	namedWindow("Red channel");
	imshow("Blue channel", bgr[0]);
	imshow("Green channel", bgr[1]);
	imshow("Red channel", bgr[2]);
	//-- Color converting example
	Mat dst;
	cvtColor(image, dst, COLOR_RGB2YCrCb);
	split(dst, bgr);//split source //Note: OpenCV uses YCrCb color order
	namedWindow("Y channel"); imshow("Y channel", bgr[0]);
	namedWindow("Cb channel"); imshow("Cb channel", bgr[1]);
	namedWindow("Cr channel"); imshow("Cr channel", bgr[2]);
	//-- Pixel processing Example with Y-component: bgr[0] plane
	Mat result;
	result = bgr[0].clone();
	int Thres = 128;
	for (int i = 0; i < dst.rows; i++) {
		for (int j = 0; j < dst.cols; j++) {
			if (bgr[0].at<uchar>(i, j) > Thres) {
				result.at<uchar>(i, j) = 255;
			}
			else {
				result.at<uchar>(i, j) = 0;
			}
		}
	}
	namedWindow("Pixel Processing");
	imshow("Pixel Processing", result);

	waitKey(0);
	//-- Color merging with 3 separated channels
	Mat merged_img;
	//-- Mtehod 1 --//
	/*vector<Mat> channels;
	channels.push_back(bgr[0]);
	channels.push_back(bgr[1]);
	channels.push_back(bgr[2]);
	merge(channels, merged_img); */
	//-- Method 2 --//
	/*
	merge(bgr, 3, merged_img);
	namedWindow("Merged image", 1);
	imshow("Merged image", merged_img);
	waitKey(0);
	return 0;
}

*/