/*
	threshold
	adaptive threshold
	dilation erode open close
	thinning
	ximgproc
	watershed

*/
#include <opencv2/core/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>

using namespace cv;
using namespace std;
/*
int threshold_value = 0;
int threshold_type = 3;
int const max_value = 255;
int const max_type = 4;
int const max_BINARY_value = 255;

Mat image, src_gray, dst;

void Threshold_Demo(int, void*);

int main(int argc, char** argv) {

	image = imread(argv[1], 1);

	if (image.empty()) {
		cout << "could not open" << endl;
		return -1;
	}

	namedWindow("original image");
	imshow("original image", image);

	cvtColor(image, src_gray, COLOR_BGR2GRAY);

	namedWindow("Threshold Demo");
	//create two trackbars to choose type of threshold on one window
	createTrackbar("Type:\n 0:Binary\n1:Binary\n2:Truncate\n3:To Zero\n 4:To Zero Inverted", 
		"Threshold Demo", &threshold_type, max_type, Threshold_Demo);

	createTrackbar("Value", "Threshold Demo", &threshold_value, max_value, Threshold_Demo);

	Threshold_Demo(0,0);

	while (true) {
		int c;
		c = waitKey(20);
		if ((char)c == 27) //esc
		{	break; 	} 
	}

	waitKey(0);
	return 0;
}

void Threshold_Demo(int, void*) {
	threshold(src_gray, dst, threshold_value, max_BINARY_value, threshold_type);
	imshow("Threshold Demo", dst);
}
*/

// Adaptivethreshold() 의 예제 

int threshold_value = 0;
int threshold_type = 2;
int const max_value = 255;
int const max_type = 4;

Mat image, src_gray, dst;

void Threshold_Demo(int, void*);

int main(int argc, char** argv) {

	image = imread(argv[1], 1);

	namedWindow("original image");
	imshow("original image", image);

	cvtColor(image, src_gray, COLOR_BGR2GRAY);

	namedWindow("Adaptive Threshold");


	createTrackbar("Type:\n 0:Binary\n1:Binary\n2:Truncate\n3:To Zero\n 4:To Zero Inverted",
		"Adaptive Threshold", &threshold_type, max_type, Threshold_Demo);

	createTrackbar("Value", "Adaptive Threshold", &threshold_value, max_value, Threshold_Demo);

	Threshold_Demo(0, 0);

	while (true) {
		int c;
		c = waitKey(20);
		if ((char)c == 27) {
			break;
		}
	}

	waitKey(0);
	return 0;
}
void Threshold_Demo(int, void*) {
	adaptiveThreshold(src_gray, dst, max_value, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY,5,0);

	imshow("Adaptive Threshold", dst);
}



//Dilation Erosion closed open
/*
int threshold_value = 0;
int threshold_type = 3;
int const max_value = 255;
int const max_type = 4;
int const max_BINARY_value = 255;

int main(int argc, char** argv) {
	Mat image, src_gray, dst,dst1;

	image = imread(argv[1], 1);

	namedWindow("original image");
	imshow("original image", image);

	cvtColor(image, src_gray, COLOR_BGR2GRAY);

	threshold(src_gray, dst, 120, max_BINARY_value, threshold_type);
	namedWindow("t image");
//	imshow("t image", dst);

	erode(dst, dst1, Mat());
	namedWindow("eroded image");
//	imshow("eroded image", dst1);


	erode(dst, dst1, Mat(), Point(-1,-1),5);  //5회 수행
	namedWindow("eroded image : 5");
//	imshow("eroded image : 5", dst1);
	
	////////////////////

	dilate(dst, dst1, Mat()); 
	namedWindow("dilated image");
	//imshow("dilated image", dst1);
	dilate(dst, dst1, Mat(), Point(-1, -1), 5); 
	namedWindow("dilated image : 5");
	//imshow("dilated image : 5", dst1);

	// 열림 연산
	Mat element3(3, 3, CV_8U, Scalar(1));
	Mat opened;
	morphologyEx(image, opened, MORPH_OPEN, element3);
	namedWindow("Opened image");
	imshow("Opened image", opened);

	Mat element5(5, 5, CV_8U, Scalar(1));
	Mat closed;
	morphologyEx(image, closed, MORPH_CLOSE, element5);

	namedWindow("Closed image");
	imshow("Closeed image", opened);

	waitKey(0);
	return 0;
}
*/

