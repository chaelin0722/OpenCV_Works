/*
	text 그리고
	두 이미지 블렌딩하기

*/
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2\opencv.hpp>
#include <iostream>
#include <string>
using namespace cv;
using namespace std;
/*
int main(int argc, char** argv) {
	string text = "Funny text inside the box";
	int fontFace = FONT_HERSHEY_SCRIPT_SIMPLEX;
	double fontScale = 2;
	int thickness = 3;

	Mat img(600, 800, CV_8UC3, Scalar::all(0));

	int baseline = 0;
	Size textSize = getTextSize(text, fontFace, fontScale, thickness, &baseline);
	baseline += thickness;

	Point textOrg((img.cols - textSize.width) / 2, (img.rows + textSize.height) / 2);

	// 박스 그리기
	rectangle(img, textOrg + Point(0, baseline), 
		textOrg + Point(textSize.width, -textSize.height), Scalar(0, 0, 255));
	// baseline 먼저 그리기
	line(img, textOrg + Point(0, thickness), textOrg + Point(textSize.width, thickness), Scalar(0, 0, 255));

	//put the text itself
	putText(img, text, textOrg, fontFace, fontScale, Scalar::all(255), thickness, 8);

	namedWindow("Display text");
	imshow("Display text", img);

	waitKey(0);
	destroyWindow("Drawing Graphics");

	return 0;
}
*/

const int alpha_slider_max = 100;
int alpha_slider;
double alpha;
double beta;

Mat image1, image2, dst;

void on_trackbar(int, void*);

int main(int argc, char** argv) {
	image1 = imread(argv[1], 1);
	image2 = imread(argv[2], 1);

	namedWindow("Display Blend");

	char TrackbarName[50];
	sprintf_s(TrackbarName, "Alpha x %d", alpha_slider_max);

	createTrackbar(TrackbarName, "Display Blend", &alpha_slider, alpha_slider_max, on_trackbar);

	on_trackbar(alpha_slider, 0);
	waitKey(0);
	destroyWindow("Display Blend"); // or destroyWindowall(); 
	return 0;
}

void on_trackbar(int, void*) {
	//alpha = (double)alpha_slider / alpha_slider_max;
	//beta = (1.0 - alpha);
	//addWeighted(image1, alpha, image2, beta, 0.0, dst);

	threshold(image1, dst, alpha_slider, 255, THRESH_BINARY);
	imshow("Display Blend",dst);
}