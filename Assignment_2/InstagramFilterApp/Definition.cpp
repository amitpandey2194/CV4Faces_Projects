#include <opencv2\imgproc.hpp>
#include<opencv2\highgui.hpp>
#include <iostream>
#include <vector>
#include "Declarations.h"
using namespace std;
using namespace cv;
Mat image2Display;
int value = 0;
int scale = 0;
InstagramFilters object;
//Functions for the Trackbars//
void filterTrackBarCallingFunction(int, void*) {
	
	switch(value)
	{
		case 0:
			image2Display = source.clone();
			break;
		case 1:
			image2Display = object.clarendonFilter();
			break;
		case 2:
			image2Display = object.kelvinFilter();
			break;
		case 3:
			image2Display = object.moonFilter();
			break;
		case 4:
			image2Display = object.X_Pro2Filter();
			break;
		default:
			break;
	}
	imshow("Test", image2Display);
	//image2Display.release();
}
void haloEffectTrackBarCallingFunction(int, void*) {
	Mat img;
	
		img = object.Vignette(image2Display, scale);
		imshow("Test", img);
	
}
void InstagramFilters::trackbarFunction() {
	namedWindow("Test", CV_WINDOW_NORMAL);
	createTrackbar("Filters", "Test", &value, 4, filterTrackBarCallingFunction);
	createTrackbar("Halo Effect", "Test", &scale, 8, haloEffectTrackBarCallingFunction);
	
}
/*

void X_Pro2Filter(int, void*) {}
void pencilSketchFilter(int, void*) {}
void haloFilter(int, void*) {}*/
//Functions for the filter Definition//
////InterPolation Function for Creating LookUp Table and Interpolating the Values between the original Values to New Values on the Curve//
Mat InstagramFilters::clarendonFilter() {
	//Enhance the channel for any image BGR or HSV etc
	Mat img = source.clone();
	float origin[] = { 0, 28, 56, 85, 113, 141, 170, 198, 227, 255 };
	float rCurve[] = { 0, 16, 35, 64, 117, 163, 200, 222, 237, 249 };
	float gCurve[] = { 0, 24, 49, 98, 141, 174, 201, 223, 239, 255 };
	float bCurve[] = { 0, 38, 66, 104, 139, 175, 206, 226, 245 , 255 };

	// Splitting the channels
	vector<Mat> channels(3);
	split(img, channels);

	// Create a LookUp Table
	float fullRange[256];
	int i;

	for (i = 0; i<256; i++)
	{
		fullRange[i] = (float)i;
	}

	Mat lookUpTable(1, 256, CV_8U);
	uchar* lut = lookUpTable.ptr();

	// Apply interpolation and create look up table
	interPolation(lut, fullRange, bCurve, origin);

	// Apply mapping and check for underflow/overflow in Red Channel
	LUT(channels[0], lookUpTable, channels[0]);

	// Apply interpolation and create look up table
	interPolation(lut, fullRange, gCurve, origin);

	// Apply mapping and check for underflow/overflow in Blue Channel
	LUT(channels[1], lookUpTable, channels[1]);

	// Apply interpolation and create look up table
	interPolation(lut, fullRange, rCurve, origin);

	// Apply mapping and check for underflow/overflow in Blue Channel
	LUT(channels[2], lookUpTable, channels[2]);

	Mat output;
	// Merge the channels 
	merge(channels, output);

	return output;
}
Mat InstagramFilters::kelvinFilter() {
	//Enhance the channel for any image BGR or HSV etc
	Mat img = source.clone();
	// Specifying the x-axis for mapping 
	float originalR[] = { 0, 60, 110, 150, 235, 255 };
	float originalG[] = { 0, 68, 105, 190, 255 };
	float originalB[] = { 0, 88, 145, 185, 255 };

	// Specifying the y-axis for mapping
	float rCurve[] = { 0, 102, 185, 220, 245, 245 };
	float gCurve[] = { 0, 68, 120, 220, 255 };
	float bCurve[] = { 0, 12, 140, 212, 255 };
	//Splitting the Channels//
	vector <Mat> channels(3);
	split(img, channels);
	//Creating a Lookup Table//
	float fullRange[256];
	for (int i = 0; i < 256;i++) {
		fullRange[i] = float(i);
	}
	Mat lookUpTable(1, 256, CV_8U);
	uchar *lut = lookUpTable.ptr();
	// Apply interpolation and create look up table//
	interPolation(lut,fullRange,bCurve,originalB);
	// Apply mapping and check for underflow/overflow in Blue Channel
	LUT(channels[0], lookUpTable, channels[0]);
	// Apply interpolation and create look up table//
	interPolation(lut, fullRange, gCurve, originalG);
	// Apply mapping and check for underflow/overflow in Green Channel
	LUT(channels[1], lookUpTable, channels[1]);
	// Apply interpolation and create look up table//
	interPolation(lut, fullRange, rCurve, originalR);
	// Apply mapping and check for underflow/overflow in Red Channel
	LUT(channels[2], lookUpTable, channels[2]);
	//merge the channels//
	Mat output;
	// Merge the channels 
	merge(channels, output);

	return output;

}
Mat InstagramFilters::moonFilter() {
	//Enhance the channel for any image BGR or HSV etc
	Mat img = source.clone();
	float origin[] = { 0, 15, 30, 50, 70, 90, 120, 160, 180, 210, 255 };
	float Curve[] = { 0, 0, 5, 15, 60, 110, 150, 190, 210, 230, 255 };

	// Create a LookUp Table
	float fullRange[256];
	int i;

	for (i = 0; i<256; i++)
	{
		fullRange[i] = (float)i;
	}

	Mat lookUpTable(1, 256, CV_8U);
	uchar* lut = lookUpTable.ptr();

	// Apply interpolation and create look up table
	interPolation(lut, fullRange, Curve, origin);

	// Applying the mapping to the L channel of the LAB color space
	Mat labImage;
	cvtColor(img, labImage, COLOR_BGR2Lab);

	// Splitting the channels
	vector<Mat> channels(3);
	split(labImage, channels);

	LUT(channels[0], lookUpTable, channels[0]);
	merge(channels, labImage);

	cvtColor(labImage, img, COLOR_Lab2BGR);

	Mat output = adjustSaturation(img, 0.01);

	return output;


}
Mat InstagramFilters::X_Pro2Filter() {
	//Enhance the channel for any image BGR or HSV etc
	Mat img = source.clone();
	//Now we need to Apply the Vignette//
	// Applying a vignette with some radius
	img = Vignette(img,3);
	// Specifying the x-axis for mapping
	float originalR[] = { 0, 42, 105, 148, 185, 255 };
	float originalG[] = { 0, 40, 85, 125, 165, 212, 255 };
	float originalB[] = { 0, 40, 82, 125, 170, 225, 255 };

	// Specifying the y-axis for mapping
	float rCurve[] = { 0, 28, 100, 165, 215, 255 };
	float gCurve[] = { 0, 25, 75, 135, 185, 230, 255 };
	float bCurve[] = { 0, 38, 90, 125, 160, 210, 222 };

	// Splitting the channels
	vector<Mat> channels(3);
	split(img, channels);

	// Create a LookUp Table
	float fullRange[256];
	int i;

	for (i = 0; i<256; i++)
	{
		fullRange[i] = (float)i;
	}

	Mat lookUpTable(1, 256, CV_8U);
	uchar* lut = lookUpTable.ptr();
	// Apply interpolation and create look up table
	interPolation(lut, fullRange, bCurve, originalB);

	// Apply mapping and check for underflow/overflow in Red Channel
	LUT(channels[0], lookUpTable, channels[0]);

	// Apply interpolation and create look up table
	interPolation(lut, fullRange, gCurve, originalG);

	// Apply mapping and check for underflow/overflow in Blue Channel
	LUT(channels[1], lookUpTable, channels[1]);

	// Apply interpolation and create look up table
	interPolation(lut, fullRange, rCurve, originalR);

	// Apply mapping and check for underflow/overflow in Blue Channel
	LUT(channels[2], lookUpTable, channels[2]);

	Mat output;
	// Merge the channels 
	merge(channels, output);
	// Adjusting the contrast a bit - just for fun!
	output = adjustContrast(output, 1.2);
	return output;
}
void InstagramFilters::interPolation(uchar* lut,float * fullRange,float * curve,float* originalValue) {
	int i;
	for (i = 0; i < 256; i++)
	{
		int j = 0;
		float a = fullRange[i];
		while (a > originalValue[j])
		{
			j++;
		}
		if (a == originalValue[j])
		{
			lut[i] = curve[j];
			continue;
		}
		float slope = ((float)(curve[j] - curve[j - 1])) / (originalValue[j] - originalValue[j - 1]);
		float constant = curve[j] - slope * originalValue[j];
		lut[i] = slope * fullRange[i] + constant;
	}
}
Mat InstagramFilters::adjustSaturation(Mat original, float saturationScale)
{
	Mat hsvImage;
	// Convert to HSV color space
	cv::cvtColor(original, hsvImage, COLOR_BGR2HSV);

	// Convert to float32
	hsvImage.convertTo(hsvImage, CV_32F);

	vector<Mat>channels(3);
	// Split the channels
	split(hsvImage, channels);

	// Multiply S channel by scaling factor 
	channels[1] = channels[1] * saturationScale;

	// Clipping operation performed to limit pixel values between 0 and 255
	min(channels[1], 255, channels[1]);
	max(channels[1], 0, channels[1]);

	// Merge the channels 
	merge(channels, hsvImage);

	// Convert back from float32
	hsvImage.convertTo(hsvImage, CV_8UC3);

	Mat imSat;
	// Convert to BGR color space
	cv::cvtColor(hsvImage, imSat, COLOR_HSV2BGR);

	return imSat;
}
Mat InstagramFilters::Vignette(Mat source,float vignetteScale) {
	Mat img = source.clone();
	int rows = img.rows;
	int cols = img.cols;
	//computing the kernel size from the Image Dimensions,
	//This step is important as the Gaussain Kernel will be Completely be applied to Entire Image, thus we need a Gaussian Matrix
	//of the Same Dimensions as that of the Original Matrix//
	int k = std::min(rows, cols) / vignetteScale;
	/*cv::getGaussianKernel is an OpenCV function which gives the gaussian filter
	coefficients. It takes three parameters: Ksize (or kernel size) which should be odd , sigma and ktype (or kernel type) which
	can be either float32 or float64 . It returns a ksize * 1 matrix of coefficients.
	Here i varies from 0 to ksize-1
	After getting the two kernels, the transpose of the X kernel is multiplied with the
	Y kernel*/
	// Create a kernel to get the halo effect
	Mat gaussianX = getGaussianKernel(cols, k);
	Mat gaussianY = getGaussianKernel(rows, k);
	Mat gaussianX_Transpose;
	transpose(gaussianX, gaussianX_Transpose);
	Mat gaussianMat = gaussianY*gaussianX_Transpose;//creating the Bigger Kernel from two X and Y vectors Matrix//
	//Normalize the Kernel//
	Mat mask;
	normalize(gaussianMat, mask, 0, 1, NORM_MINMAX);
	//Apply the halo to the L channel of the image//
	Mat yCRCBImage;
	cvtColor(img, yCRCBImage, CV_BGR2YCrCb);
	//convert the Mask to float32//
	yCRCBImage.convertTo(yCRCBImage, CV_32F);
	mask.convertTo(mask, CV_32F);
	//Split the Channels//
	vector<Mat> channels(3);
	split(yCRCBImage, channels);
	// Apply the mask to the channel 0 of ycbImage 
	channels[0] += channels[0].mul(mask);
	channels[0] /= 2;
	// Merge the channels 
	merge(channels, yCRCBImage);

	// Convert back from float32
	yCRCBImage.convertTo(yCRCBImage, CV_8UC3);
	cvtColor(yCRCBImage, img, COLOR_YCrCb2BGR);
	//imshow("vignette applied", img);
	return img;
}
Mat InstagramFilters::adjustContrast(Mat original, float alpha)
{
	Mat ycbImage;

	// Convert to YCrCb color space
	cv::cvtColor(original, ycbImage, COLOR_BGR2YCrCb);

	// Convert to float32
	ycbImage.convertTo(ycbImage, CV_32F);

	vector<Mat>channels(3);
	// Split the channels
	split(ycbImage, channels);

	// Scale the Ychannel
	channels[0] = channels[0] * alpha;

	// Clipping operation performed to limit pixel values between 0 and 255
	min(channels[0], 255, channels[0]);
	max(channels[0], 0, channels[0]);

	// Merge the channels 
	merge(channels, ycbImage);

	// Convert back from float32
	ycbImage.convertTo(ycbImage, CV_8UC3);

	Mat contrastImage;
	// Convert back to BGR
	cv::cvtColor(ycbImage, contrastImage, COLOR_YCrCb2BGR);

	return contrastImage;
}