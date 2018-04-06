#pragma once
#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/objdetect.hpp"
#include <opencv2/ml.hpp>
#include <dlib/opencv.h>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing.h>
#include "dirent.h"
#include <vector>
using namespace std;

class image_Classification_SVM
{
  public:
    void preparingDataset(vector<string> &, vector<cv::Mat> &, vector<int> &, vector<cv::Mat> &, vector<int> &, int, double);
    /*Note image here is cropped in the dataset to directly to eyes
      Size of the image is 32*96 i.e. rows=32 and cols=96
    */


    void computeHogFeatures(vector<vector<float>>&, vector<cv::Mat>&);
    void convertVector2Matrix_4SVM(vector<vector<float>>&,cv::Mat &);
    void printSVMParameters(cv::Ptr<cv::ml::SVM>);
    cv::Ptr<cv::ml::SVM>svmIntializer(float,float);
    void svmTrainer(cv::Ptr<cv::ml::SVM>,cv::Mat &,vector<int>&);
    void svmPredict(cv::Ptr<cv::ml::SVM> svm, cv::Mat &, cv::Mat &);
    void svmEvaluation(cv::Mat&,float&,float &,vector<int>&);
    void testingViaVideo(); 
  private:
};
