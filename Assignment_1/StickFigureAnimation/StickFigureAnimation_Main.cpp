// StickFigureAnimation_Main.cpp : Defines the entry point for the console application.
//

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <math.h>
#include <iostream>
using namespace std;
using namespace cv;

int main()
{
	Mat image = Mat::zeros(500, 800, CV_8UC3);//created an empty black Mat object//
	VideoWriter video("FarewellAaklin.avi", CV_FOURCC('M', 'J', 'P', 'G'), 10, Size(image.cols, image.rows));
											  // Draw a circle
	Mat stickFigure = image.clone();
	int centerOfCircle = int(image.rows/2);//integer center= half of the height of the Image, just in the middle of the image//
	namedWindow("StickFigure",CV_WINDOW_AUTOSIZE);
	int heightOfTheBodyFromFloor = 100;
	int endOfLine_y = image.rows - heightOfTheBodyFromFloor;
	float angle = 45.0; double PI = 3.14159265;
	double SlopeOfBiceps = tan(angle);
	//cout << startingSlopeOfBiceps << endl;
	float radius = 30.0;
	int waveLength = 5;
	int k = 0;
	int startingY_PosOfBiceps = radius + centerOfCircle;
	int endingY_PosOfBiceps = startingY_PosOfBiceps + 40;
	float endingX_PosofRightBiceps = (endingY_PosOfBiceps - startingY_PosOfBiceps) / (SlopeOfBiceps);
	float endingX_PosofLeftBiceps = (endingY_PosOfBiceps - startingY_PosOfBiceps) / (-SlopeOfBiceps);
	//cout << endingX_PosofBiceps << endl;
	for (int i = 0; i<int(image.cols);i++) {
		circle(stickFigure, Point(i, centerOfCircle), radius, Scalar(0, 0, 255), 2, 8);//head of the stick figure//
		line(stickFigure, Point(i, int(radius+centerOfCircle)), Point(i, endOfLine_y), Scalar(110, 220, 0), 5, CV_AA);//body of the stick figure//
		//Right-Left Bicep formation//
		line(stickFigure, Point(i, int(radius + centerOfCircle)),Point(int(endingX_PosofRightBiceps+i),endingY_PosOfBiceps), Scalar(110, 220, 0), 5, CV_AA);
		line(stickFigure, Point(i, int(radius + centerOfCircle)), Point(int(endingX_PosofLeftBiceps + i), endingY_PosOfBiceps), Scalar(110, 220, 0), 5, CV_AA);
		//forearm formation//
		line(stickFigure,Point(int(endingX_PosofRightBiceps + i), endingY_PosOfBiceps), Point(int(endingX_PosofRightBiceps + i) + waveLength, endingY_PosOfBiceps-40), Scalar(110, 220, 0), 5, CV_AA);
		line(stickFigure, Point(int(endingX_PosofLeftBiceps + i), endingY_PosOfBiceps), Point(int(endingX_PosofLeftBiceps + i), endingY_PosOfBiceps + 40), Scalar(110, 220, 0), 5, CV_AA);
		//Legs (Thighs)Formation//
		line(stickFigure,Point(i, endOfLine_y),Point(int(endingX_PosofRightBiceps + i), (endOfLine_y +20)), Scalar(110, 220, 0), 5, CV_AA);
		line(stickFigure, Point(i, endOfLine_y), Point(int(endingX_PosofLeftBiceps + i),(endOfLine_y+20)), Scalar(110, 220, 0), 5, CV_AA);
		//calf formation//
		line(stickFigure, Point(int(endingX_PosofRightBiceps + i), (endOfLine_y + 20)), Point(int(endingX_PosofRightBiceps + i), (endOfLine_y + 20) + 50), Scalar(110, 220, 0), 5, CV_AA);
		line(stickFigure, Point(int(endingX_PosofLeftBiceps + i), (endOfLine_y + 20)), Point(int(endingX_PosofLeftBiceps + i), (endOfLine_y + 20) + 50), Scalar(110, 220, 0), 5, CV_AA);
		waveLength = -(waveLength);

		//Another StickFigure//
		circle(stickFigure, Point(i+100, centerOfCircle), radius, Scalar(0, 0, 255), 2, 8);//head of the stick figure//
		line(stickFigure, Point(i+100, int(radius + centerOfCircle)), Point(i+100, endOfLine_y), Scalar(110, 220, 0), 5, CV_AA);//body of the stick figure//
																														//Right-Left Bicep formation//
		line(stickFigure, Point(i+100, int(radius + centerOfCircle)), Point(int(endingX_PosofRightBiceps + i+100), endingY_PosOfBiceps), Scalar(110, 220, 0), 5, CV_AA);
		line(stickFigure, Point(i+100, int(radius + centerOfCircle)), Point(int(endingX_PosofLeftBiceps + i+100), endingY_PosOfBiceps), Scalar(110, 220, 0), 5, CV_AA);
		//forearm formation//
		line(stickFigure, Point(int(endingX_PosofRightBiceps + i+100), endingY_PosOfBiceps), Point(int(endingX_PosofRightBiceps + i+100) + waveLength, endingY_PosOfBiceps - 40), Scalar(110, 220, 0), 5, CV_AA);
		line(stickFigure, Point(int(endingX_PosofLeftBiceps + i+100), endingY_PosOfBiceps), Point(int(endingX_PosofLeftBiceps + i+100), endingY_PosOfBiceps + 40), Scalar(110, 220, 0), 5, CV_AA);
		//Legs (Thighs)Formation//
		line(stickFigure, Point(i+100, endOfLine_y), Point(int(endingX_PosofRightBiceps + i+100), (endOfLine_y + 20)), Scalar(110, 220, 0), 5, CV_AA);
		line(stickFigure, Point(i+100, endOfLine_y), Point(int(endingX_PosofLeftBiceps + i+100), (endOfLine_y + 20)), Scalar(110, 220, 0), 5, CV_AA);
		//calf formation//
		line(stickFigure, Point(int(endingX_PosofRightBiceps + i+100), (endOfLine_y + 20)), Point(int(endingX_PosofRightBiceps + i+100), (endOfLine_y + 20) + 50), Scalar(110, 220, 0), 5, CV_AA);
		line(stickFigure, Point(int(endingX_PosofLeftBiceps + i+100), (endOfLine_y + 20)), Point(int(endingX_PosofLeftBiceps + i+100), (endOfLine_y + 20) + 50), Scalar(110, 220, 0), 5, CV_AA);
		// Identify if 'g' or 'G' is pressed
		if (k == 103 || k == 71)
			putText(stickFigure, "Congratulations Aaklin!!!!!", Point(10, 40), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0), 1);
		// Identify if 'f' or 'F' is pressed
		if (k == 102 || k == 70)
			putText(stickFigure, "Have a great Future Ahead!!!", Point(10, 40), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0), 1);
		// Identify if 'e' or 'E' is pressed
		if (k == 101 || k == 69)
			putText(stickFigure, "We Already Miss you!!Bye Bye Aaklin!", Point(10, 40), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0), 1);
		if (k == 100 || k == 68)
			putText(stickFigure, "See you Soon Brother!!", Point(10, 40), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0), 1);

		putText(stickFigure, "Amit", Point(i-35, 490), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0), 1);
		putText(stickFigure, "Deven", Point(i +50, 490), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0), 1);
		imshow("StickFigure", stickFigure);
		
		// And instead of a circle we will thick straight line at the end//
		if (k==27) {
			break;//break out of the loop if the escape key is pressed//
		}
		k = waitKey(1);
		video.write(stickFigure);
		stickFigure.setTo(Scalar(0, 0, 0));//if I don't set the Mat file again to zero, it will keep on overwriting the same Mat file//
		
	}
	// When everything done, release the video capture and write object
	stickFigure.release();
	video.release();
	destroyAllWindows();
    return 0;
}

