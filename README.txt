Name: Evan Riegel
UCID: 00311775

— Notes: —

	This program has been designed to run on the University of Calgary’s Linux distributions

	Details:

	Linux version 3.14.5-200.fc20.x86_64 (mockbuild@bkernel02.phx2.fedoraproject.org)
	(gcc version 4.8.2 20131212 (Red Hat 4.8.2-7) (GCC) )

	3rd party code used in this project:
		Author: Samuel R. Buss
			- TextureBMP.cpp (TextureBMP.h was added to accompany the former)
			- RgbImage.h
			- RgbImage.cpp

— Compile / execution instructions: —

	1. Download “A1.zip”
	2. Extract zip file to location of your choice
	3. Using Terminal, navigate into the extracted folder “A1”
	4. Type “make” and press Enter
	5. Type “./A1” and press Enter

— Operating instructions: —

	1. IMPORTANT: To open, save, or dissolve to a file, simply type the name of which of the
	bitmap images inside ./A1/Images you wish to open. For exampe:

		image filename: 	/A1/maggie.bmp
		type: 			maggie

	2. As commented inside the code, the dissolve function will only work if the two chosen
	bitmaps are exactly the same dimensions. To this end, I recommend using “scenery.bmp”
	and “maggie.bmp” to dissolve into each other, as I made sure they were both 400x400 pixels.

— Bonuses implemented: —

	1. Change contrast:
		- Load an image, then select “Edit > Contrast”
		- Follow the on-screen instructions
	1. Dissolve image:
		- Load an image, then select “Edit > Dissolve”
		- Follow the on-screen instructions

— Miscellaneous: —

	Inside “A1/Examples” are saved .bmp files demonstrating all of the image transformations.