#include "Module_1_Tutorials.h"
#include "Common_Functions.h"

/*
    This File contains all the necessary definitions of Functions and variables Required to run the Entire Project of Module_1_Tutorials.
    We have included the necessary the header files, which needs definitions 
*/
CommonFunctions commonObject;//object of the other class
Module_1_Tutorials::Module_1_Tutorials() {};//constructor
Module_1_Tutorials::Module_1_Tutorials(const Mat & image):inputImage(image){
	greyInputImage = Mat(inputImage.rows, inputImage.cols, CV_8UC1);
	cvtColor(inputImage, greyInputImage, CV_BGR2GRAY);//conversion to grey color
}//constructor definition//
Module_1_Tutorials::~Module_1_Tutorials() {}//destructor definition//

const Mat & Module_1_Tutorials::rotate_An_Image(const Mat & inputImage,const Point2i& center,const double angle, const double scale) {
	/*
		This Function is written to facilitate the work of rotating the image using function from OpenCV library
		getRotationMatrix2D(center,angle,scale) & warpAffine(source,result,rotationMatrix,Size())
	*/
	Point2f centerF = center;
	static Mat rotatedImage; // matrix in which the resulting image after rotation will be placed
	Mat rotation2DMatirx;
	/*
		The getRotationMatrix2D function takes the following parameters:
		Center: point about which rotation will occur
		rotationAngle: angle by which rotation is occurring
		Scale : an optional scaling factor
	*/
	rotation2DMatirx = getRotationMatrix2D(centerF, angle, scale); //getting the rotation matrix ready for warpAffine()
	
    //// Rotate the source and store in rotatedImage
	/*
		In OpenCV, if you want to apply an affine transform to the entire image you can use the function warpAffine
	*/
	warpAffine(inputImage, rotatedImage, rotation2DMatirx, Size(inputImage.rows, inputImage.cols),INTER_LINEAR, BORDER_REFLECT_101);
	imshow(this->windowName_4_Warping,rotatedImage);
	return rotatedImage;

}

const Mat & Module_1_Tutorials::any_Affine_Transform(const Mat& inputImage, const Mat & warpingMatrix, const double scaleX, const double scaleY) {
	/*
		This Function Facilitates the work of performing the affine transforms on the entire image based on the supplied warpingMatrix
	*/
	static Mat transformedImage;//image to be returned
	warpAffine(inputImage, transformedImage, warpingMatrix, Size(inputImage.rows*scaleY, inputImage.cols*scaleX),INTER_LINEAR,BORDER_REFLECT_101 );
	imshow(this->windowName_4_Warping, transformedImage);//displaying the transformed image
	return transformedImage;
}

const Mat & Module_1_Tutorials::get_Affine_Transform_Matrix(const vector<Point2f> &triangle_1, const vector<Point2f> &triangle_2) {
	/*
		The work of this function is to return a 2D Affine Matrix which will be genrated with help of two set of 3 points coming from the original
		and the transformed image. These 6 points will be passed to getAffineTransform function inorder to get the 2Daffine matrix
		Note: Make sure the points are not collinear in either of the images
	*/
	static Mat affine2D_Matrix = getAffineTransform(triangle_1, triangle_2);

	return affine2D_Matrix;
}

const Mat & Module_1_Tutorials::draw_Line(Mat & inputImage,const Point &start,const Point &end,
											const int lineThickness,const Scalar colorChoice) {
/*
	This Function is callled to draw a line on the supplied image based on the arguments given
*/
	static Mat lineDrawnImage = inputImage.clone();//cloning the image copies the header as well as the data to the Mat file on the left
	line(lineDrawnImage,start,end,colorChoice,lineThickness,CV_AA);
	return lineDrawnImage;
}

const Mat & Module_1_Tutorials::draw_Circle(Mat & inputImage, const Point &center, const double radius , 
															const int lineThickness=1,const int lineType=8, const Scalar colorChoice= (0, 255, 0)) {
	/*
	This Function is callled to draw a circle on the supplied image based on the arguments given
	*/
	static Mat circleDrawnImage = inputImage.clone();//cloning the image copies the header as well as the data to the Mat file on the left
	circle(circleDrawnImage, center, radius, colorChoice, lineThickness,lineType);
	return circleDrawnImage;
}


