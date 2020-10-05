#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>

using namespace cv;
using namespace std;

// RGB �� ��忡 ���� Equalization
/*
int main(int argc, char** argv)
{
	Mat image, dst;
	/// Load image
	image = imread(argv[1], 1); // Read the file
	if (image.empty()) { // Check for invalid input
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}
	namedWindow("Display window", WINDOW_AUTOSIZE);
	imshow("Display window", image);
	//--�÷� ���� ��Ȱȭ --//
	Mat channels[3];
	// ���� ä�� �и�
	split(image, channels);

	//equalize histogram on the each channel
	equalizeHist(channels[0], channels[0]);
	equalizeHist(channels[1], channels[1]);
	equalizeHist(channels[2], channels[2]);
	//merge 3 channels including the modified 1st channel into one image
	merge(channels, 3, image);
	namedWindow("Equalized Image", WINDOW_AUTOSIZE);
	// Create a window for display.
	imshow("Equalized Image", image);
	waitKey(0);
	return 0;
}

*/

int main(int argc, char** argv)
{
	Mat image, dst;
	/// Load image
	image = imread(argv[1], 1); // Read the file


	if (image.empty()) { // Check for invalid input
		cout << "Could not open or find the image" << endl;
		return -1;
	}

	namedWindow("Display window", WINDOW_AUTOSIZE);
	imshow("Display window", image);
    //--�÷� ���� ��Ȱȭ --//
	Mat channels[3];
	//�÷���ȯ
	cvtColor(image, dst, COLOR_BGR2YCrCb);
	// ���� ä�� �и�
	split(dst, channels);
	//equalize histogram on the 1st channel (Y)
	equalizeHist(channels[0], channels[0]);
	//merge 3 channels including the modified 1st channel into one image
	merge(channels, 3, dst);
	//�÷���ȯ to BGR
	cvtColor(dst, image, COLOR_YCrCb2BGR);
	namedWindow("Equalized Image", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("Equalized Image", image);
	waitKey(0);
	return 0;
}