#include "Common_Functions.h"
#include "Module_1_Tutorials.h"

Module_1_Tutorials moduleOneObject;

const Mat & CommonFunctions::read_D_Image(const string & imagepath){
	/*
		The main work of this Function is to Just read the Image Successfully and Halt the Program if there is error in reading	
	*/
	const static Mat InputImage = imread(imagepath);//the address of this variable is used as reference when returning
	//Error Check//
	if (InputImage.empty()) {
		printf("Image not read Successfully! Please Check the path and try again");
		abort();
	}
	else {
		/*
		cout << "Height is:" << InputImage.rows << endl;
		cout << "Width is:" << InputImage.cols << endl;*/
		printf("Image Read Successfully!");
	}
    return InputImage;
}

void CommonFunctions::display(const Mat& ImageForDisplay,const string & nameOftheWindow) const {
	/*
		The main Function of this image is to Display the Input Image, nothing else
	*/
	namedWindow(nameOftheWindow, WINDOW_AUTOSIZE);
	imshow(nameOftheWindow,ImageForDisplay);
}

const Mat & CommonFunctions::resize_D_Image(const Mat & inputImage,float scaleX, float scaleY,int interPolationCode) {
	/*
		This Function resizes the Image with the supplied scale factors and the interpolation method
	*/
	/* Integer Corresponding to the interpolation Values
		INTER_NEAREST=0
		INTER_LINEAR=1
		INTER_CUBIC=2
		INTER_AREA=3		
	
	*/
	static Mat resizedImage; //New Mat file for resized image
	/* We can either specify the Size(, ) of the output to determine the height and width
		of the output or we can add the scaling factors and the Size will be calculated
		automatically. */
	resize(inputImage, resizedImage, Size(), scaleX, scaleY, interPolationCode);// calling up the CV resize function
	imshow(moduleOneObject.windowName_4_Warping, resizedImage);
	return resizedImage;
}

const Mat & CommonFunctions::crop_D_Image(const Mat & inputImage, const Range& start, const Range & end) {
	/*
	This Function crops the Image with the supplied start and end range
	NOTE: you need to specify pixels postions in the start and end range.
	*/
	
	static Mat croppedImage; //New Mat file for resized image
	croppedImage=inputImage(start,end);// Crop operation// hear just the header of the croppedImage is changed, data is not copied
	imshow(moduleOneObject.windowName_4_Warping, croppedImage);
	return croppedImage;
}

const Mat & CommonFunctions::convertDataType_RGB(const Mat & inputImage,const int code_Int_Or_Float) {
	/*
		In this program, we will use OpenCV convertTo function to convert the datatype of the matrix used to store the 
		image from integer to float as well as change the range of the values from 0-255 to 0-1 and vice versa. 
		This program will not give any different output but is crucial for other applications where floating point numbers 
		are required.
	
	*/
	static Mat convertedImage;
	double scale = 1 / 255.0, shift = 0;
	if (inputImage.type() == CV_8UC3 && code_Int_Or_Float == 1) {
		inputImage.convertTo(convertedImage, CV_32FC3, scale, shift);
	}
	else if (inputImage.type() ==CV_32FC3 && code_Int_Or_Float == 0) {
		inputImage.convertTo(convertedImage, CV_8UC3, 1/scale, shift);
	}
	else {
		cout << "We cannot convert this image" << endl;
	}
	return convertedImage;
}