const Mat & Module_1_Tutorials::draw_Rectangle(Mat & inputImage, const Point &vertex, const Point &oppVertex, 
											const int lineThickness=1, const int lineType=8,const Scalar colorChoice= (0, 255, 0)) {
	/*
	This Function is callled to draw a ellipse on the supplied image based on the arguments given
	*/
	static Mat rectangleDrawnImage = inputImage.clone();//cloning the image copies the header as well as the data to the Mat file on the left
	rectangle(rectangleDrawnImage, vertex, oppVertex, colorChoice, lineThickness, lineType);
	return rectangleDrawnImage;
}

const Mat & Module_1_Tutorials::draw_Ellipse(Mat & inputImage, const Point & centerOfEllipse, const Size axes, 
						const int rotationAngle, const int startingAngle,const int endingAngle,
						const int lineThickness=1,const int lineType=8,const Scalar colorChoice=(0, 255, 0)) {
	/*
	This Function is callled to draw an ellipse on the supplied image based on the arguments given
	*/
	static Mat ellipseDrawnImage = inputImage.clone();//cloning the image copies the header as well as the data to the Mat file on the left
	ellipse(ellipseDrawnImage, centerOfEllipse, axes,rotationAngle,startingAngle,endingAngle,colorChoice,lineThickness, lineType);
	return ellipseDrawnImage;
}

const Mat & Module_1_Tutorials::draw_Polygon(Mat &inputImage, const Point** ppt,const int* npt, const int contours, 
										const Scalar colorChoice=(0,255,0), const int lineType=8) {
	/*
	This Function is callled to draw a Polygon on the supplied image based on the arguments given
	*/
	static Mat polygonDrawnImage = inputImage.clone();
	fillPoly(polygonDrawnImage,ppt,npt,contours,colorChoice,lineType);
	return polygonDrawnImage;
}
void Module_1_Tutorials::warping_Images_GUI_Caller() {
	/*
	this is a helper function which would help in creating the buttons
	*/
	//cout << this->windowName_4_Warping << endl;
	// Create a window to display results
	namedWindow(this->windowName_4_Warping, CV_WINDOW_AUTOSIZE);
	imshow(this->windowName_4_Warping, this->inputImage);
	createTrackbar("Select The Warping Op", this->windowName_4_Warping, &this->stateForWarpingOp, 
																this->maxNumStatesOfWarpingOp, main_Warping_Operations_Caller, this);
}

void Module_1_Tutorials::main_Warping_Operations_Caller(int,void* moduleOneObject) {
	Module_1_Tutorials *objectPointer = static_cast<Module_1_Tutorials*>(moduleOneObject);
	Mat warpMatrix; 
	switch (objectPointer->stateForWarpingOp) {
	case 1:
		objectPointer->rotate_An_Image(objectPointer->inputImage,
										Point2i(objectPointer->inputImage.cols / 2, objectPointer->inputImage.rows / 2), 40, 1);
		break;
	case 2:
		warpMatrix = (Mat_<double>(2, 3) << 1.2, 0.2, 2, -0.3, 1.3, 1);
		objectPointer->any_Affine_Transform(objectPointer->inputImage, warpMatrix, 1.5, 1.4);
		break;
	case 3:
		commonObject.resize_D_Image(objectPointer->inputImage,0.6, 0.6, 3);
		break;
	case 4:
		commonObject.crop_D_Image(objectPointer->inputImage, Range(200, 500), Range(40, 200));
		break;
	default:
		imshow(objectPointer->windowName, objectPointer->greyInputImage);

	}
}






void Module_1_Tutorials::binary_Operation_GUI_Caller() {
	/*
	this is a helper function which would help in creating a trackbar for binary operations
	*/
	
	//cout << this->windowName << endl;
	// Create a window to display results
	namedWindow(this->windowName, CV_WINDOW_AUTOSIZE);
	imshow(this->windowName, this->greyInputImage);
	createTrackbar("Select The Binary Op",this->windowName,&this->stateForBinaryOp,this->maxNumStatesOfBinOp,main_Binary_Operation,this);
}

