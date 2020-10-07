/* Convolution processing 기반 필터링!  */

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>

using namespace cv;
using namespace std;
/*
int main(int argc, char** argv) {
	


	Mat image,result;
	char* imageName = argv[1];

	image = imread(imageName,
		IMREAD_COLOR);
	if (argc != 2 || !image.data) {
		printf(" No image data \n ");
		return -1;
	}
	
	namedWindow("Original Image");
	imshow("Original Image", image);
	// Blur the image with a mean filter
	blur(image, result, cv::Size(5, 5));
	// Display the blurred image
	namedWindow("Mean filtered Image");
	imshow("Mean filtered Image", result);
	// Gaussian Blur the image
	GaussianBlur(image, result, cv::Size(5, 5), 1.5);
	// Display the blurred image
	namedWindow("Gaussian filtered Image");
	imshow("Gaussian filtered Image", result);
	// Get the gaussian kernel (1.5)
	Mat gauss = cv::getGaussianKernel(9, 1.5, CV_32F);
	// Display kernel values
	Mat_<float>::const_iterator it = gauss.begin<float>();
	Mat_<float>::const_iterator itend = gauss.end<float>();
	std::cout << "[";
	for (; it != itend; ++it) {
		std::cout << *it << " ";
	}
	std::cout << "]" << std::endl;

	return 0;
}*//* salt image -> mean filter, median filter, gaussian*/void salt(Mat& img, int n);int main(int argc, char** argv)
{
	Mat image, result, dst, dst1;
	/// Load image
	image = imread(argv[1], 1); // Read the file
	if (image.empty()) { // Check for invalid input
		cout << "Could not open or find the image"
			<< std::endl;
		return -1;
	}
	// make a noise image
	salt(image, 30000);
	// Display the S&P image
	cv::namedWindow("S&P Image");
	cv::imshow("S&P Image", image);
	// Blur the image with a mean filter
	cv::blur(image, result, cv::Size(5, 5));
	// Display the blurred image
	namedWindow("Mean filtered S&P Image");
	imshow("Mean filtered S&P Image", result);	// Applying a median filter
	medianBlur(image, result, 5);
	// Display the blurred image
	namedWindow("Median filtered S&P Image");
	imshow("Median filtered S&P Image", result);
	
	// Gaussian Blur the image
	GaussianBlur(image, result, cv::Size(5, 5), 1.5);
	// Display the blurred image
	namedWindow("Gaussian filtered Image");
	imshow("Gaussian filtered Image", result);
	// Get the gaussian kernel (1.5)

	waitKey(0);
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