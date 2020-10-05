#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2\opencv.hpp>
#include <iostream>
#include <string>
using namespace cv;
using namespace std;
void mouseEvent(int evt, int x, int y, int flags, void* param) {
	Mat* rgb = (Mat*)param;
	if (evt == EVENT_LBUTTONDOWN)
	{
		printf("%d %d= b: %d, g: %d, r: %d\n",
			x, y,
			(int)(*rgb).at<Vec3b>(y, x)[0],
			(int)(*rgb).at<Vec3b>(y, x)[1],
			(int)(*rgb).at<Vec3b>(y, x)[2]);
	}
}
int main(int argc, char** argv) {
	//--OpenCV 2.x ±¸Çö --//
	Mat image, result;
	image = imread("../../../../images/Desert.bmp", IMREAD_COLOR); // Read the file 

	if (image.empty()) // Check for invalid input
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}
	namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.
	//set the callback function for any mouse event
	setMouseCallback("Display window", mouseEvent, &image);
	imshow("Display window", image); // Show our image inside it.
	waitKey(0); // Wait for a keystroke in the window
	return 0;
}