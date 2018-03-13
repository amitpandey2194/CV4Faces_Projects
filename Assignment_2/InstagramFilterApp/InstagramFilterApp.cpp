// InstagramFilterApp.cpp : Defines the entry point for the console application.
//


#include <opencv2\imgproc.hpp>
#include<opencv2\highgui.hpp>
#include <iostream>
#include <vector>
#include<string>
#include "Declarations.h"
using namespace std;
using namespace cv;
Mat source;

int main(int argc,const char* argv[])
{
	string filename;
	if (argc < 2) {
		cout << "Please provide the file path in the command window" << endl;
		return 0;
	}
	filename = argv[1];//getting the file name in the program//
	source = imread(filename,CV_LOAD_IMAGE_COLOR);//reading the image in to a externally globally declared Mat object//
	if (source.empty()) {
		cout << "Please provide valid file path" << endl;
		return 0;
	}
	imshow("Test", source);
	InstagramFilters obj;
	obj.trackbarFunction();
	
	waitKey(0);
    return 0;
}

