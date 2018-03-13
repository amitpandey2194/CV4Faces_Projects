#pragma once
#include <opencv2\imgproc.hpp>
#include<opencv2\highgui.hpp>
#include <iostream>
#include <vector>
using namespace std;
using namespace cv;
extern Mat source;
class InstagramFilters {
public:
	void trackbarFunction();
	//Functions for the Trackbars//
	//void trackBarCallingFunction(int,void*);
	/*friend void clarendonFilter(int,void*);
	friend void kelvinFilter(int, void*);
	friend void moonFilter(int, void*);
	friend void X_Pro2Filter(int, void*);
	friend void pencilSketchFilter(int, void*);
	friend void haloFilter(int, void*);*/
	//Functions for the filter Definition//
	Mat clarendonFilter();
	Mat kelvinFilter();
	Mat moonFilter();
	Mat X_Pro2Filter();
	//Common Interpolation Function//
	void interPolation(uchar*,float*,float*,float*);
	//adjust saturation Function//
	Mat adjustSaturation(Mat,float);
	//Vignette Function for Halo Effect//
	Mat Vignette(Mat,float);
	Mat adjustContrast(Mat,float);
	
};