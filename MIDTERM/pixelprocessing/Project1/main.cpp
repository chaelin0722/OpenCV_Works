// 컬러모델 연습 
/*
	히스토그램

*/
#include <opencv2/core/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;
/*
int main(int argc, char** argv) {

	Mat img,img2, result;
	img = imread(argv[1],1);\

	if (img.empty()){
		cout << "no image" << endl;
		return -1;
	}

	Mat rgbChannels[3];
	split(img, rgbChannels);

	namedWindow("blue");
	imshow("blue", rgbChannels[0]);
	namedWindow("green");
	imshow("green", rgbChannels[1]);
	namedWindow("red");
	imshow("red", rgbChannels[2]);

	Mat g, fin_img;
	g = Mat::zeros(img.size(), CV_8UC1);
	
	//-- Showing Red Channel
//-- G and B channels are kept as zero matrix for visual perception
	{
		vector<Mat> channels;
		channels.push_back(g);
		channels.push_back(g);
		channels.push_back(rgbChannels[2]);

		merge(channels, fin_img);
		namedWindow("r", 1);
		imshow("r", fin_img);
	}
	{
		//green
		vector<Mat> channels;
		channels.push_back(g);
		channels.push_back(rgbChannels[1]);
		channels.push_back(g);

		merge(channels, fin_img);
		namedWindow("G");
		imshow("G", fin_img);
	}
	{
		//blue
		vector<Mat> channels;
		channels.push_back(rgbChannels[0]);
		channels.push_back(g);
		channels.push_back(g);

		merge(channels, fin_img);
		namedWindow("G");
		imshow("G",fin_img);
	}

	waitKey(0);
	return 0;
}*/
int main(int argc, char** argv)
{
	Mat image, dst;

	image = imread(argv[1], 1);
	
	Mat channels[3];

	cvtColor(image, dst, COLOR_BGR2YCrCb);
	split(dst, channels);
	equalizeHist(channels[0], channels[0]);
	merge(channels, 3, dst);

	cvtColor(dst, image, COLOR_YCrCb2BGR);

	namedWindow("result");
	imshow("result", image);

	waitKey(0);
	return 0;
}