void Module_1_Tutorials::thresholding(int state, void * moduleOneObject) {
	//Value of the pixel greater than threshold will become 255 and pixels lesser than threshValue will become equal to threshValue 
	Module_1_Tutorials *objectPointer = static_cast<Module_1_Tutorials*>(moduleOneObject);
	Mat imageToBeManipulated;//image after thresholding
	threshold(objectPointer->greyInputImage, imageToBeManipulated,objectPointer->threshValue, objectPointer->max_BINARY_value, objectPointer->thresholdType);
	imshow(objectPointer->windowName, imageToBeManipulated);	
}
void Module_1_Tutorials::opening(int state, void * moduleOneObject) {
	
	//Small Blobs can be removed by performing erosion first and then dilation. this is called morphological opening
	int iterations = 3;

	//We also need to create structuring element that is going to be used  for opening operation
	int openingSize = 3;

	//Let us create a structuring element//
	Mat structElement = getStructuringElement(MORPH_ELLIPSE,Size(2*openingSize+1, 2 * openingSize + 1),Point(openingSize,openingSize));

	Module_1_Tutorials *objectPointer = static_cast<Module_1_Tutorials*>(moduleOneObject);
	Mat imageMorphed; //image after morphing
	morphologyEx(objectPointer->greyInputImage, imageMorphed, MORPH_OPEN,structElement,Point(-1,-1),iterations);
	imshow(objectPointer->windowName, imageMorphed);
	
}
void Module_1_Tutorials::closing(int state, void * moduleOneObject) {
	//Small Holes can be filled by performing dilation first and then erosion. this is called morphological closing
	int iterations = 3;

	//We also need to create structuring element that is going to be used  for closing operation
	int closingSize = 3;

	//Let us create a structuring element//
	Mat structElement = getStructuringElement(MORPH_ELLIPSE, Size(2 * closingSize + 1, 2 * closingSize + 1), Point(closingSize, closingSize));

	Module_1_Tutorials *objectPointer = static_cast<Module_1_Tutorials*>(moduleOneObject);
	Mat imageMorphed; //image after morphing
	morphologyEx(objectPointer->greyInputImage, imageMorphed, MORPH_CLOSE, structElement, Point(-1, -1), iterations);
	imshow(objectPointer->windowName, imageMorphed);
	
}
void Module_1_Tutorials::erosion(int state, void * moduleOneObject) {
	//We also need to create structuring element that is going to be used  for closing operation
	int erosionSize = 6;

	//Let us create a structuring element//
	Mat structElement = getStructuringElement(MORPH_CROSS, Size(2 * erosionSize + 1, 2 * erosionSize + 1), Point(erosionSize, erosionSize));

	Module_1_Tutorials *objectPointer = static_cast<Module_1_Tutorials*>(moduleOneObject);
	Mat imageErosion; //image after Dilating
	erode(objectPointer->greyInputImage, imageErosion, structElement);
	imshow(objectPointer->windowName, imageErosion);
	
}
void Module_1_Tutorials::dilation(int state, void * moduleOneObject) {
	//We also need to create structuring element that is going to be used  for closing operation
	int dilationSize = 6;

	//Let us create a structuring element//
	Mat structElement = getStructuringElement(MORPH_CROSS, Size(2 * dilationSize + 1, 2 * dilationSize + 1), Point(dilationSize, dilationSize));

	Module_1_Tutorials *objectPointer = static_cast<Module_1_Tutorials*>(moduleOneObject);
	Mat imageDilated; //image after Dilating
	dilate(objectPointer->greyInputImage, imageDilated, structElement);
	imshow(objectPointer->windowName, imageDilated);
}

void Module_1_Tutorials::main_Binary_Operation(int,void *moduleOneObject) {
	Module_1_Tutorials *objectPointer = static_cast<Module_1_Tutorials*>(moduleOneObject);
	switch (objectPointer->stateForBinaryOp) {
	case 1:
		createTrackbar("Thresholding", objectPointer->windowName, &objectPointer->threshValue, objectPointer->maxThreshValue, thresholding, objectPointer);
		break;
	case 2:
		opening(0, objectPointer);//calling the opening function
		break;
	case 3:
		closing(0, objectPointer);//calling the closing function
		break;
	case 4:
		dilation(0, objectPointer);//calling the dilation function
		break;
	case 5:
		erosion(0, objectPointer);//calling the erosion function
		break;
	default:
		imshow(objectPointer->windowName, objectPointer->greyInputImage);

	}
	
}





