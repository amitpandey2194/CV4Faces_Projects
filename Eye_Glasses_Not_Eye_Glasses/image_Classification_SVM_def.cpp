#include "image_Classification_SVM_dec.h"
#include "Common_Functions.h"
using namespace cv::ml;
using namespace cv;
void image_Classification_SVM::preparingDataset(vector<string> &imageNames, vector<Mat> &trainDataset,
                                                vector<int> &trainLabels, vector<Mat> &testDataset,
                                                vector<int> &testLabels, int actual_Label, double fraction_Data)
{
    /*
        This function helps in preparing the dataset for training and testing along with the labels
    */
    int fraction_Test_Dataset = imageNames.size() * fraction_Data;
    cout << "Total_Dataset:" << imageNames.size() << endl;
    cout << "Training Dataset contains:" << fraction_Test_Dataset << " images" << endl;
    cout << "Testing Dataset contains:" << imageNames.size() - fraction_Test_Dataset << " images" << endl;

    for (int nameCounter = 0; nameCounter < imageNames.size(); nameCounter++)
    {
        Mat tempImage = imread(imageNames[nameCounter]);
        if (nameCounter < fraction_Test_Dataset)
        {
            trainDataset.push_back(tempImage);
            trainLabels.push_back(actual_Label);
        }
        else
        {
            testDataset.push_back(tempImage);
            testLabels.push_back(actual_Label);
        }
    }
}
//image_Classification_SVM object; //object used for accessing HOG
HOGDescriptor hog(
    Size(96, 32), //winSize, always Cols first then rows,
    Size(8, 8),   //blockSize=generally 2*cellsize
    Size(8, 8),   //blockstride,no overlapping here as bstride=bSize
    Size(4, 4),   //cell Size//entire image will be divided in 4*4 blocks of cells
    9,            //nbins for histogram, recommended by the paper
    0,            //derivAper,
    -1,           //winSigma default value,winSigma = ( blockSize.width + blockSize.height ) / 8
    1,            //histogramNormType,
    0.2,          //L2HysThresh,
    true,         //gammal correction,Boolean indicating whether or not Gamma correction should be done as a pre-processing step
    64,           //nlevels, number of pyramid levels, generally used for object detection
    false         //unsignedGradient by default
);
void image_Classification_SVM::computeHogFeatures(vector<vector<float>> &hogFeatureVectors, vector<Mat> &dataset)
{
    /*
        this function helps to compute the hog features\descriptors for given dataset
    */
    for (vector<Mat>::iterator it = dataset.begin(); it != dataset.end(); it++)
    {
        vector<float> hogFeatures;
        hog.compute(*it, hogFeatures);
        hogFeatureVectors.push_back(hogFeatures);
    }
}

void image_Classification_SVM::convertVector2Matrix_4SVM(vector<vector<float>> &hogFeatureVectors, Mat &hogFeatureMatrix)
{
    for (int i = 0; i < hogFeatureVectors.size(); i++)
    {
        for (int j = 0; j < hogFeatureVectors[0].size(); j++)
        {
            hogFeatureMatrix.at<float>(i, j) = hogFeatureVectors[i][j];
        }
    }
}

void image_Classification_SVM::printSVMParameters(Ptr<SVM> svm)
{
    /*
        This Function prints the parameters used in the SVM Classifier supplied
    */
    cout << "Kernel type         :" << svm->getKernelType() << endl;
    cout << "Type                :" << svm->getType() << endl;
    cout << "C                   :" << svm->getC() << endl;
    cout << "Degree              :" << svm->getDegree() << endl;
    cout << "Nu                  :" << svm->getNu() << endl;
    cout << "Gamma               :" << svm->getGamma() << endl;
}

Ptr<SVM> image_Classification_SVM::svmIntializer(float C, float gamma)
{
    /*
        This function will help in initialize the SVM classifier
    */
    //creating an object with using smart OpenCV pointer PTR
    Ptr<SVM> svm = SVM::create();

    //SVM type//
    svm->setType(SVM::C_SVC);
    //using radial basis function as SVM kernel for introducing non-linearity
    svm->setKernel(SVM::RBF);
    //setting up the margin parameter C
    svm->setC(C);
    //setting up the gamma parameter for rbf
    svm->setGamma(gamma);
    return svm;
}

void image_Classification_SVM::svmTrainer(Ptr<SVM> svm, Mat &trainMat, vector<int> &trainLabels)
{
    //ROW_SAMPLE: indicates that the training data is arranged in rows//
    //using TrainData class is necessary as All the statistical model classes in ml take Ptr<TrainData>.
    cout << "Size of the Feature Matrix inside the trainer" << Size(trainMat.rows, trainMat.cols) << endl;
    Ptr<TrainData> td = TrainData::create(trainMat, ROW_SAMPLE, trainLabels);
    svm->train(td);
    svm->save("../../Eye_Glasses_Not_Eye_Glasses.yml");
}

