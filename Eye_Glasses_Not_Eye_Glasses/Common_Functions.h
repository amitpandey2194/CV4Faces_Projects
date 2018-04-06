#ifndef AP_Common_Functions_H
#define AP_Common_Functions_H

//Include all the OpenCV libraries Needed for this Header
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <dlib/opencv.h>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing.h>
#include<string>
#include <vector>
#include "dirent.h"
using namespace std;

class CommonFunctions{
    /*
    This class contains the declarations of the most common functions that we will use all the time:
    eg: reading image, display, check for valid input etc.
    */
public:
	//this facilitates the reading and error check process while reading and returns read image
    const cv::Mat & read_D_Image(const string &);

	//Just for the Display Purpose
    void display( const cv::Mat&,const string &) const;

	//Resizing the Image with the supplied scale factors and the interpolation method//
	const cv::Mat& resize_D_Image(const cv::Mat &, float,float,int);

	//Crop the Image based on the supplied pixel range//
	void crop_D_Image(const cv::Mat &, cv::Mat&,const cv::Range &,const cv::Range &);

	//Convert the DataTypeof the Supplied Image//
	const cv::Mat & convertDataType_RGB(const cv::Mat &,const int);

	//Helper Function in reading the names of the file//

	void getNamesOfFiles(string,vector<string>&);

	//Crop the image based on the locations of the landmarks
	void getTheCroppedEyeImage(dlib::full_object_detection&,cv::Mat &,cv::Mat &);



private:

};

#endif //AP_Common_Functions_H