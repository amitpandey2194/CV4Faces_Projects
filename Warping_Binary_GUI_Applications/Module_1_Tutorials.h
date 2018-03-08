#ifndef AP_Module_1_Tutorials_H
#define AP_Module_1_Tutorials_H

//Include all the OpenCV libraries Needed for this Header
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>
#include <string>
using namespace std;
using namespace cv;
class Module_1_Tutorials{
    /*
        This Class will contain all the declarations of the Functions that
        Needs to be implemented in the Module_1 of for the Course of "Computer Vision for Faces"
        Definitions of these functions is provided in a separate File. 
    
    */
public:
	//Variables and Mat Files Intializations//
	const Mat inputImage; Mat greyInputImage;
	////////////////////////////////////////////////////////
	string windowName		    = "Binary Operations"; 
	string windowName_4_Warping = "Warping Operations";
	///////////////////////////////////////////////////////
	int threshValue               = 0;	   const int maxThreshValue     = 255; int thresholdType    = 3;    int const maxType  = 4;
	int const max_BINARY_value    = 255;  int const maxNumStatesOfBinOp = 5;   int stateForBinaryOp = 0; int stateForWarpingOp = 0; 
	int const maxNumStatesOfWarpingOp = 5;
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	Module_1_Tutorials(); //constructor//
	Module_1_Tutorials(const Mat &); //constructor//
	~Module_1_Tutorials();//destructor//
//Member Functions//
	void warping_Images_GUI_Caller();//this function will be able to call other warping functions
	static void main_Warping_Operations_Caller(int,void*);
	const  Mat & rotate_An_Image(const Mat&, const Point2i&,const double,const double);
	const  Mat & any_Affine_Transform(const Mat&, const Mat&, const double, const double);
	const  Mat & get_Affine_Transform_Matrix(const vector<Point2f>&,const vector<Point2f>&);
	const  Mat & draw_Circle(Mat &, const Point &,const double, const int,const int,const Scalar);
	const  Mat & draw_Line(Mat &, const Point &,const Point&,const int lineThickness = 1, const Scalar colorChoice = (0, 255, 0));
	const  Mat & draw_Rectangle(Mat &,const Point &, const Point &,const int,const int,const Scalar);
	const  Mat & draw_Ellipse(Mat&,const Point &,const Size,const int,const int,const int,const int,const int,const Scalar);
	const  Mat & draw_Polygon(Mat &,const Point **,const int*,const int,const Scalar,const int);

	//Function for the GUI of the Binary Operation//
	void binary_Operation_GUI_Caller();	//this function will be able to call createtrackbar function in OpenCV.
	static void thresholding(int,void*);// function to perform thresholding
	static void opening     (int, void*);// function to perform Opening
	static void closing     (int, void*);// function to perform Closing
	static void erosion     (int, void*);// function to perform Erosion
	static void dilation    (int, void*);// function to perform Dilation//
	// this function will be called by each trackbar based on the value of stateForBinaryOp variable
	static void main_Binary_Operation(int, void*);
private:

};
#endif //AP_Module_1_Tutorials_H