void image_Classification_SVM::svmPredict(Ptr<SVM> svm, Mat &testResponse, Mat &testData)
{
    svm->predict(testData, testResponse);
}

void image_Classification_SVM::svmEvaluation(Mat &testResponse, float &count, float &accuracy, vector<int> &testLabels)
{
    for (int i = 0; i < testResponse.rows; i++)
    {
        if (testResponse.at<float>(i, 0) == testLabels[i])
        {
            count = count++;
        }
    }
    accuracy = (count / testLabels.size()) * 100;
}

void image_Classification_SVM::testingViaVideo()
{

    cv::VideoCapture capFrames(0);
    if (!capFrames.isOpened())
    {
        cout << "unable to connect to the camera" << endl;
        return;
    }
    double fps = 30.0;
    cv::Mat frame, frameSmall, frameDisplay;
    capFrames >> frame;
    float height = frame.rows;
    //cout<<height<<"x"<<frame.cols<<endl;
    cv::Size size = frame.size();
    dlib::frontal_face_detector faceDetector = dlib::get_frontal_face_detector();
    //the landmark detector is placed in the shape_predictor class
    dlib::shape_predictor landMarkDetector;
    dlib::deserialize("../../shape_predictor_68_face_landmarks.dat") >> landMarkDetector;
    vector<dlib::rectangle> faceRects;
    const float resize_height = 330.0;
    const float resize_scale = height / resize_height;
    const int skip_frames = 5;
    cv::Ptr<cv::ml::SVM> savedModel = cv::ml::StatModel::load<cv::ml::SVM>("../../Eye_Glasses_Not_Eye_Glasses.yml");
    cv::Mat pred;
    CommonFunctions commnObj;
    int count=0;
    while (1)
    {
        capFrames >> frame;
        //we are going to detect the faces at lower resolution
        cv::resize(frame, frameSmall, cv::Size(), 1.0 / resize_scale, 1.0/resize_scale);

        dlib::cv_image<dlib::bgr_pixel> dlibImage(frame);
        dlib::cv_image<dlib::bgr_pixel> dlibImageSmall(frameSmall);
        if (count % skip_frames == 0)
        {
            faceRects = faceDetector(dlibImageSmall);
            cout << "Number of Faces detected:" << faceRects.size();
        }
        if(faceRects.size()>0)
        {
        vector<dlib::full_object_detection> landmarksAll;
        for (int i = 0; i < faceRects.size(); i++)
        {
            
            dlib::rectangle r(
                (long)(faceRects[i].left() * resize_scale),
                (long)(faceRects[i].top() * resize_scale),
                (long)(faceRects[i].right() * resize_scale),
                (long)(faceRects[i].bottom() * resize_scale));
            
            dlib::full_object_detection landmarks = landMarkDetector(dlibImage, r);
            if (i == 0)
            {    cout << "Number of landmarks detected:" << landmarks.num_parts() << endl;}
            landmarksAll.push_back(landmarks);
        }
        cv::Mat croppedImage;
        commnObj.getTheCroppedEyeImage(landmarksAll[0], frame, croppedImage);
        vector<vector<float>> hogFeatureVectors;
        vector<cv::Mat> croppedImageVec;
        croppedImageVec.push_back(croppedImage);
        computeHogFeatures(hogFeatureVectors, croppedImageVec);
        cv::Mat hogFeatureMatrix(hogFeatureVectors.size(), hogFeatureVectors[0].size(), CV_32FC1);
        convertVector2Matrix_4SVM(hogFeatureVectors, hogFeatureMatrix);
        cout << "Size of the Feature Matrix" << cv::Size(hogFeatureMatrix.rows, hogFeatureMatrix.cols) << endl;
        svmPredict(savedModel, pred, hogFeatureMatrix);
        if (pred.at<float>(0,0) == 1)
        {
            cv::putText(frame,"Eye_Glasses",cv::Point(50,size.height-50),cv::FONT_HERSHEY_COMPLEX,1.5,cv::Scalar(0,0,255),3);
        }
        else
        {
            cv::putText(frame,"Not_Eye_Glasses",cv::Point(50,size.height-50),cv::FONT_HERSHEY_COMPLEX,1.5,cv::Scalar(0,0,255),3);
        }
        //cout << "Prediction : " <<pred.at<float>(0, 0) << endl;
        cv::imshow(string("croppedImage"),croppedImage);
        }
        cv::imshow(string("video"), frame);
        count++;
        // Wait for keypress
        char key = cv::waitKey(1);
        if (key == 27) // ESC
        {
            // If ESC is pressed, exit.
            break;
        }
    }
}