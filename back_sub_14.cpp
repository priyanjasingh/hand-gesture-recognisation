#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>
using namespace cv; 
using namespace std;

int main(int argc, char *argv[])
{
    cv::Mat frame;
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
 
    for(;;)
    {
        cap >> frame;
        bg.operator ()(frame,fore);
        bg.getBackgroundImage(back);
	int i,j,r,g,b,b1,g1,r1;
	
	unsigned char *ptr1 = (unsigned char*)(frame.data);
	unsigned char *ptr2 = (unsigned char*)(back.data);
	unsigned char *ptr3 = (unsigned char*)(subtracted.data);

	cv::imshow("Frame",frame);
	
	for(int i = 0;i < frame.rows ;i++){
	  for(int j = 0;j < 3*(frame.cols) ;j++){
	    b =  ptr1[frame.step * i + j ] ;
	    g = ptr1[frame.step * i + j + 1];
	    r = ptr1[frame.step * i + j + 2];
	    
	    /* 
	    
	    b1 = ptr2[back.step*i +j] ;
	    g1 = ptr2[back.step * i + j + 1];
	    r1 = ptr2[back.step * i + j + 2];
	    */
	    cout<<b<<" "<<g<<" "<<r<<endl;
	    /*
	    if(b-b1>30)ptr1[frame.step*i + j ]=255;
	    else if(b-b1<-30)ptr1[frame.step*i + j ]=0;
	    else ptr1[frame.step*i + j ]=127;
	    */
	    /*  
	      if(b-b1<=70 && b-b1 >=-70)ptr1[frame.step * i + j ]=1;
	      else ptr1[frame.step*i + j+1 ]=b;   
	      
	      if(g-g1<=70 && g-g1 >=-70)ptr1[frame.step * i + j+1 ]=1;
	       else ptr1[frame.step*i + j+1 ]=g;
	      
	      if(r-r1<=70 && r-r1 >=70)ptr1[frame.step * i + j+2 ]=1;
	      else ptr1[frame.step*i + j+2 ]=r;
	    */
	  }
       }
	
	
      	cv::imshow("Frame",frame);
	/*
        cv::erode(frame,frame,cv::Mat());
      	cv::imshow("Frame1",frame);

	cvtColor(frame, frame, CV_RGB2GRAY);
	cv::dilate(frame,frame,cv::Mat());
	ptr1 = (unsigned char*)(frame.data);
	
	for(int i=0;i<frame.rows;i++){
	  for(int j=0;j<frame.cols;j++){
	    
	    if( ptr1[frame.step * i + j ]>5){
	      ptr1[frame.step * i + j ] =254;

	    }

	  }
	  
	}
	
	//cvtColor(frame, frame, CV_RGB2GRAY);
	cv::imshow("Frame2",frame);
	cv::dilate(frame,frame,cv::Mat());
	
	cv::imshow("Frame3",frame);
	*/
	//absdiff(frame,back,subtracted);
        /*cv::erode(subtracted,subtracted,cv::Mat());
	cv::imshow("erosion",subtracted);	
	// cv::findContours(fore,contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE);
	// cv::drawContours(frame,contours,-1,cv::Scalar(0,0,255),2);
	// cv::imshow("Frame1",frame);
	// cv::imshow("Background",back);
	//	cv::imshow("after sub",subtracted);
	*/ 
	if(cv::waitKey(30) >= 0) break;

        }
    return 0;
}
