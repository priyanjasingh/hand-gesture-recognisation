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
		//unsigned char *ptr2 = (unsigned char*)(back.data);
		//unsigned char *ptr3 = (unsigned char*)(subtracted.data);
		for(int i = 0;i < frame.rows ;i++){
				for(int j = 0;j < 3*(frame.cols) ;j++){
					b =  ptr1[frame.step * i + j ] ;
					g = ptr1[frame.step * i + j + 1];
					r = ptr1[frame.step * i + j + 2];
					
					//	cout<<b<<" "<<g<<" "<<r<<endl;
						if(b<(255-143) && g<(255-184) && r<(255-220))
					{
					//	cout<<"A"<<endl;
						if(r>g && g>b )
						{
							//	cout<<"FEFEFE"<<endl;
						 ptr1[frame.step * i + j ]=255;
						 ptr1[frame.step * i + j+1]=255;
						 ptr1[frame.step * i + j +2]=255;
						}
							}
			/*	else
					{
					    ptr1[frame.step * i + j ] =1;
						ptr1[frame.step * i + j+1 ]=1;
						ptr1[frame.step * i + j +2]=1;
				}
			*/	}
		}
			cv::imshow("Frame",frame);
				if(cv::waitKey(30) >= 0) break;

        }
    return 0;
}
						
						
