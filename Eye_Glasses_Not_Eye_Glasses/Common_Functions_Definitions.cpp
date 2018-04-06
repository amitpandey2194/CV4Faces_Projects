#include "Common_Functions.h"
#include <vector>
using namespace std;
using namespace cv;


const Mat & CommonFunctions::read_D_Image(const string & imagepath)
{
	/*
		The main work of this Function is to Just read the Image Successfully and Halt the Program if there is error in reading	
	*/
	const static Mat InputImage = imread(imagepath);//the address of this variable is used as reference when returning
	//Error Check//
	if (InputImage.empty())
	 {
		printf("Image not read Successfully! Please Check the path and try again");
		abort();
	}
	else 
	{
		/*
		cout << "Height is:" << InputImage.rows << endl;
		cout << "Width is:" << InputImage.cols << endl;*/
		printf("Image Read Successfully!");
	}
    return InputImage;
}

void CommonFunctions::display(const Mat& ImageForDisplay,const string & nameOftheWindow) const 
{
	/*
		The main Function of this image is to Display the Input Image, nothing else
	*/
	namedWindow(nameOftheWindow, WINDOW_AUTOSIZE);
	imshow(nameOftheWindow,ImageForDisplay);
}

const Mat & CommonFunctions::resize_D_Image(const Mat & inputImage,float scaleX, float scaleY,int interPolationCode) 
{
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
	//imshow(moduleOneObject.windowName_4_Warping, resizedImage);
	return resizedImage;
}

void CommonFunctions::crop_D_Image(const Mat & inputImage, Mat & croppedImage,const Range& start, const Range & end) 
{
	/*
	This Function crops the Image with the supplied start and end range
	NOTE: you need to specify pixels postions in the start and end range.
	*/
	croppedImage=inputImage(start,end);// Crop operation// hear just the header of the croppedImage is changed, data is not copied
	//imshow(moduleOneObject.windowName_4_Warping, croppedImage);
}

const Mat & CommonFunctions::convertDataType_RGB(const Mat & inputImage,const int code_Int_Or_Float) 
{
	/*
		In this program, we will use OpenCV convertTo function to convert the datatype of the matrix used to store the 
		image from integer to float as well as change the range of the values from 0-255 to 0-1 and vice versa. 
		This program will not give any different output but is crucial for other applications where floating point numbers 
		are required.
	
	*/
	static Mat convertedImage;
	double scale = 1 / 255.0, shift = 0;
	if (inputImage.type() == CV_8UC3 && code_Int_Or_Float == 1)
	{
		inputImage.convertTo(convertedImage, CV_32FC3, scale, shift);
	}
	else if (inputImage.type() ==CV_32FC3 && code_Int_Or_Float == 0) 
	{
		inputImage.convertTo(convertedImage, CV_8UC3, 1/scale, shift);
	}
	else
	{
		cout << "We cannot convert this image" << endl;
	}
	return convertedImage;
}

void CommonFunctions::getNamesOfFiles(string dirName, vector<string> & imageNames)
{

	DIR *dir; //pointer to an open directory
    struct dirent  *entry;//stuff in  the directory
    //open+
    dir=opendir(dirName.c_str());
    if (!dir)
    {
        cout<<"Directory not found"<<endl;
        return;
    }
    //2. read
	string tempDirName=dirName;
    while ((entry=readdir(dir))!=NULL)
    {
		//this condition helps eliminate the "." and ".." strings which are read by default indicating the current directory
        if(strcmp(entry->d_name,".") == 0 | strcmp(entry->d_name, "..") == 0)
        {
            continue;
        }
        //cout<<dirName.append(entry->d_name)<<endl;		
		imageNames.push_back(dirName.append(entry->d_name));

		//reintializing the directory name 
		dirName=tempDirName;       
    }
	closedir(dir);
}


void CommonFunctions::getTheCroppedEyeImage(dlib::full_object_detection & landmarks,cv::Mat & inputImage,cv::Mat & croppedImage)
{
	float topCornerPointX	=landmarks.part(0).x();
	float topCornerPointY	=min(landmarks.part(19).y(),landmarks.part(24).y());
	float bottomCornerPointX=landmarks.part(16).x();
	float bottomCornerPointY=landmarks.part(29).y();

	cout<<topCornerPointX<<" "<<topCornerPointY<<" "<<bottomCornerPointX<<" "<<bottomCornerPointY<<endl;
	//first specify the rows and then the column's range
	crop_D_Image(inputImage,croppedImage,cv::Range(topCornerPointY,bottomCornerPointY),cv::Range(topCornerPointX,bottomCornerPointX));
	resize(croppedImage,croppedImage,cv::Size(96,32),0,0,CV_INTER_CUBIC);
}



