// ColorExtaction.cpp : Defines the entry point for the console application.
//
#include<iostream>
#include <string>
#include<vector>
#include<opencv2\imgproc.hpp>
#include<opencv2\highgui.hpp>
using namespace std;
using namespace cv;
/////////////Declaring Source & Output Variable ////////////////////////////////
Mat src, srcHSV, outputHSV,outputHSVInter, output; vector<Mat>channels(3); Mat thresholdChannel;
////Variables for the trackbars////////
int hMin = 0, sMin = 0, vMin = 0;
int hMax = 179, sMax = 255, vMax = 255;
int const maxThreshold = 255;
void applyColorExtraction(int, void*);
int main(int argc, const char* argv[])
{
	string filename;
	if (argc < 2) {
		cout << "Please input the location of the source image:in the command line itself" << endl;
		return 0;
	}
	filename = argv[1];//getting the file path in the program//
	src = imread(filename, CV_LOAD_IMAGE_COLOR);
	if (src.empty()) {
		cout << "file not found: please check the path or the presence of the file" << endl;
		return 0;
	}
	namedWindow("Color Extraction", CV_WINDOW_NORMAL);
	imshow("Color Extraction", src);
	cvtColor(src, srcHSV, CV_BGR2HSV);
	///////////hue Channel trackbar///////////////////////////////////////////////////////////
	// Trackbar to control the hue Channel min threshold
	createTrackbar("hue Min", "Color Extraction", &hMin, 179, applyColorExtraction);
	// Trackbar to control the hue Channel min threshold
	createTrackbar("hue Max", "Color Extraction", &hMax,179, applyColorExtraction);
	///////////Saturation Channel trackbar///////////////////////////////////////////////////////////
	// Trackbar to control the Sat Channel min threshold
	createTrackbar("Sat Min", "Color Extraction", &sMin, maxThreshold, applyColorExtraction);
	// Trackbar to control the Sat Channel min threshold
	createTrackbar("Sat Max", "Color Extraction", &sMax, maxThreshold, applyColorExtraction);
	///////////Value Channel trackbar///////////////////////////////////////////////////////////
	// Trackbar to control the Value Channel min threshold
	createTrackbar("Val Min", "Color Extraction", &vMin, maxThreshold, applyColorExtraction);
	// Trackbar to control the Value Channel min threshold
	createTrackbar("Val Max", "Color Extraction", &vMax, maxThreshold, applyColorExtraction);

	waitKey(0);
	destroyAllWindows();
	return 0;
}
void applyColorExtraction(int, void*) {
	outputHSV = srcHSV.clone();	 
	///////hue Channel Operation///////
	inRange(outputHSV, Scalar(hMin,sMin,vMin), Scalar(hMax, sMax, vMax), thresholdChannel);
	split(src, channels);//splitting the three channels in to three different Mat Files//
	thresholdChannel = thresholdChannel / 255;
	for (int i = 0; i < 3;i++) {
		channels[i] = channels[i].mul(thresholdChannel);
	}
	merge(channels, output);//merging channel for display
	//cvtColor(outputHSVInter, output, CV_HSV2BGR);
	//Display Images//
	//imshow("thresholded Channel", thresholdChannel);
	imshow("Color Extraction", output);

}

