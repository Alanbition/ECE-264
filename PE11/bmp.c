#include <stdlib.h>
#include <stdio.h>

#include "bmp.h"

/* check whether a header is valid
 * assume that header has been read from fptr
 * the position of the indicator of fptr is not certain
 * could be at the beginning of the file, end of the file or 
 * anywhere in the file
 * note that the check is only for this exercise/assignment
 * in general, the format is more complicated
 */

int Is_BMP_Header_Valid(BMP_Header* header, FILE *fptr) {
  // Make sure this is a BMP file
  if (header->type != 0x4d42) {
     return FALSE;
  }
  // skip the two unused reserved fields

  // check the offset from beginning of file to image data
  // essentially the size of the BMP header
  // BMP_HEADER_SIZE for this exercise/assignment
  if (header->offset != BMP_HEADER_SIZE) {
     return FALSE;
  }
      
  // check the DIB header size == DIB_HEADER_SIZE
  // For this exercise/assignment
  if (header->DIB_header_size != DIB_HEADER_SIZE) {
     return FALSE;
  }

  // Make sure there is only one image plane
  if (header->planes != 1) {
    return FALSE;
  }
  // Make sure there is no compression
  if (header->compression != 0) {
    return FALSE;
  }

  // skip the test for xresolution, yresolution

  // ncolours and importantcolours should be 0
  if (header->ncolours != 0) {
    return FALSE;
  }
  if (header->importantcolours != 0) {
    return FALSE;
  }
  
  // Make sure we are getting 24 bits per pixel
  // or 16 bits per pixel
  // only for this assignment
  if (header->bits != 24 && header->bits != 16) {
    return FALSE;
  }

  // fill in extra to check for file size, image size
  // based on bits, width, and height


  if((header->bits * header->width * header->height / 8 - 54 ) == header->imagesize)

   {

    return FALSE;
   }

  return TRUE;
}

/* The input argument is the source file pointer. 
 * The function returns an address to a dynamically allocated BMP_Image only 
 * if the file * contains a valid image file 
 * Otherwise, return NULL
 * If the function cannot get the necessary memory to store the image, also 
 * return NULL
 * Any error messages should be printed to stderr
 */
BMP_Image *Read_BMP_Image(FILE* fptr) {

  // go to the beginning of the file

   BMP_Image *bmp_image = NULL;

   //fseek(fptr, 0 ,SEEK_SET);
  //Allocate memory for BMP_Image*;

  bmp_image = malloc(sizeof(BMP_Image));
  if(bmp_image == NULL)
  {
   fprintf(stderr, "Errpr allocating memory\n");
   return NULL;
  }
  

  //Read the first 54 bytes of the source into the header
   int i;
   i = fread(&(bmp_image->header), sizeof(BMP_Header), 1, fptr);
   if(i ==0)
   {
     fprintf(stderr, "Error writing\n");
	 return NULL;
   }

  
  // if read successful, check validity of header

   if(Is_BMP_Header_Valid(&bmp_image->header, fptr) == FALSE)
   {
     
    fprintf(stderr, "Input file not in expected format\n");
	return NULL;
   }
    

  // Allocate memory for image data
   bmp_image->data=(unsigned char*)malloc(sizeof(unsigned char)*(bmp_image->header.size- 54));
   if(bmp_image->data == NULL)
   {
     fprintf(stderr, "Error allocating memory\n");
	 return NULL;
   } // read in the image data fread(bmp_image->data,sizeof(unsigned char), (bmp_image->header.imagesize), fptr); 

   int j;
   j = fread(bmp_image->data, sizeof(unsigned char), (bmp_image->header.size-54), fptr);
   {
     if(j == 0)
	 {  
	   fprintf(stderr, "Inpute data wrong\n");
	 }
   }
  return bmp_image;
}

/* The input arguments are the destination file pointer, BMP_Image *image.
 * The function write the header and image data into the destination file.
 * return TRUE if write is successful
 * FALSE otherwise
 */
int Write_BMP_Image(FILE* fptr, BMP_Image* image) 
{
   // go to the beginning of the file

   fseek(fptr, 0 ,SEEK_SET);
   // write header
   int i;
   i = fwrite(&(image->header), sizeof(BMP_Header), 1, fptr);
   if(i == 0){
   fprintf(stderr, " Error\n");
   return FALSE;
   }
   // write image data
   int j;
   j = fwrite(image->data,sizeof(unsigned char), (image->header).imagesize, fptr);
   if(j == 0){
   fprintf(stderr, " Error\n");
   return FALSE;
   }

    //if it is 1 for sizeof
   return TRUE;
}

