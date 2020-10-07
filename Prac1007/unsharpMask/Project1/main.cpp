/* unsharp mask 를 이용한 영상 처리!*/
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>

using namespace cv;
using namespace std;

//Unsharp Mask 이용 실습
int main(int argc, char** argv) {
	Mat image, result, dst, dst1;

	image = imread(argv[1], 1);

	if (image.empty()) {
		cout << "Could not open or find the image" << endl;
		return -1;
	}

	namedWindow("Original image");
	imshow("Original image", image);

	// Unsharp 부분!
	Mat blurred; 
	double sigma = 1;
	double threshold = 5;
	double amount = 1;
	GaussianBlur(image, blurred, Size(), sigma, sigma /*border type 은 default로 들어가게 되어있음*/); 
	Mat lowContrastMask = abs(image - blurred) < threshold;  // 원본과 블러 처리된 이미지의 차이가 threshold 보다 작게 만듦..
	Mat sharpened = image * (1 + amount) + blurred * (-amount);
	image.copyTo(sharpened, lowContrastMask);

	namedWindow("Sharpened image");
	imshow("Sharpened image", sharpened);

	waitKey(0);

	return 0;
}


//resampling 실습
/*
int main(int argc, char** argv)
{
	Mat src, dst, tmp;
	/// General instructions
	printf("\n Zoom In-Out demo \n ");
	printf("------------------ \n");
	printf(" * [u] -> Zoom in \n");
	printf(" * [d] -> Zoom out \n");
	printf(" * [ESC] -> Close program \n \n");

	/// Test image - Make sure it s divisible by 2^{n}
	src = imread(argv[1]);
	if (!src.data)
	{
		printf(" No data! -- Exiting the program \n");
		return -1;
	}
	tmp = src;
	dst = tmp;
	/// Create window
	namedWindow("Original Image");
	imshow("Original Image", src);
	/// Loop
	while (true) {
		int c;
		c = waitKey(10);
		if ((char)c == 27) { break; } // ESC 키 입력 시 종료
		if ((char)c == 'u')
		{
			pyrUp(tmp, dst, Size(tmp.cols * 2, tmp.rows * 2));
			printf("** Zoom In: Image x 2 \n");
		}
		else if ((char)c == 'd') {
			pyrDown(tmp, dst, Size(tmp.cols / 2, tmp.rows / 2));
			printf("** Zoom Out: Image / 2 \n");
		}
		imshow("pyramid demo", dst);
		tmp = dst;
	}
	return 0;
}
*/

/*sobel 예제*/
/*
int main(int argc, char** argv) {
	Mat image, result;
	image = imread(argv[1], 0);
	if (!image.data)
		return 0;
	// Display the image
	cv::namedWindow("Original Image");
	cv::imshow("Original Image", image);
	// Compute Sobel X derivative
	cv::Mat sobelX;
	cv::Sobel(image, sobelX, CV_8U, 1, 0, 3, 0.4, 128);
	// Display the image
	cv::namedWindow("Sobel X Image");
	cv::imshow("Sobel X Image", sobelX);
	// Compute Sobel Y derivative
	cv::Mat sobelY;
	cv::Sobel(image, sobelY, CV_8U, 0, 1, 3, 0.4, 128);

	// Compute norm of Sobel
	cv::Sobel(image, sobelX, CV_16S, 1, 0);
	cv::Sobel(image, sobelY, CV_16S, 0, 1);
	cv::Mat sobel;
	//compute the L1 norm
	sobel = abs(sobelX) + abs(sobelY);
	double sobmin, sobmax;
	cv::minMaxLoc(sobel, &sobmin, &sobmax);
	cv::Mat sobelImage;
	sobel.convertTo(sobelImage, CV_8U, -255. / sobmax, 255);
	// Display the image
	cv::namedWindow("Sobel Image");
	cv::imshow("Sobel Image", sobelImage);
	// Apply threshold to Sobel norm (low threshold value)
	cv::Mat sobelThresholded;
	cv::threshold(sobelImage, sobelThresholded, 225, 255, cv::THRESH_BINARY);
	// Display the image
	cv::namedWindow("Binary Sobel Image (low)");
	cv::imshow("Binary Sobel Image (low)", sobelThresholded);
	
	waitKey(0);

	return 0;
}*/