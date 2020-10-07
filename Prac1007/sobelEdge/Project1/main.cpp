/* sobel edge : convolution based processing filtering : edge!*/
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>

using namespace cv;
using namespace std;
/*
int main(int argc, char** argv) {

	Mat image, result;

	image = imread(argv[1], 0);

	if (!image.data) {
		cout << "Could not found image" << endl;
		return -1;
	}

	namedWindow("Original Image");
	imshow("Original Image", image);

	//sobel X,Y 贸府
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
*/
//Laplacian tutorial

int main(int argc, char** argv) {

	Mat src, src_gray, dst;
	int kernel_size = 3;
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;

	int c;

	src = imread(argv[1], 1);

	if (!src.data) {
		cout << "Could not found imaage" << endl;
		return -1;
	}

	namedWindow("Original image");
	imshow("Original image", src);

	GaussianBlur(src, src, Size(3, 3), 0, 0, BORDER_DEFAULT);

	cvtColor(src, src_gray, COLOR_BGR2GRAY);

	//apply laplace function
	Mat abs_dst;
	Laplacian(src_gray, dst, ddepth, kernel_size, scale, delta, BORDER_DEFAULT);
	convertScaleAbs(dst, abs_dst);
	/*gaussian blur 贸府 饶 laplacian 贸府 秦淋*/

	namedWindow("Laplace Demo");
	imshow("Laplace Demo", abs_dst);

	waitKey(0);
	return 0;
}