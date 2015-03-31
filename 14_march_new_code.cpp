#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>
#include<algorithm>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
using namespace std;
using namespace cv;
int main(int argc, char *argv[])
{
Mat frame;
Mat back;
Mat fore;
vector<pair<Point,double> > palm_centers;
VideoCapture cap(0);
BackgroundSubtractorMOG2 bg;
bg.set("nmixtures",3);
bg.set("detectShadows",false);
namedWindow("Frame");
namedWindow("Background");
int backgroundFrame=500;
for(;;)
{
vector<vector<Point> > contours;
//Get the frame
cap >> frame;
//Update the current background model and get the foreground
if(backgroundFrame>0)
{bg.operator ()(frame,fore);backgroundFrame--;}
else
{bg.operator()(frame,fore,0);}
//Get background image to display it
bg.getBackgroundImage(back);
//Enhance edges in the foreground by applying erosion and dilation
erode(fore,fore,Mat());
dilate(fore,fore,Mat());
if(backgroundFrame>0)
putText(frame, "Recording Background", cvPoint(30,30), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200,200,250), 1, CV_AA);
imshow("Frame",fore);
imshow("Background",back);
if(waitKey(10) >= 0) break;
}
return 0;
}
