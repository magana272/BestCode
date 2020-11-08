# ===============================================================================================================
# ineffecient way to seperate channels  
# ===============================================================================================================

import cv2 as cv

import numpy as np 
def color_seperator():
	image = input("are you ready ?!!: ") 
	print("i didn't ask you for your file but i could have ... but here is mine", str(image))
	image  = cv.imread("color.jpg")
	
	if(image is None) :
		sys.exit("Could not read the image.")
	red_pic_of_me = []
	green_pic_of_me = []
	blue_pic_of_me = []
	me_numoy = np.array(image)
	cv.imwrite('color.png', me_numoy)
	meme =cv.imread("color.png")
	picture_of_me=cv.resize(meme,(400,400))
	cv.imshow('image',meme)
	k = cv.waitKey(0)
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
#       cv.imshow("Displaywindow", np.array(RGB_picture[0]))
# ===============================================================================================================
# SAVE AND SEPERATE COLOR CHANNELS 
# ===============================================================================================================
	red_arr,green_arr,blue_arr = np.array(RGB_picture[2]), np.array(RGB_picture[1]), np.array(RGB_picture[0])
	combined_img = np.add(np.add(red_arr,green_arr),blue_arr)
	cv.imwrite('red3.png',red_arr) 
	red1 =cv.imread("red3.png")
	cv.imshow('image3',red1)
	cv.imwrite('green3.png', green_arr) 
	green1 =cv.imread("green3.png")
	cv.imshow('image3',green1)
	cv.imwrite('blue3.png', blue_arr) 
	blue1 =cv.imread("blue3.png")
	cv.imshow('image1',blue1)
	cv.imwrite('combined.png', combined_img) 
	com =cv.imread("red3.png")
	cv.imshow('image4',com)

	if k == 27:         # wait for ESC key to exit
   		cv.destroyAllWindows()

color_seperator()
# ===============================================================================================================
# NOTES : This project made me miss C !! i should start useing C or C++ again,, those languages are kinda fun !!
#        1)have a file called "color.jpg"
#   	 2)change image on line 11, if you want to sepearate the colors of another picture !!
#	 
#
#
#	 
# ===============================================================================================================

