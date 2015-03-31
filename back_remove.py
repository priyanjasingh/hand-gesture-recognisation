import cv2.cv as cv
import cv2
import numpy as np


def main():
    cv.NamedWindow("camera", 1)
    #cv.NamedWindow("camera1", 1)
    #cv.NamedWindow("camera2", 1)

    capture = cv.CaptureFromCAM(0)
    
    mid = cv.QueryFrame(capture)
    frames = cv.QueryFrame(capture)
    while True:
        mid = cv.CloneImage(frames)
        img = cv.QueryFrame(capture)
        
        im_mid = cv.CreateMat(mid.height, mid.width, cv.CV_8U)
        cv.CvtColor(mid, im_mid, cv.CV_RGB2GRAY)
    
        im_img = cv.CreateMat(img.height, img.width, cv.CV_8U)
        cv.CvtColor(img, im_img, cv.CV_RGB2GRAY)
    
        im_mi = np.asarray(im_mid)
        im_i = np.asarray(im_img)
    
        #differ(array_mid,array_img)
        a=0.01
        for y in range(im_i.shape[1]):
            for x in range(im_i.shape[0]):
                im_mi[x][y]= (a)*int(im_mi[x,y])+(1-a)*int(im_i[x,y])
        

            
        img_diff = cv.fromarray(im_mi)
        frames = im_mi.operator IplImage();
        #iplImage = cv2.adaptors.NumPy2Ipl(im_mi)
        cv.ShowImage("After differ", img_diff)
        

        c=cv.WaitKey(1)
        if c==27: #Break if user enters 'Esc'.
            break
main()
