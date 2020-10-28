#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	Mat image, gray, binary;
	/// Load image
	image = imread(argv[1], 1); 
	if (image.empty()) { 
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}
	namedWindow("Display window"); 
	imshow("Display window", image);
	// define bounding rectangle --전경(객체 부분) 정의
	Rect rectangle2(10, 100, 380, 180);
	Mat bkgModel, fgrModel; // the models (internally used) =>
	Mat result; 
	Mat foreground(image.size(), CV_8UC3, Scalar(255, 255, 255));

	// GrabCut segmentation
	grabCut(image, result,rectangle2, bkgModel, fgrModel, 5, GC_INIT_WITH_RECT);
	// Get the pixels marked as likely foreground
	result = result & 1;
	foreground.create(image.size(), CV_8UC3);
	foreground.setTo(cv::Scalar(255, 255, 255));
	image.copyTo(foreground, result); // bg pixels not copied
	// draw rectangle on original image
	rectangle(image, rectangle2, Scalar(255, 255, 255), 1);
	namedWindow("Image 2");
	imshow("Image 2", image);
	// display result
	namedWindow("Foreground objects");
	imshow("Foreground objects", foreground);
	waitKey(0);
	return 0;
}