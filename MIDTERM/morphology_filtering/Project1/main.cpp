
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>

using namespace cv;
using namespace std;
/*
int threshold_value = 0;
int threshold_type = 3;
int const max_value = 255;
int const max_type = 4;
int const max_BINARY_value = 255;

Mat image, src_gray, dst;

void Threshold_Demo(int, void*);

int main(int argc, char** argv) {

	image = imread(argv[1], 1);

	if (image.empty()) {
		cout << "could not open" << endl;
		return -1;
	}

	namedWindow("original image");
	imshow("original image", image);

	cvtColor(image, src_gray, COLOR_BGR2GRAY);

	namedWindow("Threshold Demo");
	//create two trackbars to choose type of threshold on one window
	createTrackbar("Type:\n 0:Binary\n1:Binary\n2:Truncate\n3:To Zero\n 4:To Zero Inverted", 
		"Threshold Demo", &threshold_type, max_type, Threshold_Demo);

	createTrackbar("Value", "Threshold Demo", &threshold_value, max_value, Threshold_Demo);

	Threshold_Demo(0,0);

	while (true) {
		int c;
		c = waitKey(20);
		if ((char)c == 27) //esc
		{	break; 	} 
	}

	waitKey(0);
	return 0;
}

void Threshold_Demo(int, void*) {
	threshold(src_gray, dst, threshold_value, max_BINARY_value, threshold_type);
	imshow("Threshold Demo", dst);
}

*/
// Adaptivethreshold() 의 예제 
/*
int threshold_value = 0;
int threshold_type = 2;
int const max_value = 255;
int const max_type = 4;

Mat image, src_gray, dst;

void Threshold_Demo(int, void*);

int main(int argc, char** argv) {

	image = imread(argv[1], 1);

	namedWindow("original image");
	imshow("original image", image);

	cvtColor(image, src_gray, COLOR_BGR2GRAY);

	namedWindow("Adaptive Threshold");

	createTrackbar("Type:\n 0:Binary\n1:Binary\n2:Truncate\n3:To Zero\n 4:To Zero Inverted",
		"Adaptive Threshold", &threshold_type, max_type, Threshold_Demo);

	createTrackbar("Value", "Adaptive Threshold", &threshold_value, max_value, Threshold_Demo);

	Threshold_Demo(0, 0);

	while (true) {
		int c;
		c = waitKey(20);
		if ((char)c == 27) {
			break;
		}
	}

	waitKey(0);
	return 0;
}
void Threshold_Demo(int, void*) {
	adaptiveThreshold(src_gray, dst, max_value, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY,5,0);

	imshow("Adaptive Threshold", dst);
}

*/

//Dilation Erosion closed open
/*
int threshold_value = 0;
int threshold_type = 3;
int const max_value = 255;
int const max_type = 4;
int const max_BINARY_value = 255;

int main(int argc, char** argv) {
	Mat image, src_gray, dst,dst1;

	image = imread(argv[1], 1);

	namedWindow("original image");
	imshow("original image", image);

	cvtColor(image, src_gray, COLOR_BGR2GRAY);

	threshold(src_gray, dst, 120, max_BINARY_value, threshold_type);
	namedWindow("t image");
//	imshow("t image", dst);

	erode(dst, dst1, Mat());
	namedWindow("eroded image");
//	imshow("eroded image", dst1);


	erode(dst, dst1, Mat(), Point(-1,-1),5);  //5회 수행
	namedWindow("eroded image : 5");
//	imshow("eroded image : 5", dst1);
	
	////////////////////

	dilate(dst, dst1, Mat()); 
	namedWindow("dilated image");
	//imshow("dilated image", dst1);
	dilate(dst, dst1, Mat(), Point(-1, -1), 5); 
	namedWindow("dilated image : 5");
	//imshow("dilated image : 5", dst1);

	// 열림 연산
	Mat element3(3, 3, CV_8U, Scalar(1));
	Mat opened;
	morphologyEx(image, opened, MORPH_OPEN, element3);
	namedWindow("Opened image");
	imshow("Opened image", opened);

	Mat element5(5, 5, CV_8U, Scalar(1));
	Mat closed;
	morphologyEx(image, closed, MORPH_CLOSE, element5);

	namedWindow("Closed image");
	imshow("Closeed image", opened);

	waitKey(0);
	return 0;
}
*/

//thinning 세선화

int main(int argc, char** argv) {

	Mat image;

	image = imread(argv[1], 0);

	namedWindow("original image");
	imshow("original image", image);

	Mat skel(image.size(), CV_8UC1, Scalar(0));
	Mat temp(image.size(), CV_8UC1);

	Mat element = getStructuringElement(MORPH_CROSS, Size(3, 3));

	bool done;
	do {
		morphologyEx(image, temp, MORPH_OPEN, element);
		bitwise_not(temp, temp);
		bitwise_and(image, temp, temp);
		bitwise_or(skel, temp, skel);
		erode(image, image, element);

		double max;
		minMaxLoc(image, 0, &max);
		done = (max == 0);
	} while (!done);

	namedWindow("Skeleton");
	imshow("Skeleton", skel);

	waitKey(0);
	return 0;
}