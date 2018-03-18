#include <stdio.h>
#include <iostream>
#include "Module_1_Tutorials.h"
#include "Common_Functions.h"
using namespace cv;
using namespace std;
int main(int argc,const char*argv[]){	

	CommonFunctions commonObject;
	const Mat & inputImage=commonObject.read_D_Image(argv[1]);// First argument will the File Path
	commonObject.display(inputImage,"InputImage");//Displaying the Image
	Module_1_Tutorials moduleObject(inputImage);
	/*Functionality 1 Testing*/
	
	/*
	const Mat & resizeImage = commonObject.resize_D_Image(inputImage, 0.6, 0.6,3);
	commonObject.display(resizeImage,"resizedImage");//Displaying the Image
	*/
	/*Functionality 2 Testing*/
	/*
	const Mat & croppedImage = commonObject.crop_D_Image(inputImage, Range(200,500), Range(40, 200));
	commonObject.display(croppedImage,"croppedImage");//Displaying the Image
	*/
	/*Functionality 3 Testing*/
	/*
	const Mat & rotatedImage=moduleObject.rotate_An_Image(inputImage, Point2i(inputImage.cols/2, inputImage.rows/2), 40, 1);
	commonObject.display(rotatedImage,"rotatedImage");//Displaying the Image
	*/
	/*Functionality 4 Testing*/
	/*
	Mat warpMatrix = (Mat_<double>(2,3)<<1.2,0.2,2,-0.3,1.3,1);
	const Mat & transformedImage = moduleObject.any_Affine_Transform(inputImage, warpMatrix, 1.5, 1.4);
	commonObject.display(transformedImage,"transformedImage");//Displaying the Image
	*/

	/*Functionality 5 Testing*/

	//cout << "The Height and Width are:"<<"("<<inputImage.rows<<","<<inputImage.cols<<")" << endl;
	/*
	vector<Point2f> triangle_1(3); vector<Point2f>triangle_2(3);
	NOTE: We can't go for the above declaration, as this intializes zero's based on the data type, then eventually when
	we pushback something, that thing gets appended after zero's for the given locations in the declaration.
	therefore we were getting the error......
	Interesting point about the vectors
	cout << triangle_1 << endl;
	*/
	// the reason for going with the below declaration is mentioned above//
	/*
	vector<Point2f> triangle_1; vector<Point2f>triangle_2;
	//Pushing in the 3 Coordinates from the InputImage (make sure they are non-collinear)
	triangle_1.push_back(Point2f(50,50)); triangle_1.push_back(Point2f(180, 140)); triangle_1.push_back(Point2f(150, 200));
	//Pushing in the 3 Coordinates from the transformedImage (make sure they are non-collinear)
	triangle_2.push_back(Point2f(72, 51)); triangle_2.push_back(Point2f(246, 129)); triangle_2.push_back(Point2f(222, 216));
	const Mat & affine_Transform_Matrix = moduleObject.get_Affine_Transform_Matrix(triangle_1,triangle_1);
	const Mat & transformedImage = moduleObject.any_Affine_Transform(inputImage,affine_Transform_Matrix, 1, 1);
	commonObject.display(transformedImage, "transformedImage");//Displaying the Image
	*/
	//Functionality 6 Testing//
	// Draw a filled Polygon
/*	Mat image = Mat::zeros(400, 400, CV_8UC3);
	int w = 400;
	// Create some points 
	Point rookPoints[1][20]; // the points are created by making an array of datatype Point of the dimensions 1*20
	rookPoints[0][0] = Point(w / 4.0, 7 * w / 8.0);
	rookPoints[0][1] = Point(3 * w / 4.0, 7 * w / 8.0);
	rookPoints[0][2] = Point(3 * w / 4.0, 13 * w / 16.0);
	rookPoints[0][3] = Point(11 * w / 16.0, 13 * w / 16.0);
	rookPoints[0][4] = Point(19 * w / 32.0, 3 * w / 8.0);
	rookPoints[0][5] = Point(3 * w / 4.0, 3 * w / 8.0);
	rookPoints[0][6] = Point(3 * w / 4.0, w / 8.0);
	rookPoints[0][7] = Point(26 * w / 40.0, w / 8.0);
	rookPoints[0][8] = Point(26 * w / 40.0, w / 4.0);
	rookPoints[0][9] = Point(22 * w / 40.0, w / 4.0);
	rookPoints[0][10] = Point(22 * w / 40.0, w / 8.0);
	rookPoints[0][11] = Point(18 * w / 40.0, w / 8.0);
	rookPoints[0][12] = Point(18 * w / 40.0, w / 4.0);
	rookPoints[0][13] = Point(14 * w / 40.0, w / 4.0);
	rookPoints[0][14] = Point(14 * w / 40.0, w / 8.0);
	rookPoints[0][15] = Point(w / 4.0, w / 8.0);
	rookPoints[0][16] = Point(w / 4.0, 3 * w / 8.0);
	rookPoints[0][17] = Point(13 * w / 32.0, 3 * w / 8.0);
	rookPoints[0][18] = Point(5 * w / 16.0, 13 * w / 16.0);
	rookPoints[0][19] = Point(w / 4.0, 13 * w / 16.0);

	const Point *ppt[1] = { rookPoints[0] };
	int npt[] = { 20 };
	const Mat & polygonDrawnImage = moduleObject.draw_Polygon(image,ppt,npt,1,Scalar(0,255,0),8);
	commonObject.display(polygonDrawnImage,"PolygonDrawnImage");
	*/
	
	moduleObject.binary_Operation_GUI_Caller();
	moduleObject.warping_Images_GUI_Caller();
	
	
	
	waitKey(0);
	return 0;
}