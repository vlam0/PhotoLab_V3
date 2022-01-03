#include "Advanced.h"
#include "Image.h"

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>

/* Add noise to an image */
IMAGE *Noise(IMAGE *image, int n)
{
	int x, y, i;
	int num; /* number of noise added */
	num = (n * ImageHeight(image) * ImageWidth(image)) / 100;
	srand(time(NULL));
	
	/* Sets the random loction of pixels to white */
	for ( i = 0; i < num; i++ ) 
	{
		x = ( (double)rand()/RAND_MAX )*(ImageWidth(image)-1);
		y = ( (double)rand()/RAND_MAX )*(ImageHeight(image)-1);
		SetPixelR(image, x, y, 255);
		SetPixelG(image, x, y, 255);
		SetPixelB(image, x, y, 255);
	}

	return image;
}

/* make the image posterized */
IMAGE *Posterize(IMAGE *image, int rbits, int gbits, int bbits)
{
   int x, y;
   int redOnes = 0, greenOnes = 0, blueOnes = 0;
   int i;
   int red, green, blue;

   /* Obtains ones for the lower bits */
   for (i = 1; i < rbits; i++)
   {
        redOnes += pow(2,i-1);
   }

   for (i = 1; i < gbits; i++)
   {
        greenOnes += pow(2,i-1);
   }

   for (i = 1; i < bbits; i++)
   {
        blueOnes += pow(2,i-1);
   }

   /* Loops to shift the bits */
   for (x = 0; x < ImageWidth(image); x++)
   {
        for (y = 0; y < ImageHeight(image); y++)
        {
            /* Shifts out unnecessary bits */
            red = GetPixelR(image, x, y) >> rbits;
            red = red << rbits;
            green = GetPixelG(image,x, y) >> gbits;
            green = green << gbits;
            blue = GetPixelB(image, x, y) >> bbits;
            blue = blue << bbits;

            /* Posterize */
            SetPixelR(image, x, y, (red | redOnes));
            SetPixelG(image, x, y, (green | greenOnes));
            SetPixelB(image, x, y, (blue | blueOnes));
        }
    }
    return image;
}

/* add motion blur to the image */
IMAGE *MotionBlur(IMAGE *image, int BlurAmount)
{
	int x,y,m;
	int temp_r , temp_g , temp_b;
	/* Applies Motion blur to image */
	for (x = 0; x < ImageWidth(image); x++)
	{
        	for (y = ImageHeight(image) - 1; y >= 0 ; y--)
		{
			int count = 0;
			temp_r = temp_g = temp_b = 0.0;
			/* Obtains pixels values of RGB for the BlurAmount of pixels upwards of current pixel */
			for (m = 1; m<=BlurAmount ; m++)
			{
				//if ((x-m) >= 0)
				if((y-m) >= 0)
				{
					temp_r += GetPixelR(image, x, y-m);
					temp_b += GetPixelB(image, x, y-m);
					temp_g += GetPixelG(image, x, y-m);
					count++;
				}
			}
			count = (count==0)?1:count;
			/* Finds average between the original pixel and temp value fore RGB */
			SetPixelR(image, x, y, temp_r / 2.0 / count + GetPixelR(image, x, y) / 2.0);
			SetPixelB(image, x, y, temp_b / 2.0 / count + GetPixelB(image, x, y) / 2.0);
			SetPixelG(image, x, y, temp_g / 2.0 / count + GetPixelG(image, x, y) / 2.0);
		}
	}
	return image;		
}