//thinning 세선화
/*
int main(int argc, char** argv) {

	Mat image;

	image = imread(argv[1], 0);

	namedWindow("original image");
	imshow("original image", image);

	Mat skel(image.size(), CV_8UC1, Scalar(0));
	Mat temp(image.size(), CV_8UC1);

	Mat element = getStructuringElement(MORPH_CROSS, Size(3, 3));

	bool done;
	do {
		morphologyEx(image, temp, MORPH_OPEN, element);
		bitwise_not(temp, temp);
		bitwise_and(image, temp, temp);
		bitwise_or(skel, temp, skel);
		erode(image, image, element);

		double max;
		minMaxLoc(image, 0, &max);
		done = (max == 0);
	} while (!done);

	namedWindow("Skeleton");
	imshow("Skeleton", skel);

	waitKey(0);
	return 0;
}
*/
/*
#include <opencv2/ximgproc.hpp>

int main(int argc, char** argv) {

	Mat src, dst, tmp;
	char window_name[20] = "Pyramids Demo";
	
	src = imread(argv[1], 1);

	Mat img_grayscale, img_binary;

	cvtColor(src, img_grayscale, COLOR_BGR2GRAY);
	threshold(img_grayscale, img_binary, 0, 255, THRESH_OTSU | THRESH_BINARY_INV);

	Mat img_thinning_ZS, img_thinning_GH;
	ximgproc::thinning(img_binary, img_thinning_ZS, ximgproc::THINNING_ZHANGSUEN);
	ximgproc::thinning(img_binary, img_thinning_GH, ximgproc::THINNING_GUOHALL);

	Mat result_ZS(src.rows, src.cols, CV_8UC3);
	Mat result_GH(src.rows, src.cols, CV_8UC3);

	Mat in[] = { img_thinning_ZS, img_thinning_ZS, img_thinning_ZS };
	Mat in2[] = { img_thinning_GH, img_thinning_GH, img_thinning_GH};
	int from_to[] = { 0,0,1,1,2,2 };
	mixChannels(in, 3, &result_ZS, 1, from_to, 3);
	mixChannels(in2, 3, &result_GH, 1, from_to, 3);

	//combining everything into a canvas
	Mat canvas(src.rows, src.cols * 3, CV_8UC3);
	src.copyTo(canvas(Rect(0, 0, src.cols, src.rows)));
	result_ZS.copyTo(canvas(Rect(src.cols, 0, src.cols, src.rows)));
	result_GH.copyTo(canvas(Rect(src.cols*2,0, src.cols, src.rows)));
	
	imshow("Skeleton", canvas);
	waitKey(0);
	return 0;
}
*/
// 코너 검출기 
/*
class MorphoFeatures {

private:
	int threshold;
	Mat cross;
	Mat diamond;
	Mat square;
	Mat x;

	void applyThreshold(Mat& result) {
		if (threshold > 0)
			cv::threshold(result, result, threshold, 255, THRESH_BINARY_INV);
	}
public:
	MorphoFeatures() : threshold(-1), 
		cross(5, 5, CV_8U, Scalar(0)),
		diamond(5, 5, CV_8U, Scalar(1)),
		square(5, 5, CV_8U, Scalar(1)),
		x(5, 5, CV_8U, Scalar(0)) {

		for (int i = 0; i < 5; i++) {
			cross.at<uchar>(2, i) = 1;
			cross.at<uchar>(i, 2) = 1;
		}

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
		diamond.at<uchar>(1, 4) = 0;		// creating the x-shaped structuring element
		for (int i = 0; i < 5; i++) {
			x.at<uchar>(i, i) = 1;
			x.at<uchar>(4 - i, i) = 1;
		}
	}
	void setThreshold(int t) {
		threshold = t;
	}
	int getThreshold() const {
		return threshold;
	}
	Mat getEdges(const Mat& image) {
		Mat result;
		morphologyEx(image, result, MORPH_GRADIENT, Mat());

		applyThreshold(result);

		return result;
	}
	Mat getCorners(const Mat& image) {
		Mat result;   //닫힘 연산
		//dilate with cross
		dilate(image, result, cross);
		//erode with diamond
		erode(result, result, diamond);


		Mat result2;  //닫힘연산
		//dilate with X
		dilate(image, result2, x);
		//erode with a square
		erode(result2, result2, square);

		//corners are obtained by differencing
		// the two closed images
		absdiff(result2, result, result);

		applyThreshold(result);

		return result;
	}
	void drawOnImage(const Mat& binary, Mat& image) {
		Mat_ <uchar>::const_iterator it = binary.begin <uchar>();
		Mat_ <uchar>::const_iterator itend = binary.end <uchar>();

		//for each pixel;
		for (int i = 0; it != itend; ++it, ++i) {
			if (!*it)
				circle(image, Point(i % image.step, i / image.step), 5, Scalar(255, 0, 0));
		}
	}
};

int main(int argc, char** argv) {
	Mat image;
	image = imread(argv[1], 0);
	if (image.empty()) {
		cout << "no image found" << endl;
		return -1;
	}

	namedWindow("Display window");
	imshow("Display window", image);

	//클래서 객체 선언
	MorphoFeatures morpho;

	morpho.setThreshold(40);

	//get edges
	Mat edges;
	edges = morpho.getEdges(image);

	namedWindow("Edge");
	imshow("Edge", edges);

	morpho.setThreshold(-1);
	Mat corners;
	corners = morpho.getCorners(image);
	morphologyEx(corners, corners, MORPH_TOPHAT, Mat());
	threshold(corners, corners, 40, 255, THRESH_BINARY_INV);

	namedWindow("Corner");
	imshow("Corner", corners);

	morpho.drawOnImage(corners, image);

	namedWindow("corners on image");
	imshow("corners on image", image);

	waitKey(0);
	return 0;
}
*/

