import cv2.cv as cv
import cv2
import numpy as np
import time

#def differ(imgmid,imgnew):
    
    



def main():
    cv.NamedWindow("camera", 1)
    #cv.NamedWindow("camera1", 1)
    #cv.NamedWindow("camera2", 1)

    capture = cv.CaptureFromCAM(0)
    
    mid = cv.QueryFrame(capture)
    frames = cv.QueryFrame(capture)
    
    #res = cv.CreateImage(cv.GetSize(frames),8,1);
    #cv.ShowImage("camera1", res)
    #cv.ShowImage("camera", img)
    res = cv.CreateMat(frames.height, frames.width, cv.CV_8U)

	
    while True:
        mid = cv.CloneImage(frames);
        img = cv.QueryFrame(capture)
	
        im_mid = cv.CreateMat(mid.height, mid.width, cv.CV_8U)
        cv.CvtColor(mid, im_mid, cv.CV_RGB2GRAY)
        
        print im_mid
        
        im_img = cv.CreateMat(img.height, img.width, cv.CV_8U)
        cv.CvtColor(img, im_img, cv.CV_RGB2GRAY)
        
        
        
        
        cv.AbsDiff(im_mid, im_img , res)
        cv.ShowImage("After AbsDiff", res)
        
        

        
        
        cv.Smooth(res, res, cv.CV_BLUR, 5,5)
        cv.ShowImage("Image1", res)
        
        element = cv.CreateStructuringElementEx(5*2+1, 5*2+1, 5, 5,  cv.CV_SHAPE_RECT)
        cv.MorphologyEx(res, res, None, None, cv.CV_MOP_OPEN)
        cv.MorphologyEx(res, res, None, None, cv.CV_MOP_CLOSE)
        
        cv.ShowImage("Image2", res)
        
        cv.Threshold(res, res, 10, 255, cv.CV_THRESH_BINARY_INV)
        
        cv.ShowImage("Image", res)
    
        
        #im_mid = np.asarray(img)
        #im_img = np.asarray(img)
        #img_res = np.asarray(res)
        
        #cv2.absdiff(im_mid,im_img,img_res)
        
        #cv.ShowImage("camera", img_res)
		#differ(im_mid,im_img)
		
        print im_mid
        if cv.WaitKey(10) == 27:
            break 


main()

differ(im_mid,im_img):
    total=0
    #num=1.0/(3*(imgid.width)*(imgid.height))
    sqs=0    
    for x in range(480):
    		for y in range(640):
		        k = im_img[x,y]-im_mid[x,y];
		        if (k > 30) ptrmid[x]=255;
				elif (k < -30) ptrmid[x]=0;
				else ptrmid[x]=127;
		        print graypixel
'''
#int k, x;
#	float total=0, num=1.0/(3*(imgmid->width)*(imgmid->height)), sqs=0;
#	for( int y=0; y<imgmid->height; y++ ) {
#		uchar* ptrmid = (uchar*) (
#		imgmid->imageData + y * imgmid->widthStep
#		);
#		uchar* ptrnew = (uchar*) (
#		imgnew->imageData + y * imgnew->widthStep
#		);
#		for(x=0; x<3*(imgmid->width); x++ ) {
#			k=ptrnew[x]-ptrmid[x];
#			if (k > 30) ptrmid[x]=255;
#			else if (k < -30) ptrmid[x]=0;
#			else ptrmid[x]=127;
#		}
#	}
'''
