#include "Image.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* Get the R intensity of pixel (x, y) in image */
unsigned char GetPixelR(const IMAGE *image, unsigned int x,  unsigned int y)
{
     assert(image);
     return image->R[x + y *image->W];
}

/* Get the G intensity of pixel (x, y) in image */
unsigned char GetPixelG(const IMAGE *image, unsigned int x,  unsigned int y)
{
     assert(image);
     return image->G[x + y *image->W];
}

/* Get the B intensity of pixel (x, y) in image */
unsigned char GetPixelB(const IMAGE *image, unsigned int x,  unsigned int y)
{
     assert(image);
     return image->B[x + y *image->W];
}

/* Set the R intensity of pixel (x, y) in image to r */
void SetPixelR(IMAGE *image, unsigned int x,  unsigned int y, unsigned char r)
{
     assert(image);    
     image->R[x + y *image->W] = r;
}

/* Set the G intensity of pixel (x, y) in image to g */
void SetPixelG(IMAGE *image, unsigned int x,  unsigned int y, unsigned char g)
{
     assert(image);
     image->G[x + y *image->W] = g;
}

/* Set the B intensity of pixel (x, y) in image to b */
void SetPixelB(IMAGE *image, unsigned int x,  unsigned int y, unsigned char b)
{
     assert(image);
     image->B[x + y *image->W] = b;
}

/* Allocate dynamic memory for the image structure and its R/G/B values */
/* Return the pointer to the image, or NULL in case of error */
IMAGE *CreateImage(unsigned int Width, unsigned int Height)
{
     IMAGE *image;
     image = malloc(sizeof(IMAGE));
     
     if (!image)
     {
          perror("Out of memory! Abort...");
          exit(10);
     }
  
     image->W = Width;
     image->H = Height;
     image->R = NULL;
     image->G = NULL;
     image->B = NULL;
     
     image->R = malloc(sizeof(unsigned char) * image->W * image->H);
     image->G = malloc(sizeof(unsigned char) * image->W * image->H);
     image->B = malloc(sizeof(unsigned char) * image->W * image->H);
 
     return image;
}

/* Free the memory for the R/G/B values and IMAGE structure */
void DeleteImage(IMAGE *image)
{
     assert(image);
     free(image->R);
     free(image->G);
     free(image->B);
     free(image);
}

/* Return the image's width in pixels */
unsigned int ImageWidth(const IMAGE *image)
{
     assert(image);
     return image->W;

}

/* Return the image's height in pixels */
unsigned int ImageHeight(const IMAGE *image)
{
     assert(image);
     return image->H;
}