/* Enlarge image */
IMAGE *Enlarge(IMAGE *image, int percentage)
{
    double x;
    double y;
    double newX, newY;
    int duplicatex, duplicatey;
    IMAGE *E;
    
    double w = ImageWidth(image) * (percentage / 100.00);
    double h = ImageHeight(image) * (percentage / 100.00);
    E = CreateImage(w, h);
    
    /* New image is the original image */
    if (percentage == 100)
    {
        for (x = 0; x < ImageWidth(image); x++)
	{
	    for (y = 0; y < ImageHeight(image); y++)
	    {
		SetPixelR(E, x, y, GetPixelR(image, x, y));
		SetPixelG(E, x, y, GetPixelG(image, x, y));
		SetPixelB(E, x, y, GetPixelB(image, x, y)); 		
	    }
	}	
    }

    /* New image larger than original */
    else if (percentage > 100)
    {
        for (x = 0; x < ImageWidth(image); x++)
        {
            for (y = 0; y < ImageHeight(image); y++)
            {	
		newX = x * (percentage / 100.00);
		newY = y * (percentage / 100.00);

                for (duplicatex = 0; (percentage/100.00) - duplicatex > 0; duplicatex++)
		{	
		    for (duplicatey = 0; (percentage/100.00) - duplicatey > 0; duplicatey++)
		    {
			SetPixelR(E, newX, newY, GetPixelR(image, x, y));
			SetPixelG(E, newX, newY, GetPixelG(image, x, y));
			SetPixelB(E, newX, newY, GetPixelB(image, x, y));
			
			newX++;
		    }
		    newX = newX - duplicatey;
		    newY++;
		}
            }
        }
    }
    DeleteImage(image);
    image = NULL;
    return E;
}

/* Squares image */
IMAGE *Square(IMAGE *image, int x, int y, int L)
{
    int width, height;
    int maxW, maxH;
    IMAGE *sqr;
    sqr = CreateImage(L, L);

    ((x + L) > ImageWidth(image)) ? (maxW = ImageWidth(image)):(maxW = L);
    ((y + L) > ImageHeight(image)) ? (maxH = ImageHeight(image)):(maxH = L);
    
    for (width =  0; width < maxW; width++)
    {
	for (height = 0; height < maxH; height++)
	{
	     SetPixelR(sqr, width, height, GetPixelR(image, x + width, y + height)); 
             SetPixelG(sqr, width, height, GetPixelG(image, x + width, y + height));
             SetPixelB(sqr, width, height, GetPixelB(image, x + width, y + height));
	}
    }
    DeleteImage(image);
    image = NULL;
    return sqr;
}

/* Add Brightness & Constrast to image */
IMAGE *BrightnessAndContrast(IMAGE *image, int brightness, int contrast)
{
    double factor;
    int x, y;
    int r, g, b;
    
    /* Brightness off bounds */
    if (brightness < -255)
	brightness = -255;
    else if (brightness > 255)
	brightness = 255;
    
    /* Contrast off bounds */
    if (contrast < -255)
	contrast = -255;
    else if (contrast > 255)
	contrast = 255;
    
    /* Brightness calculations */
    for (x =  0; x < ImageWidth(image); x++)
    {
        for (y = 0; y < ImageHeight(image); y++)
	{
             SetPixelR(image, x, y, GetPixelR(image, x, y) + brightness);
             SetPixelG(image, x, y, GetPixelG(image, x, y) + brightness);
             SetPixelB(image, x, y, GetPixelB(image, x, y) + brightness);
        }
    }

    /* Contrast correction factor */
    factor = (double)(259 * (contrast + 255)) / (double)(255 * (259 - contrast));

    /* Contrast calculations */
    for (x =  0; x < ImageWidth(image); x++)
    {
        for (y = 0; y < ImageHeight(image); y++)
        {
             r = (int)(factor * (GetPixelR(image, x, y) - 128) + 128);
             g = (int)(factor * (GetPixelG(image, x, y) - 128) + 128);
             b = (int)(factor * (GetPixelB(image, x, y) - 128) + 128);

             if (r > 255)
		r = 255;
	     if (r < 0)
		r = 0;
             if (g > 255)
                g = 255;
             if (g < 0)
                g = 0;
             if (b > 255)
                b = 255;
             if (b < 0)
                b = 0;

             SetPixelR(image, x, y, r);
             SetPixelG(image, x, y, g);
             SetPixelB(image, x, y, b);
        }
    }

    return image;
}



/* vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */
