#include <iostream>
#include "image_Classification_SVM_dec.h"
#include "Common_Functions.h"
#include <string>
#include <vector>
#include "dirent.h"
using namespace std;

int main()
{
    CommonFunctions obj;
    image_Classification_SVM object;

    string dir_Name_1 = "C:/Users/amitp/Desktop/OpenCV_Course/cv4faces/data/images/glassesDataset/cropped_withGlasses2/";
    string dir_Name_2 = "C:/Users/amitp/Desktop/OpenCV_Course/cv4faces/data/images/glassesDataset/cropped_withoutGlasses2/";
    vector<string> imageNames_WithG;
    vector<string> imageNames_WithOutG;
    obj.getNamesOfFiles(dir_Name_1, imageNames_WithG);
    obj.getNamesOfFiles(dir_Name_2, imageNames_WithOutG);
    /*for(const auto &x:imageNames_WithG)
    {
        cout<<x<<endl;
    }*/
    //cout<<imageNames_WithG.size()<<endl;
    vector<cv::Mat> trainDataset;
    vector<int> trainLabels;
    vector<cv::Mat> testDataset;
    vector<int> testLabels;
    object.preparingDataset(imageNames_WithG, trainDataset, trainLabels, testDataset, testLabels, 1, 0.8);    //80% of the positive dataset goes to trainDataset
    object.preparingDataset(imageNames_WithOutG, trainDataset, trainLabels, testDataset, testLabels, 0, 0.8); //80% of the negative dataset goes to trainDataset
    /*for(const auto &x:trainDataset)
    {
        cout<<x.cols<<endl;
    }*/

    //cout<<"Final Number of Images in train Dataset= "<<trainDataset.size()<<endl;
    //cout<<"Final Number of Images in test Dataset= "<<testDataset.size()<<endl;

    vector<vector<float>> hogTrainFeatureVectors, hogTestFeatureVectors;
    object.computeHogFeatures(hogTrainFeatureVectors, trainDataset);
    object.computeHogFeatures(hogTestFeatureVectors, testDataset);
    cout<<" "<<hogTestFeatureVectors.size()<<endl;

    cv::Mat hogTrainFeatureMatrix(hogTrainFeatureVectors.size(), hogTrainFeatureVectors[0].size(), CV_32FC1);
    object.convertVector2Matrix_4SVM(hogTrainFeatureVectors,hogTrainFeatureMatrix);

    cv::Mat hogTestFeatureMatrix(hogTestFeatureVectors.size(), hogTestFeatureVectors[0].size(), CV_32FC1);
    object.convertVector2Matrix_4SVM(hogTestFeatureVectors,hogTestFeatureMatrix );
    
    cout<<"Size of the Feature Matrix"<<cv::Size(hogTrainFeatureMatrix.rows,hogTrainFeatureMatrix.cols)<<endl;
    cout<<"Size of the Feature Matrix"<<cv::Size(hogTestFeatureMatrix.rows,hogTestFeatureMatrix.cols)<<endl;


    cv::Ptr<cv::ml::SVM> svm=object.svmIntializer(2.5,0.02);
    object.printSVMParameters(svm);
    object.svmTrainer(svm,hogTrainFeatureMatrix,trainLabels);

    cv::Mat testResponse;

    object.svmPredict(svm,testResponse,hogTestFeatureMatrix);
    float count=0,accuracy=0;
    object.svmEvaluation(testResponse,count,accuracy,testLabels);
    cout<<accuracy<<endl;
    object.testingViaVideo();
    return 0;
}