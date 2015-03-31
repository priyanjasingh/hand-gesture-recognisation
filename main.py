import cv2.cv as cv
import cv2
import numpy as np
import time

def differ(im_mi,im_im):
    total=0
    sqs=0    
    im_img = np.asarray(im_mi)
    im_mid = np.asarray(im_im)
    for x in range(480):
        for y in range(640):
            k = int(im_img[x,y])-int(im_mid[x,y])
            if (k > 30): im_mid[x,y]=255;
            elif (k < -30): im_mid[x,y]=0;
            else: im_mid[x,y]=127;
    iplImage =opencv.adaptors.NumPy2Ipl(im_mid)
    return iplImage

def horize(origin,modif):
    ptr = np.asarray(origin)
    nemptr = np.asarray(modif)
    for x in range(480):
        for t in range(3):
            for y in range(3*640):
                if ptr[y][x]!=127:
                    begin=i=x
                    while ptr[y][x]!=127:i=i+3
                    if i-begin<70:
                        while x<i:
                            nemptr[y][x]=127
                            x=x+3
                    else: 
                        while x<i:
                            nemptr[y][x]=ptr[y][x]
                            x=x+3
                    nemptr[y][x]=127

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
	mid =differ(mid,img);
        cv.ShowImage("camera1", mid)
        """
        horize = cv.CreateMat(mid.height, mid.width, cv.CV_8U)
        horize(mid,horize);
        verize= cv.CreateMat(mid.height, mid.width, cv.CV_8U)
        verize(mid,verize);
        commonize(mid,horize,verize)
        cv.ShowImage("camera2", mid)
        
        cv.CvtColor(mid, im_mid, cv.CV_RGB2GRAY)
        cv.ShowImage("camera1", im_mid)
        #print im_mid
        
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
		
        #print im_mid
        """
        if cv.WaitKey(10) == 27:
            break 


main()


		        


