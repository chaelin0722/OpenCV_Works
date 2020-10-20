#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>

using namespace cv;
using namespace std;
/*
//--Class for Corner detection ---//
class MorphoFeatures {
private:
	// threshold to produce binary image
	int threshold;
	// structuring elements used in corner detection
	Mat cross;
	Mat diamond;
	Mat square;
	Mat x;
	void applyThreshold(Mat& result) {
		// Apply threshold on result
		if (threshold > 0)
			cv::threshold(result, result, threshold, 255, THRESH_BINARY_INV);
	}
public:
	MorphoFeatures() : threshold(-1), cross(5, 5, CV_8U, cv::Scalar(0)),
		diamond(5, 5, CV_8U, cv::Scalar(1)),
		square(5, 5, CV_8U, cv::Scalar(1)),
		x(5, 5, CV_8U, cv::Scalar(0)) {
		// Creating the cross-shaped structuring element
		for (int i = 0; i < 5; i++) {
			cross.at<uchar>(2, i) = 1;
			cross.at<uchar>(i, 2) = 1;
		}
		// Creating the diamond-shaped structuring element
		diamond.at<uchar>(0, 0) = 0;
		diamond.at<uchar>(0, 1) = 0;
		diamond.at<uchar>(1, 0) = 0;
		diamond.at<uchar>(4, 4) = 0;
		diamond.at<uchar>(3, 4) = 0;
		diamond.at<uchar>(4, 3) = 0;
		diamond.at<uchar>(4, 0) = 0;
		diamond.at<uchar>(4, 1) = 0;
		diamond.at<uchar>(3, 0) = 0;
		diamond.at<uchar>(0, 4) = 0;
		diamond.at<uchar>(0, 3) = 0;
		diamond.at<uchar>(1, 4) = 0;
		// Creating the x-shaped structuring element
		for (int i = 0; i < 5; i++) {
			x.at<uchar>(i, i) = 1;
			x.at<uchar>(4 - i, i) = 1;
		}
	}	void setThreshold(int t) {
		threshold = t;
	}
	int getThreshold() const {
		return threshold;
	}
	Mat getEdges(const cv::Mat& image) {
		// Get the gradient image
		Mat result;
		morphologyEx(image, result, MORPH_GRADIENT, Mat());
		// Apply threshold to obtain a binary image
		applyThreshold(result);
		return result;
	}	Mat getCorners(const cv::Mat& image) {
		Mat result;
		// Dilate with a cross
		dilate(image, result, cross);
		// Erode with a diamond
		erode(result, result, diamond);
		Mat result2;
		// Dilate with a X
		dilate(image, result2, x);
		// Erode with a square
		erode(result2, result2, square);
		// Corners are obtained by differencing
		// the two closed images
		absdiff(result2, result, result);
		// Apply threshold to obtain a binary image
		applyThreshold(result);
		return result;
	}
	void drawOnImage(const Mat& binary, Mat& image) {
		Mat_<uchar>::const_iterator it = binary.begin<uchar>();
		Mat_<uchar>::const_iterator itend = binary.end<uchar>();
		// for each pixel
		for (int i = 0; it != itend; ++it, ++i) {
			if (!*it)
				circle(image, Point(i % image.step, i / image.step), 5, Scalar(255, 0, 0));
		}
	}
};

int main(int argc, char** argv)
{
	/// Load image
	Mat image;
	image = imread(argv[1], 0); 
	if (image.empty()) { 
		cout << "Could not open or find the image" << endl;
		return -1;
	}
	namedWindow("Display window");
	imshow("Display window", image);
	//--클래스 객체 선언 --//
	MorphoFeatures morpho;
	morpho.setThreshold(40);
	//--에지 가져오기 --//
	// Get the edges
	Mat edges;
	edges = morpho.getEdges(image);
	// Display the edge image
	namedWindow("Edge Image");
	imshow("Edge Image", edges);
	//-- Get the corners--//
	morpho.setThreshold(-1);
	Mat corners;
	corners = morpho.getCorners(image);
	morphologyEx(corners, corners, MORPH_TOPHAT, Mat());	// Display the corner image
	namedWindow("Corner Image");
	imshow("Corner Image", corners);
	// Display the corner on the image
	morpho.drawOnImage(corners, image);
	namedWindow("Corners on Image");
	imshow("Corners on Image", image);
	waitKey(0);
	return 0;
}*/class WatershedSegmenter {
private:
	cv::Mat markers;
public:
	void setMarkers(const cv::Mat& markerImage) {
		// Convert to image of ints
		markerImage.convertTo(markers, CV_32S);
	}
	cv::Mat process(const cv::Mat& image) {
		// Apply watershed
		cv::watershed(image, markers);
		return markers;
	}

	// Return result in the form of an image
	cv::Mat getSegmentation() {
		cv::Mat tmp;
		// all segment with label higher than 255
		// will be assigned value 255
		markers.convertTo(tmp, CV_8U);
		return tmp;
	}
	// Return watershed in the form of an image
	cv::Mat getWatersheds() {
		cv::Mat tmp;
		markers.convertTo(tmp, CV_8U, 255, 255);
		return tmp;
	}
};

int main(int argc, char** argv)
{
	Mat image, gray, binary;
	/// Load image
	image = imread(argv[1], 1); // Read the file
	if (image.empty()) { // Check for invalid input
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}
	namedWindow("Display window", WINDOW_AUTOSIZE);
	imshow("Display window", image);
	cvtColor(image, gray, COLOR_BGR2GRAY);
	threshold(gray, binary, 120, 255, THRESH_BINARY_INV);
	// Display the binary image
	cv::namedWindow("Binary Image");
	cv::imshow("Binary Image", binary);

	// Eliminate noise and smaller objects
	cv::Mat fg;
	cv::erode(binary, fg, cv::Mat(), cv::Point(-1, -1), 6);
	// Display the foreground image
	cv::namedWindow("Foreground Image");
	cv::imshow("Foreground Image", fg);
	// Identify image pixels without objects
	cv::Mat bg;
	cv::dilate(binary, bg, cv::Mat(), cv::Point(-1, -1), 6);
	cv::threshold(bg, bg, 1, 128, cv::THRESH_BINARY_INV);
	// Display the background image
	cv::namedWindow("Background Image");
	cv::imshow("Background Image", bg);
	// Show markers image
	cv::Mat markers(binary.size(), CV_8U, cv::Scalar(0));
	markers = fg + bg;
	cv::namedWindow("Markers");
	cv::imshow("Markers", markers);

	// Create watershed segmentation object
	WatershedSegmenter segmenter;
	// Set markers and process
	segmenter.setMarkers(markers);
	Mat res = segmenter.process(image);
	// Display segmentation result
	//cv::namedWindow("Pre - Segmentation");
	//cv::imshow("Pre - Segmentation",res);
			// Display segmentation result
	cv::namedWindow("Segmentation");
	cv::imshow("Segmentation", segmenter.getSegmentation());
	// Display watersheds
	cv::namedWindow("Watersheds");
	cv::imshow("Watersheds", segmenter.getWatersheds());
	waitKey(0);
	return 0;
}