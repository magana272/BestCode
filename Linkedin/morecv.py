import numpy as np
import cv2 as cv 
import sys
import scipy.misc
from PIL import Image
def color_seperator():
	image = input("file name and please make it a jpeg if you!: ") 
	print("i didn't really take your input", str(image))
	pic1  = cv.imread("color.jpg")
	picture_of_me  = cv.imread("download.png")
	if (pic1 is None) or (picture_of_me is None) :
		sys.exit("Could not read the image.")
	picture_one_resized = cv.resize(pic1,(picture_of_me.shape[1],picture_of_me.shape[0]))
	red_pic_of_me = []
	green_pic_of_me = []
	blue_pic_of_me = []
	me_numoy = np.array(picture_of_me)
	print("actual\n:",picture_of_me)
	print("numpye\n:",me_numoy)
	meme = Image.fromarray(me_numoy, 'YCbCr')
	meme.save('me2.jpeg')
	meme.show()
	RGB_picture = [red_pic_of_me,green_pic_of_me,blue_pic_of_me]
	layers = 0
#red ===============================================================================================================
	indexer = 0
	for i in picture_of_me:	
		RGB_picture[layers].append([])
		for j in i :
			RGB_picture[layers][indexer].append([j[layers],0,0])
		indexer +=1
	layers += 1	
#green ===============================================================================================================
	indexer = 0
	for i in picture_of_me:
		RGB_picture[layers].append([])
		for j in i :
			RGB_picture[layers][indexer].append([0,j[layers],0])
		indexer +=1
	layers += 1
#blue ===============================================================================================================
	indexer = 0
	for i in picture_of_me:
		RGB_picture[layers].append([])
		for j in i :
			RGB_picture[layers][indexer].append([0,0,j[layers]])
		indexer +=1
#	cv.imshow("Displaywindow", np.array(RGB_picture[0]))
	red_arr,green_arr,blue_arr = np.array(RGB_picture[2]), np.array(RGB_picture[1]), np.array(RGB_picture[0])
	print(red_arr)
#	red = Image.fromarray(red_arr, 'RGB')
#	red.save('red2.png')
#	red.show()
#	green = Image.fromarray(green_arr, 'RGB')
#	green.save('green2.png')
#	green.show()
#	blue = Image.fromarray(blue_arr, 'RGB')
#	blue.save('blue2.png')
#	blue.show()
#	combined_img = np.add(np.add(red_arr,green_arr),blue_arr)
#	recom = Image.fromarray(combined_img, 'RGB')
#	recom.save('combined.png')
#	recom.show()
	print("fuuunck")
color_seperator()
