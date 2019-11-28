/*==============================================================================
Author		:	Vidula Alhat
Date		:	01/06/2016
Description :	Code to combine two frames.
				Provide HEIGHT, WIDTH, DEPTH, CHANNELS, MAX_FRAMES (No of frames),
				BIFURCATION(between two frames)
================================================================================*/
#include "external/highgui/highgui_c.h"
#include "external/core/cv.h"
#include "external/core/cxcore.h"
#include <stdio.h>
	
#define HEIGHT			(800/*400*/)
#define WIDTH			(1280*2)
#define DEPTH			(8)
#define CHANNELS		(3)
#define MAX_FRAMES		(3000)
#define BIFURCATION		(5)
#define RGB_IMAGE		(1)// else grayscale image

void main()
{
	IplImage *combine, *old_output, *new_output;
	int counter,row,column;
	uchar white_line = 255;
	char buff[300],buff1[320],buff2[330];
	CvFont font;
	cvInitFont (&font, CV_FONT_HERSHEY_SIMPLEX, 0.3, 0.5, 0, 1, CV_AA);//0.3,0.5

	combine = cvCreateImage(cvSize(WIDTH,HEIGHT),DEPTH,CHANNELS);

	for(counter = 0; counter < combine->height * combine->widthStep; counter++)
	{
		combine->imageData[counter] = 255;
	}
	
	for(counter = 0; counter < MAX_FRAMES; counter++)
	{	
		//sprintf (buff1,"C:\\Users\\alhatv\\Documents\\Visual Studio 2008\\LDA_MM_Nov_17\\out\\0 (%d).jpeg",counter+1); ///old frames location
		//sprintf (buff1,"C:\\Users\\alhatv\\Documents\\Visual Studio 2008\\LDA_MM_Dec_1\\out\\0 (%d).jpeg",counter+1); ///old frames location
		sprintf (buff1,"C:\\Users\\alhatv\\Desktop\\in\\%06d.jpeg",counter); ///old frames location

		old_output = cvLoadImage(buff1,CV_LOAD_IMAGE_COLOR);

		//sprintf (buff2,"C:\\Users\\alhatv\\Documents\\Visual Studio 2008\\LDA_MM_Dec_1\\out_debug\\0 (%d).jpeg",counter+1);///new frames location
		sprintf (buff2,"C:\\Users\\alhatv\\Desktop\\out\\%06d.jpeg",counter); ///old frames location

		new_output = cvLoadImage(buff2,CV_LOAD_IMAGE_COLOR);

#if RGB_IMAGE
		for(row = 0; row < old_output->height; row++)
		{
			for(column = 0; column < old_output->width; column++)
			{
				
					combine->imageData[row * combine->widthStep + column * 3 + 0 ] = old_output->imageData[row * old_output->widthStep + column * 3 + 0 ];
					combine->imageData[row * combine->widthStep + column * 3 + 1 ] = old_output->imageData[row * old_output->widthStep + column * 3 + 1 ];
					combine->imageData[row * combine->widthStep + column * 3 + 2 ] = old_output->imageData[row * old_output->widthStep + column * 3 + 2 ];
				
					combine->imageData[row * combine->widthStep  + ((column + WIDTH/2) + BIFURCATION) * 3 + 0 ] = new_output->imageData[row * new_output->widthStep + column * 3 + 0 ];
					combine->imageData[row * combine->widthStep  + ((column + WIDTH/2) + BIFURCATION) * 3 + 1 ] = new_output->imageData[row * new_output->widthStep + column * 3 + 1 ];
					combine->imageData[row * combine->widthStep  + ((column + WIDTH/2) + BIFURCATION) * 3 + 2 ] = new_output->imageData[row * new_output->widthStep + column * 3 + 2 ];
			
			}
		}
#else
		//Need to be worked 
			for(row = 0; row < old_output->height; row++)
		{
			for(column = 0; column < old_output->width; column++)
			{
				
					combine->imageData[row * combine->widthStep + column ] = old_output->imageData[row * old_output->widthStep + column];
					
					combine->imageData[row * combine->widthStep  + ((column + WIDTH/2) + BIFURCATION)  ] = new_output->imageData[row * new_output->widthStep + column];
					
			}
		}
#endif
		cvPutText(combine,"OLD_OUTPUT",cvPoint(WIDTH/4,50),(const CvFont*)&font, cvScalar (0,0,255,0));
		cvPutText(combine,"NEW_OUTPUT",cvPoint((3*WIDTH/4),50),(const CvFont*)&font, cvScalar (0,0,255,0));
		//sprintf (buff,"C:\\Users\\alhatv\\Desktop\\Demo1_1Dec\\%d.jpeg", counter);   //final combine location
		sprintf (buff,"C:\\Users\\alhatv\\Desktop\\1629_compare\\%d.jpeg", counter);   //final combine location

		cvSaveImage(buff,combine,0);
		printf("Combining Frame No - %d \n",counter);
		cvReleaseImage(&old_output);
		cvReleaseImage(&new_output);
	}
}