/* The input argument is the BMP_Image pointer. The function frees memory of 
 * the BMP_Image.
 */
void Free_BMP_Image(BMP_Image* image) {


    free(image->data);
	free(image);

}

// Given a BMP_Image, create a new image that is a reflection 
// of the given image
// It could be a horizontal reflection (with the vertical mirror 
// being placed at the center of the image) 
// It could be a vertical reflection (with the horizontal mirror
// being placed at the center of the image)
// It could be a horizontal reflection followed by a vertical
// reflection (or equivalently, a vertical reflection followed by
// horizontal reflection).
// hrefl == 1 implies that a horizontal reflection should take place
// hrefl == 0 implies that a horizontal reflection should not take place
// vrefl == 1 implies that a vertical reflection should take place
// vrefl == 0 implies that a vertical reflection should not take place

BMP_Image *Reflect_BMP_Image(BMP_Image *image, int hrefl, int vrefl)
{
   // create a new image reflected from the given image
  // int pic; 
   int row;
   int col;
   BMP_Image *t_image = NULL;

   printf("w= %d, h = %d, IMsize = %d", image->header.width, image->header.height, image->header.imagesize);
   t_image=malloc(sizeof(BMP_Image));  

   t_image->header = image -> header;

   t_image->data=(unsigned char*)malloc((sizeof(unsigned char)* (image->header.size - 54)));


   int oheight = t_image->header.height;
   int bytewidth2 = (t_image->header.width * t_image->header.bits % 32 + t_image->header.width *t_image->header.bits)/8;
   //int bytewidth1 = (t_image->header.width % 4 + t_image->header.width * 3);
   int pad = (t_image->header.width % 4);
   int b_p = t_image->header.width *3;

    printf("w= %d,realw = %d, h = %d, IMsize = %d", image->header.width, bytewidth2, image->header.height, image->header.imagesize);
   
   if(t_image->data == NULL)
   {
     fprintf(stderr, "Error allocating memory\n");
	 return NULL;
   } 

    
   if(vrefl == 0 && (hrefl == 0))
   {
    for(row = 0; row < (oheight) ; row++)
	{
	 for(col=0; col < (bytewidth2);col++)
	 {
	  t_image->data[row*bytewidth2 + col] = image->data[row*bytewidth2 + col];
	 }
    }
   }


   if(vrefl == 1 && (hrefl == 0))
   {
    for(row = 0; row < (oheight); row++)
	{
	 for(col=0; col < (bytewidth2);col++)
	 {
	  t_image->data[(oheight-1-row)*bytewidth2 + col] = image->data[col+row*bytewidth2];
	 }
    }
   }




   if(hrefl == 1 && (vrefl == 0))
   {
    for(row=0; row < (oheight);row++)
	{
     for(col=0;col < (bytewidth2);col++)
	  {
      if(col > b_p )
	   {
       	  t_image->data[row*bytewidth2 + col] = image->data[row*bytewidth2 - col + bytewidth2];
	   }
      else
       {
          t_image->data[row*bytewidth2 + col] = image->data[(row+1)*bytewidth2 - pad - col/3*3 - 3 + col%3];
       }
	  }
    }
   }

/*
   if(hrefl == 1 && (vrefl == 0))
   {
    for(row=0; row < (oheight);row++)
	{
	   for(pic = 0; pic < b_p/3; pic++)
	   {
	     for(col = 0; col < 3; col ++)
		 {
		  
          if(col+col*pic > b_p - 1)
	      {
       	    t_image->data[row*bytewidth2 + col + col * pic] = image->data[row*bytewidth2 + col + col* pic];
	      }
          else
          {
           t_image->data[b_p-col-col*pic+row*bytewidth2] = image->data[col+col*pic+row*bytewidth2];
          }
	     }
       }
    }
   }
*/

   if((vrefl == 1) && (hrefl == 1))
   {
     //vrefl
    for(row = 0; row < (oheight); row++)
	{
	 for(col=0; col < (bytewidth2);col++)
	 {
	  t_image->data[(oheight-1-row)*bytewidth2 + col] = image->data[col+row*bytewidth2];
	 }
    }
    //hrefl
    for(row=0; row < (oheight);row++)
	{
     for(col=0;col < (bytewidth2);col++)
	  {
      if(col > b_p )
	   {
       	  t_image->data[row*bytewidth2 + col] = image->data[row*bytewidth2 - col + bytewidth2];
	   }
      else
       {
          t_image->data[row*bytewidth2 + col] = image->data[(row+1)*bytewidth2 - pad - col/3*3 - 3 + col%3];
       }
	  }
    }
   }

   return t_image;
}

