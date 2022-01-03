/*********************************************************************/
/* PhotoLab.c: homework assignment #4, for EECS 22,  Fall 2020       */
/*                                                                   */
/* Author: Vivian Lam                                                */
/* Date:   02/28/2020                                                */
/*                                                                   */
/* Comments:                                                         */
/*                                                                   */
/* Please use this template to submit your hw4.                      */
/*********************************************************************/

#include <stdio.h>
#include <string.h>

#include "DIPs.h"
#include "Advanced.h"
#include "FileIO.h"
#include "Test.h"
#include "Image.h"
#include "Constants.h"

/*** function declarations ***/

/* print a menu */
void PrintMenu();

int main()
{
    #ifdef DEBUG
	AutoTest();
    #else
	int rc;
	int option;            /* user input option */
	char fname[SLEN];        /* input file name */
        char name[SLEN];
        IMAGE *image = NULL;
        IMAGE *result = NULL;
	rc = 1;
	PrintMenu();
	scanf("%d", &option);

	/* Hue() parameter */
	int hue;

	/* Posterize() parameter */
	unsigned char rbits, gbits, bbits;

	/* Noise() parameter */
	int n;

	/* MotionBlur() parameter */
	int blur_amount;
        
        /* Enlarge() parameter */
        int enlarge;
    
	/* Square() parameter */
	int offset_Y, offset_X, SquareSize;

	/* BrightnessAndContrast() parameter */
        int brightness, contrast;

	while (option != EXIT)
	{
	    if (option == 1) 
	    {
		printf("Please input the file name to load: ");
		scanf("%s", fname);
		image = LoadImage(fname);
	        if (image)
		   rc = SUCCESS;
		DeleteImage(image);
		image = NULL;
       	    }

	    /* menu item 2 - 12 requires image is loaded first */
            else if (option >= 2 && option < 12) 
            {
		if (rc != SUCCESS)     
		{
                    printf("No image to process!\n");
		}
		/* now image is loaded */
		else 
		{
                    switch (option) 
		    {
			case 2:
			    if (!result)
				result = LoadImage(fname);
                            printf("Please input the file name to save: ");
                            scanf("%s", name);
                            SaveImage(name, result);
                            DeleteImage(result);
			    result = NULL;
                            break;
			
			case 3:
			    image = LoadImage(fname);
                            result = BlackNWhite(image);
                            printf("\"Black amd White\" operation is done!\n");
                            break;
                    
			case 4:
			    image = LoadImage(fname);
                            result = Sharpen(image);
                            printf("\"Sharpen\" operation is done!\n");
                            break;
                    
			case 5:
			    image = LoadImage(fname);
                            printf("Please input the degree of changing hue: ");
                            scanf("%d", &hue);
                            result = Hue(image, hue);
                            printf("\"Hue\" operation is done!\n");
			    break;
                    
			case 6:
			    image = LoadImage(fname);
                            printf("Please input noise percentage: ");
                            scanf("%d", &n);
                            result = Noise(image, n);
                            printf("\"Noise\" operation is done!\n");
                            break;
                    
			case 7:
			    image = LoadImage(fname);
                            printf("Enter the number of posterization bits for R channel (1 to 8): ");
                            scanf("%hhu", &rbits);
                            printf("Enter the number of posterization bits for G channel (1 to 8): ");
                            scanf("%hhu", &gbits);
                            printf("Enter the number of posterization bits for B channel (1 to 8): ");
                            scanf("%hhu", &bbits);
                            result = Posterize(image, rbits, gbits, bbits);
                            printf("\"Posterize\" operation is done!\n");
                            break;
                    
			case 8:
			    image = LoadImage(fname);
                            printf("Please input motion blur amount: ");
                            scanf("%d", &blur_amount);
                            result = MotionBlur(image ,blur_amount);
                            printf("\"Motion Blur\" operation is done!\n");
                            break;
			
			case 9:
			    image = LoadImage(fname);
			    printf("Please input the enlarging percentage (integer between 100 - 200): ");
			    scanf("%d", &enlarge);
                            if (enlarge < 100)
			    {
				do 
				{
				    printf("Warning! Please input proper enlarge percentage (integer between 100 - 200): ");
	                            scanf("%d", &enlarge);
				
				} while (enlarge < 100);
			    }
                            result = Enlarge(image, enlarge);
			    printf("\"Enlarge the image\" operation is done!\n");
			    break;
			
			case 10:
			    image = LoadImage(fname);
			    printf("Please enter the X offset value: ");
			    scanf("%d", &offset_X);
			    printf("Please enter the Y offset value: ");
			    scanf("%d", &offset_Y);
			    printf("Please input the cropped square size: ");
			    scanf("%d", &SquareSize);
			    result = Square(image, offset_X, offset_Y, SquareSize);
			    printf("\"Square\" operation is done!\n");
			    break;
			
			case 11:
			    image = LoadImage(fname);
			    printf("Please input the brightness level (integer between -255 - 255): ");
			    scanf("%d", &brightness);
			    printf("Please input the contrast level (integer between -255 - 255): ");
			    scanf("%d", &contrast);
			    result = BrightnessAndContrast(image, brightness, contrast);
			    printf("\"Brightness and Contrast Adjustment\" operation is done!\n");
			    break;

		    default:
                        break;

                    }
               }
           }

	   else if (option == 12) 
           {
	    	AutoTest();
		rc = SUCCESS;    /* set returned code SUCCESS, since image is loaded */
           }

           else 
           {
		printf("Invalid selection!\n");
	   }

           /* Process finished, waiting for another input */
           PrintMenu();
           scanf("%d", &option);
       }
       printf("You exit the program.\n");
    #endif

    return 0;
}


/*******************************************/
/* Function implementations should go here */
/*******************************************/

/* Menu */
void PrintMenu()
{

    printf("\n------------------------------------------------\n");
    printf("1: Load a PPM image\n");
    printf("2: Save the image in PPM and JPEG format\n");
    printf("3: Change the color image to black and white\n");
    printf("4: Sharpen the image\n");
    printf("5: Change the hue of image\n");
    printf("6: Add Noise to an image\n");
    printf("7: Posterize an image\n");
    printf("8: Motion Blur\n");
    printf("9: Enlarge the picture by percentage\n");
    printf("10: Crop a square portion of the image\n");
    printf("11: Adjust the Brightness and Contrast of an image\n");
    printf("12: Test all functions\n");
    printf("13: Exit\n");
    printf("\n------------------------------------------------\n");
    printf("Please make your choice: ");
}


/* vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */
