#include<opencv2/opencv.hpp>
#include<bits/stdc++.h>
#include<iostream>
#include<vector>
using namespace cv; 
using namespace std;

void  INThandler(int sig)
{
     char  c;
     // signal(sig, SIG_IGN);
     printf("OUCH, did you hit Ctrl-C?\n"
            "Do you really want to quit? [y/n] ");
     c = getchar();
     if (c == 'y' || c == 'Y')
       exit(0);
}


int main(int argc, char *argv[])
{
    cv::Mat frame;
	cv::Mat frame1;
    cv::Mat back;
    cv::Mat fore;
    cv::Mat subtracted;
    cv::VideoCapture cap(0);
    cv::BackgroundSubtractorMOG2 bg;
    bg.set("nmixtures", 3);
    bg.set("detectShadows", false);
 
    std::vector<std::vector<cv::Point> > contours;
 
     cv::namedWindow("Frame");
    //cv::namedWindow("Frame1");
    // cv::namedWindow("Frame1");
    //cv::namedWindow("Frame1");
    // cv::namedWindow("Background");
     
    signal(SIGINT, INThandler);
 
    for(;;)
    {
        vector<vector<Point> > contours;
        cap >> frame;
        bg.operator ()(frame,fore);
        bg.getBackgroundImage(back);
	int i,j,r,g,b,b1,g1,r1;
	
	// cv::imshow("Frame",frame);
//	cv::imshow("back",back);
	
	
	
	
	cv::erode(fore,fore,cv::Mat());
	cv::dilate(fore,fore,cv::Mat());	

	cv::imshow("Fore",fore);

	unsigned char *ptr1 = (unsigned char*)(frame.data);
	unsigned char *ptr2 = (unsigned char*)(back.data);
	unsigned char *ptr3 = (unsigned char*)(subtracted.data);

	//cv::imshow("Frame",frame);
	
	for(int i = 0;i < frame.rows ;i++){
	  for(int j = 0;j < 3*(frame.cols) ;j++){
	    b =  ptr1[frame.step * i + j ] ;
	    g = ptr1[frame.step * i + j + 1];
	    r = ptr1[frame.step * i + j + 2];
	    	    
	    b1 = ptr2[back.step*i +j] ;
	    g1 = ptr2[back.step * i + j + 1];
	    r1 = ptr2[back.step * i + j + 2];
	    
	    //cout<<b-b1<<" "<<g-g1<<" "<<r-r1<<endl;
	    /*
	    if(b-b1>30)ptr1[frame.step*i + j ]=255;
	    else if(b-b1<-30)ptr1[frame.step*i + j ]=0;
	    else ptr1[frame.step*i + j ]=127;
	    */
					
		
	    int level=30;
	    if((b-b1<=level) && (b-b1 >=-level))ptr1[frame.step * i + j ]=5;
	      else ptr1[frame.step*i + j ]=b;   
			      
	    if((g-g1<=level) && (g-g1>=-level))ptr1[frame.step * i + j+1 ]=5;
	       else ptr1[frame.step*i + j+1 ]=g;
	      
	    if((r-r1<=level) && (r-r1 >=-level))ptr1[frame.step * i + j+2 ]=5;
	      else ptr1[frame.step*i + j+2 ]=r;
	    
	  }
       }
	
	//	cv::imshow("loop",frame);
	
        cv::erode(frame,frame,cv::Mat());
		cv::dilate(frame,frame,cv::Mat());
	//	cv::imshow("Frame1",frame);

   	cvtColor(frame, frame, CV_RGB2GRAY);
	
	cv::imshow("Frame1",frame);	
	
	
	ptr1 = (unsigned char*)(frame.data);
	
	for(int i=0;i<frame.rows;i++){
	  for(int j=0;j<frame.cols;j++){
	    
	    if( ptr1[frame.step * i+j]>5){
	      ptr1[frame.step * i+j] =254;

	    }

	  }
	  
	}
	cv::imshow("Frame2",frame);
cv::threshold(frame, frame, 1, 255, CV_THRESH_BINARY);
	cv::Mat contourImage(frame.size(), CV_8UC3, cv::Scalar(0,0,0));
     cv::findContours(fore,contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE);
	for(int i=0;i<contours.size();i++)
	{
//Ignore all small insignificant areas
if(contourArea(contours[i])>=500)
{
//Draw contour
vector<vector<Point> > tcontours;
tcontours.push_back(contours[i]);
drawContours(contourImage,contours,-1,cv::Scalar(0,0,255),2);
}
	}
	cv::imshow("contour",contourImage);
	/*
	absdiff(frame,back,subtracted);
     cv::erode(subtracted,subtracted,cv::Mat());
	cv::imshow("erosion",subtracted);	
	 cv::findContours(fore,contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE);
	 cv::drawContours(frame,contours,-1,cv::Scalar(0,0,255),2);
	 cv::imshow("Frame1",frame);
	 cv::imshow("Background",back);
		cv::imshow("after sub",subtracted);
	*/

	if(cv::waitKey(30) >= 0) break;

        }
    return 0;
}


//g++ 15_march_apply_contour.cpp -o hand -lopencv_core -lopencv_imgproc -lopencv_objdetect -lopencv_highgui -lopencv_video -lXtst -lX11 -lm
/*findContours(fore,contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE);
*/
