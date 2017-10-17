// Crop_Resize.cpp : Defines the entry point for the console application.
//

#pragma warning (disable : 4996)
#ifdef _WIN32 
#define _CRT_SECURE_NO_WARNINGS
#endif
#include<stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include "Dec.h"


using namespace std;
using namespace cv;

Mat image2bCropped, mainImage,tempImage,finalOutput;
string imageName;
int main(int argc, const char* argv[])
{
	
	//string for the filename//
	string filename_1, filename_2;
	if (argc!=3) {
		cout << "Please Provide Valid Input via Command Line as given below" << endl;
		cout << "source.exe path_of_the_first_image path_of_the_second_image" << endl;
		return 0;//terminate the program//
	}
	//Getting filename from the command line//
	filename_1 = argv[1];
	filename_2 = argv[2];
	//reading the images from the path provided by the user, in it's colored form//
	mainImage = imread(filename_1,CV_LOAD_IMAGE_COLOR);
	image2bCropped = imread(filename_2, CV_LOAD_IMAGE_COLOR);
	//cloning original mainImage//
	finalOutput = mainImage.clone();

	//Now I want the user to get the opportunity to be able to crop the region of interest from the images and place it on the other image//
	//just make sure that the size of the cropped image shouldn't be greater than the image on which we need to replace//
	Crop_Resize obj;
	imageName = "image2bcropped";
	tempImage = image2bCropped.clone();
	obj.ROISelection(imageName,tempImage);
	////selecting the mainImage ROI///
	imageName = "mainImage";
	tempImage = mainImage.clone();
	obj.ROISelection(imageName, tempImage);	
	waitKey(0);
	
    return 0;
}

