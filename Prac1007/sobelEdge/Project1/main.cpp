/* sobel edge : convolution based processing filtering : edge!*/
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {

	Mat image, result;

	image = imread(argv[1], 0);

	if (!image.data) {
		cout << "Could not found image" << endl;
		return -1;
	}

	namedWindow("Original Image");
	imshow("Original Image", image);

	//sobel X,Y Ã³¸®
	Mat sobelX;
	Sobel(image, sobelX, CV_8U, 1, 0, 3, 0.4, 128);

	namedWindow("Sobel X Image");
	imshow("Sobel X Image", sobelX);

	Mat sobelY;
	Sobel(image, sobelY, CV_8U, 0, 1, 3, 0.4, 128);


	namedWindow("Sobel Y Image");
	imshow("Sobel Y Image", sobelY);

	// compute norm of sobel
	Sobel(image, sobelX, CV_16S, 1, 0);
	Sobel(image, sobelY, CV_16S, 0, 1);

	Mat sobel;
	//compute L1 norm
	sobel = abs(sobelX) + abs(sobelY);

	double sobmin, sobmax;
	minMaxLoc(sobel, &sobmin, &sobmax);

	Mat sobelImage;
	sobel.convertTo(sobelImage, CV_8U, -255./sobmax, 255);

	namedWindow("Sobel Image");
	imshow("Sobel Image", sobelImage);

	// apply threshold to sobel norm
	Mat sobelThresholded;
	threshold(sobelImage, sobelThresholded, 255, 255, THRESH_BINARY);

	namedWindow("Binary Sobel Image (low)");
	imshow("Binary Sobel Image (low)", sobelThresholded);

	waitKey(0);

	return 0;
}
