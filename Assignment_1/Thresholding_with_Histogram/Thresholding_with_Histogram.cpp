// Thresholding_with_Histogram.cpp : Defines the entry point for the console application.
//
#include <string>
#include <stdio.h>
#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
using namespace std;
using namespace cv;

int thresholdValue = 150;
int thresholdType = 3;
int const maxValue = 255;
int const maxType = 4;
int const max_BINARY_value = 255;
Mat inputImage,dst;

string windowName = "Threshold Demo";
string trackbarType = "Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted";
string trackbarValue = "Value";

void thresholdUsingTrackbar(int, void*); //This function should be prototyped as void Foo(int, void*);//
MatND & histoGramPlot(Mat &);

int main(int argc,const char*argv[])
{
	if (!(argc >= 2)) {
		cout << "Provide the Path name of the image as a command line argument" << endl;
		return 0;
	}
	string filename = argv[1];//getting the ImageName;
	inputImage = imread(filename, CV_LOAD_IMAGE_GRAYSCALE);
	if (inputImage.empty()) {
		cout << "File not found" << endl;
		return 0;
	}
	// Create a window to display results
	namedWindow(windowName, CV_WINDOW_AUTOSIZE);
	
	
	/// Wait until user finishes program
	/*while (true) {
		int c;
		c = waitKey(20);
		if (static_cast<char>(c) == 27)
		{
			break;
		}
	}*/
	Mat hist=histoGramPlot(inputImage);
	int tempValue=0, tempLocation=0;
	for (int i = 0; i < hist.rows;i++) {
		if (i == 0) {
			tempValue = int(hist.at<float>(0,0));
			tempLocation = 0;
		}
		if (tempValue == 0 && hist.at<float>(i,0)==0) {
			tempLocation = i;
		}
		else {
			break;
		}
	}
	cout << tempLocation << endl;
	//cout << hist << endl;
	//thresholdValue = tempLocation;
	//threshold(inputImage, dst, thresholdValue, max_BINARY_value, thresholdType);
	//imshow(windowName, dst);
	// Create Trackbar to choose type of Threshold
	createTrackbar(trackbarType, windowName, &thresholdValue, maxType, thresholdUsingTrackbar);
	createTrackbar(trackbarValue, windowName, &thresholdValue, maxValue, thresholdUsingTrackbar);

	// Call the function to initialize//
	thresholdUsingTrackbar(0, 0); 
	waitKey(0);
	return 0;
}

void thresholdUsingTrackbar(int, void*) {
	/*
	0: Binary
	1: Binary Inverted
	2: Threshold Truncated
	3: Threshold to Zero
	4: Threshold to Zero Inverted
	*/

	threshold(inputImage, dst, thresholdValue, max_BINARY_value, thresholdType);

	imshow(windowName, dst);
}
MatND & histoGramPlot(Mat & inputImage) {
	// Initialize parameters//
	int histSize = 256;//number of bins in the histogram//
	float range[] = {0,255};//range of the values on the x axis is 0-255//
	const float *ranges[] = { range };
	static MatND hist;
	/*We use the calcHist() function in OpenCV to compute the histogram.Since the values
		in the H channel range from 0 to 179, we keep the number of bins at 180 and the
		range of values for the histogram from 0 to 179. Let�s see the arguments of the
		calcHist function.
		The 1st argument we have specified is channel[0] which is the H channel, the 2nd
		argument is the number of images(1), and the 3rd is the channel number of the
		image(but since we are just passing a single channel image, we specify 0).The 4th
		argument is the mask(but we want it for the whole matrix so we keep it empty), the
		5th is the output matrix histogram, and the 6th is the number of dimensions of
		histogram, which is 1 in our case.The 7th and 8th are the number of bins and range
		as defined in lines 31 - 33.*/
	calcHist(&inputImage, 1, 0, Mat(), hist, 1, &histSize, ranges,true, false);
	cout << hist.type() << endl;
	cout << hist.rows << endl;
	cout << hist.cols << endl;
	//cout<<hist<<endl;
	/*After getting the histogram, we need to write some more code to plot the histogram.
We define the height and width of the image (histImage) which we will use to show
the histogram. Finally we draw a line to specify the x-axis.*/
// Parameters for the plot
	
	 int hist_w = histSize * 3; int hist_h = 400;
	 int bin_w = cvRound((double)hist_w / histSize);
	
	 // construct the histogram as an image
	 Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(255, 255, 255));
	 normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

	 // draw the x-axis
	 line(histImage, Point(0, hist_h - 30), Point(hist_w, hist_h - 30), Scalar(0, 0, 0), 2, 8, 0);
	 // Draw the histogram
	 for (int i = 0; i <histSize; i++) {
		 if (i == 0) {
			 line(histImage, Point(bin_w*(i - 1), hist_h - 30),
				 Point(bin_w*(i), hist_h - 30 - cvRound(hist.at<float>(i))),
				 Scalar(0, 0, 255), 2, 8, 0);
		 }
		 else {
			 line(histImage, Point(bin_w*(i - 1), hist_h - 30 - cvRound(hist.at<float>(i - 1))),
				 Point(bin_w*(i), hist_h - 30 - cvRound(hist.at<float>(i))),
				 Scalar(0, 0, 255), 2, 8, 0);
		 }
		
		 // show the x axis values
		 if (i % 20 == 0)
		 {
			 char buffer[5];
			 sprintf(buffer, "%d", i);
			 line(histImage, Point(i*bin_w + 5, hist_h - 35), Point(i*bin_w + 5, hist_h - 25), Scalar(0, 0, 0), 2, 8, 0);
			 putText(histImage, buffer, Point(i*bin_w, hist_h - 5), cv::FONT_HERSHEY_COMPLEX, .5, (0, 0, 0), 1, cv::LINE_AA);
		 }
	 }
	 imshow("Histogram", histImage);
	 return hist;
}

