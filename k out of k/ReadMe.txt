

We have implemented a 'k-out-of-k' visual secret sharing scheme, in which we create k transparencies out of a given image file, and get back the original image by stacking all k transparencies together. The encryption is such that only when all k transparencies are stacked will we then get the decrypted image. For (k-1) or a lesser number of transparencies, the stacked image would still look encrypted.

Our main goal is to encrypt any Bitmap image into 'k' transparencies. In visual cryptography, each original pixel is modified into a share. A share is a collection of 'm' black and white subpixels which are printed in close proximity so that the human visual system averages their black/white contributions.

For module 2, we have generalized the implementation done in module 1, which was implementing a 2-out-of-2 visual secret sharing scheme on black and white images. 

In the first module, we had implemented a byte-wise encryption, where the scheme was hard coded, since the number of transparencies (k) was always 2. In this module, the implementation is such that the scheme is prepared after entering the value of k. Here the scheme is represented as a k*m matrix, where m=2^(k-1). Also, this scheme is then incorporated for encrypting the image file in a bit-wise manner, that is, each bit is treated as an individual pixel, and is then transformed into k shares of m sub-pixels each.

Having a bit-wise encryption helped us in generalizing the implementation to any Bitmap image, instead of being restricted only to black and white images. However, this works for Bitmap images alone, as the program involves processing the header by changing the dimensions of the image.



Instructions :

A bitmap image(.bmp) is processed as input and 'k' encrypted bitmap images are generated as output, the value of k being taken as a parameter. On merging these 'k' cipher images, the original message can be seen.

-Run kofk.cpp with image as parameter:
	1. g++ kofk.cpp -o ./kofk
	2. ./kofk filename.bmp k
	   (value of k has to be given)
						
-Run output.cpp with two cipher images as parameters:
	1. g++ dekofk.cpp -o ./dekofk
	2. ./op file0.bmp file1.bmp file0+1.bmp finalimage.bmp k
	   (value of k has to be given)


Test Cases :

1) 	File			:	chessboard.bmp
	Value of k		:	3

2) 	File			:	ColorLena.bmp
	Value of k		:	4

3) 	File			:	GrayLena.bmp
	Value of k		:	3

4) 	File			:	logo.bmp
	Value of k		:	4

5) 	File			:	building.bmp
	Value of k		:	5
