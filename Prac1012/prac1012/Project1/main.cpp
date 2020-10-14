#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>

using namespace cv;
using namespace std;


///--- Global variables----///
int threshold_value = 0;
int threshold_type = 3;
int const max_value = 255;
int const max_type = 4;
int const max_BINARY_value = 255;

Mat image, src_gray, dst;
void Threshold_Demo(int, void*);

int main(int argc, char** argv)
{
	/// Load image
	image = imread(argv[1], 1); // Read the file
	if (image.empty()) { // Check for invalid input
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}
	namedWindow("Display window"); // Create a window for display.
	imshow("Display window", image);
	/// Convert the image to Gray
	cvtColor(image, src_gray, COLOR_BGR2GRAY);

	//Threshold Demo
	/*
	/// Create a window to display results
	namedWindow("Threshold Demo");
	/// Create two Trackbars to choose type of Threshold on one window
	createTrackbar("Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted","Threshold Demo", &threshold_type, max_type, Threshold_Demo);
	createTrackbar("Value", "Threshold Demo", &threshold_value, max_value, Threshold_Demo);
	/// Call the function to initialize
	Threshold_Demo(0, 0);
	/// Wait until user finishes program
	while (true)
	{
		int c;
		c = waitKey(20);
		if ((char)c == 27)
		{
			break;
		}
	}
	*/
	////////**************************************************************************...///
	/// Create a window to display results
	namedWindow("Threshold Demo");
	/// Create Trackbar to choose type of Threshold
	createTrackbar("Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted", "Threshold Demo", &threshold_type, max_type, Threshold_Demo);
	createTrackbar("Value", "Threshold Demo", &threshold_value, max_value, Threshold_Demo);
	/// Call the function to initialize
	Threshold_Demo(0, 0);
	/// Wait until user finishes program
	while (true)
	{
		int c;
		c = waitKey(20);
		if ((char)c == 27)
		{
			break;
		}
	}
}
/*예제2*/
void Threshold_Demo(int, void*)
{
	/* 0: Binary 1: Binary Inverted 2: Threshold Truncated 3: Threshold to Zero 4: Threshold to Zero Inverted */
	//threshold( src_gray, dst, threshold_value, max_BINARY_value,threshold_type );
	adaptiveThreshold(src_gray, dst, max_value, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 5, 0);
	imshow("Threshold Demo", dst);
}

/* 예제 1

void Threshold_Demo(int, void*)
{
	// 0: Binary 1: Binary Inverted 2: Threshold Truncated 3: Threshold to Zero 4: Threshold to Zero Inverted 
	threshold(src_gray, dst, threshold_value, max_BINARY_value, threshold_type);
	imshow("Threshold Demo", dst);
}
*/