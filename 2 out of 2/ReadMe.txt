
Implemented the core concept of the visual secret sharing problem. We assume that the message consists of a collection of black and white pixels and each pixel is handled separately. 

Each original pixel is modified into a share. A share is a collection of 'm' black and white subpixels which are printed in close proximity so that the human visual system averages their black/white contributions. 

In this implementation, we generate 2 shares per pixel which will result in 2 transparencies(cipher images), and each share will consist of 4 subpixels. 

A bitmap image(.bmp) is processed as input and and two bitmap images are generated as output. On merging these two cipher images, the original message can be seen.

Instructions:

-Run input.cpp with image as parameter:
	1. g++ input.cpp -o ./inp
	2. ./inp filename.bmp
	
						
-Run output.cpp with two cipher images as parameters:
	1. g++ output.cpp -o ./op
	2. ./op file0.bmp file1.bmp



