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
    cv::namedWindow("Frame1");
   for(;;)
    {
		vector<vector<Point> > contours;
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
	    
	    
	    b1 = ptr2[back.step*i +j] ;
	    g1 = ptr2[back.step * i + j + 1];
	    r1 = ptr2[back.step * i + j + 2];
	    
	    //cout<<b-b1<<" "<<g-g1<<" "<<r-r1<<endl;
	    /*
	    if(b-b1>30)ptr1[frame.step*i + j ]=255;
	    else if(b-b1<-30)ptr1[frame.step*i + j ]=0;
	    else ptr1[frame.step*i + j ]=127;
	    */
	    
	      if(b-b1<=70 && b-b1 >=-70)ptr1[frame.step * i + j ]=1;
	      else ptr1[frame.step*i + j+1 ]=b;   
	      
	      if(g-g1<=70 && g-g1 >=-70)ptr1[frame.step * i + j+1 ]=1;
	       else ptr1[frame.step*i + j+1 ]=g;
	      
	      if(r-r1<=70 && r-r1 >=70)ptr1[frame.step * i + j+2 ]=1;
	      else ptr1[frame.step*i + j+2 ]=r;
	    
	  }
       }
	
	cv::imshow("Frame1",frame);
	
    cv::erode(frame,frame,cv::Mat());
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
	cv::dilate(frame,frame,cv::Mat());
	//cvtColor(frame, frame, CV_RGB2GRAY);
	cv::imshow("Frame2",frame);

	vector<Vec4i> hierarchy;
    RNG rng(12345);
	
	IplImage copy = frame;
	IplImage* new_frame = &copy;
	cvSmooth(new_frame,new_frame,CV_GAUSSIAN,3,0,0,0);
	Mat frame1(new_frame);
	cv::imshow("result",frame1);
	Canny(frame, frame, 100, 200, 3);
	findContours( frame, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
	Mat drawing = Mat::zeros( frame.size(), CV_8UC3 );
	for( int i = 0; i< contours.size(); i++ )
    {
		if(contourArea( contours[i],false)>100){
        Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
		
        drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, Point() );
		}}
   	
	cv::erode(drawing,drawing,cv::Mat());
	
	//cv::imshow("result1",drawing);
	if(cv::waitKey(30) >= 0) break;

        }
    return 0;
}
