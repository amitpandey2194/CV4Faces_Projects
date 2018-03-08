#ifndef AP_Common_Functions_H
#define AP_Common_Functions_H

//Include all the OpenCV libraries Needed for this Header
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include<string>
using namespace std;
using namespace cv;
class CommonFunctions{
    /*
    This class contains the declarations of the most common functions that we will use all the time:
    eg: reading image, display, check for valid input etc.
    */
public:
	//this facilitates the reading and error check process while reading and returns read image
    const Mat & read_D_Image(const string &);

	//Just for the Display Purpose
    void display( const Mat&,const string &) const;

	//Resizing the Image with the supplied scale factors and the interpolation method//
	const Mat& resize_D_Image(const Mat &, float,float,int);

	//Crop the Image based on the supplied pixel range//
	const Mat& crop_D_Image(const Mat &, const Range &,const Range &);

	//Convert the DataTypeof the Supplied Image//
	const Mat & convertDataType_RGB(const Mat &,const int);





private:

};

#endif //AP_Common_Functions_H