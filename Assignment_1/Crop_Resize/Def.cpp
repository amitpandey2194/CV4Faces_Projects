#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include<stdio.h>
#include "Dec.h"
using namespace std;
using namespace cv;
Point startPoint, EndPoint;
Point tempStartPoint, tempEndPoint;
Mat croppedImage;
void on_mouse(int ev, int x, int y, int flags, void* obj)
{

	Crop_Resize* app = static_cast<Crop_Resize*>(obj);
	if (app)
		app->clickAndCrop(ev,x,y);
}

void Crop_Resize::clickAndCrop(int event,int x,int y) {
	// Record left (x,y) on left click and set cropping to true
	
	if (event == EVENT_LBUTTONDOWN)
	{
		startPoint = (Point(x, y));
	}
	// Mark end of cropping
	// Record ending (x,y)
	else if (event == EVENT_LBUTTONUP)
	{
		EndPoint = (Point(x, y));
		// Draw rectangle of interest
		rectangle(tempImage, startPoint, EndPoint, Scalar(0, 255, 0), 2);		
		imshow(imageName, tempImage);
	}
	if (imageName == "image2bcropped") {
		tempEndPoint = EndPoint;
		tempStartPoint = startPoint;
	}
}
void Crop_Resize::ROISelection(string nameOftheWindow, Mat & image) {
	namedWindow(nameOftheWindow);
	cout << "IMportant:draw the ROI from any TopLEft Point" << endl;
	setMouseCallback(nameOftheWindow, on_mouse,this);//friend function directly called here
	cout<<"After cropping the image hit key 'c' "<<endl;
	//imshow("mainImage", mainImage);
	while (1)
	{
		// Display image and wait for a key press
		imshow(nameOftheWindow, image);
		char key = waitKey(1);
		// if the 'c' key is pressed, break from the loop
		if (key == 'c')
			break;
	}
	if (nameOftheWindow == "image2bcropped")
		extractTheCroppedPart();//extract the image only after the region of interest is marked//
	else if (nameOftheWindow == "mainImage")
		mainImageROI();//extract the image only after the region of interest is marked//
	else
		cout << "somethingElse" << endl;
}
void Crop_Resize::extractTheCroppedPart() {
	cout << "x:" << startPoint.x << "y:" << startPoint.y << endl;
	cout << "x:" << EndPoint.x << "y:" << EndPoint.y << endl;
	//here first we give location of y i.e. range of height and then the range of width i.e. x//
	croppedImage =tempImage(Range(startPoint.y, EndPoint.y),Range(startPoint.x, EndPoint.x));
	imshow("croppedImage", croppedImage);
	
}
void Crop_Resize::mainImageROI() {
	int heightROI_MainImage = EndPoint.y - startPoint.y;
	int widthROI_MainImage = EndPoint.x - startPoint.x;
	int height_CroppedImage = tempEndPoint.y - tempStartPoint.y;
	int width_CroppedImage = tempEndPoint.x - tempStartPoint.x;
	double scaleX = widthROI_MainImage / (width_CroppedImage*1.0);
	double scaleY = heightROI_MainImage / (height_CroppedImage*1.0);
	/*cout << "mainImage x:" << startPoint.x << "mainImage y:" << startPoint.y << endl;
	cout << "mainImage x:" << EndPoint.x << "mainImage y:" << EndPoint.y << endl;
	cout << "tempx:" << tempStartPoint.x << "tempy:" << tempStartPoint.y << endl;
	cout << "tempx:" << tempEndPoint.x << "tempy:" << tempEndPoint.y << endl;
	cout << heightROI_MainImage << endl;
	cout << widthROI_MainImage << endl;
	cout << height_CroppedImage << endl;
	cout << width_CroppedImage << endl;	
	cout << scaleX << endl;
	cout << scaleY << endl;*/
	Mat resizedCroppedImage;
	resize(croppedImage, resizedCroppedImage, Size(), scaleX, scaleY, INTER_LINEAR);
	imshow("resizedCroppedImage",resizedCroppedImage);
	///////////////////////////////////////////////////////////
	resizedCroppedImage.copyTo(finalOutput(Range(startPoint.y, EndPoint.y), Range(startPoint.x, EndPoint.x)));
	imshow("finalOutput", finalOutput);
}