// watershed
/*
class WatershedSegmenter {

private:
	Mat markers;
public:
	void setMarkers(const Mat& markerImage) {
		markerImage.convertTo(markers,CV_32S);
	}
	Mat process(const Mat& image) {
		watershed(image, markers);
		return markers;
	}
	Mat getSegmentation() {
		Mat tmp;
		markers.convertTo(tmp, CV_8U);
		return tmp;
	}
	Mat getWatersheds() {
		Mat tmp;
		markers.convertTo(tmp, CV_8U, 255, 255);
		return tmp;
	}
};

int main(int argc, char** argv) {

	Mat image, gray, binary;

	image = imread(argv[1], 1);

	if (image.empty()) {
		cout << "could not open the image" << endl;
		return -1;
	}
	namedWindow("Display Window");
	imshow("Display Window", image);

	cvtColor(image, gray, COLOR_BGR2GRAY);
	threshold(gray, binary, 120, 255, THRESH_BINARY_INV);

	namedWindow("Binary Image");
	imshow("Binary Image", binary);

	Mat fg;
	erode(binary, fg, Mat(), Point(-1, -1), 6);

	namedWindow("Foreground Image");
	imshow("Foreground Image", fg);

	Mat bg;
	dilate(binary, bg, Mat(), Point(-1, -1), 6);
	threshold(bg, bg, 1, 128, THRESH_BINARY_INV);

	namedWindow("background Image");
	imshow("Background Image", bg);

	//show markers image
	Mat markers(binary.size(), CV_8U, Scalar(0));
	markers = fg + bg;
	namedWindow("Markers");
	imshow("Maskers", markers);

	//create watershed segmentation object
	WatershedSegmenter segmenter;

	segmenter.setMarkers(markers);
	Mat res = segmenter.process(image);

	namedWindow("segmentation");
	imshow("segmentation", segmenter.getSegmentation());


	namedWindow("watersheds");
	imshow("watersheds", segmenter.getWatersheds());

	waitKey(0);
	return 0;
}
*/