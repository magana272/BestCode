import numpy as np
import cv2 as cv 
import sys
neu  = cv.imread("brain.jpg")
picture_of_me  = cv.imread("download.png")
if (neu is None) or (picture_of_me is None) :
	sys.exit("Could not read the image.")
NEU= cv.resize(neu,(picture_of_me.shape[1],picture_of_me.shape[0]))
pic = cv.addWeighted(picture_of_me,.75 ,NEU,.25, .4) 
cv.imshow("Displaywindow",pic)
key = cv.waitKey()
if key == ord("f"):
	cv.imwrite("meandneuron.png", pic)


