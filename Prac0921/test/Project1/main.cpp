/*#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>

using namespace std;  
using namespace cv;   
double alpha; //simple contrast
int beta; //simple brightness
int main(int argc, char** argv) {
	/// Read image given by user
	Mat image = imread(argv[1]);
	Mat new_image = Mat::zeros(image.size(), image.type());
	/// Initialize values
	cout << " Basic Linear Transforms " << endl;
	cout << "-------------------" << endl;
	cout << "* Enter the alpha value [1.0-3.0]: ";
	cin >> alpha;
	cout << "* Enter the beta value [0-100]: ";
	cin >> beta;
	/// Do the operation new_image(i,j) = alpha*image(i,j) + beta
	for (int y = 0; y < image.rows; y++) {
		for (int x = 0; x < image.cols; x++) {
			for (int c = 0; c < 3; c++) {
				new_image.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(alpha * (image.at<Vec3b>(y, x)[c]) + beta);
			}
		}
	}
	/// Create Windows
	namedWindow("Original Image", 1);
	namedWindow("New Image", 1);
	/// Show stuff
	imshow("Original Image", image);
	imshow("New Image", new_image);
	/// Wait until user press some key
	waitKey();
	return 0;
}
*/

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <iostream>
using namespace cv;
using namespace std;
int main()
{
	Mat image;
	//image = imread("lena.jpg", CV_LOAD_IMAGE_COLOR);
	image = imread("../../../../images/beach.jpg", IMREAD_UNCHANGED);
	if (!image.data)
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}
	// Create a new matrix to hold the gray image
	Mat gray;
	// convert RGB image to gray
	//cvtColor(image, gray, CV_BGR2GRAY);
	cvtColor(image, gray, COLOR_BGR2GRAY);
	namedWindow("Display window");
	imshow("Display window", image);
	namedWindow("Result window");
	imshow("Result window", gray);

	waitKey(0);
	return 0;

}