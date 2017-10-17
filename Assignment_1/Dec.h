#pragma once
#ifndef DEC_H
#define DEC_H
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include<stdio.h>
using namespace std;
using namespace cv;
extern Mat image2bCropped, mainImage,tempImage,finalOutput;//made these extern as to use them freely throughout all the three linked files//
extern string imageName;
class Crop_Resize {
public:
	friend void on_mouse(int ev, int x, int y, int, void* obj);
	void clickAndCrop(int, int, int);
	void ROISelection(string,Mat &);//this function helps in selecting the ROI
	void extractTheCroppedPart();//this function extracts the croppedROI
	void mainImageROI();//this function helps in selecting the ROI of the main image and then place it at apporpriate location and size//
	
};
#endif
