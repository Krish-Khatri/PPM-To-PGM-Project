/*
Krish Khatri
Project 5
10/31/2018

This program is responsible for taking a colored image
in ppm format from a file and applying multiple algorithms
to greyscale the image and print the pixel values to a Given
file.

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "image.h"
#include <math.h>

//Finds the maximum of 3 numbers. Used in computeLightness function.
int maximumValueFinder(int red, int green, int blue)
{
  int maxPixel = 0;
  if (red > green)
  {
    if (red > blue)
    {
      maxPixel = red;
    }
    else
    {
      maxPixel = blue;
    }
  }
  else if (green > blue)
  {
    maxPixel =  green;
  }
  else
  {
    maxPixel = blue;
  }

  return maxPixel;
}

//Finds the miminum of 3 numbers. Used in computeLightness function.
int minimumValueFinder(int red, int green, int blue)
{
  int minimumValue = 0;

  if(red < green && red < blue)
   {
      minimumValue = red;
   }
   else if(green < blue)
   {
      minimumValue = green;
   }
  else
  {
      minimumValue = blue;
  }

  return minimumValue;
}

// Given a filename of a ppm image, read in the image and
// store it in the ImagePPM structure. Return the address ofs
// the ImagePPM structure if the file can be opened or
// NULL otherwise.
ImagePPM *readPPM(char *filename)
{
  char magicIdentifer[3];
  ImagePPM *ImagePPMPointer = malloc(sizeof(ImagePPM));

  FILE *fp;
  fp = fopen (filename,"r");

  if (fp == NULL)
  {
    return NULL;
  }

  fgets(magicIdentifer,3,fp);
  strcpy(ImagePPMPointer -> magic,magicIdentifer);

  fscanf(fp,"%d",&ImagePPMPointer -> width );
  fscanf(fp,"%d",&ImagePPMPointer -> height);
  fscanf(fp,"%d",&ImagePPMPointer -> max_value);

  ImagePPMPointer -> pixels = malloc(sizeof(Pixel *) * ImagePPMPointer -> height);

  for (int i = 0; i < ImagePPMPointer -> height; i++)
  {
    ImagePPMPointer -> pixels[i] = malloc(sizeof(Pixel) * ImagePPMPointer -> width);
  }

  for (int i=0; i<ImagePPMPointer -> height; i++)
  {
      for (int j=0; j<ImagePPMPointer -> width; j++)
       {
                fscanf(fp, "%d", &ImagePPMPointer->pixels[i][j].red);
                fscanf(fp, "%d", &ImagePPMPointer->pixels[i][j].green);
                fscanf(fp, "%d", &ImagePPMPointer->pixels[i][j].blue);
       }
  }


  return ImagePPMPointer;
}

// Write out a pgm image stored in a ImagePGM structure into
// the specified file. Return 1 if writing is successful or
// 0 otherwise.
int writePGM(ImagePGM *pImagePGM, char *filename)
{
  FILE *fp;
  fp = fopen (filename,"w");

  if (fp == NULL)
  {
    return 0;
  }

  fprintf(fp, "%s\n", pImagePGM -> magic);
  fprintf(fp, "%d %d %d\n",pImagePGM -> width, pImagePGM -> height, pImagePGM -> max_value);
  for (int i=0; i< pImagePGM-> height; i++)
  {
      for (int j=0; j< pImagePGM -> width; j++)
       {
            fprintf(fp, "%d ", pImagePGM -> pixels[i][j]);
       }
  }

  fclose(fp);

  return 1;
}

// Convert a ppm image into a pgm image.
// grayscale = R
ImagePGM *extractRed(ImagePPM *pImagePPM)
{
  ImagePGM *PtrImagePGM = malloc(sizeof(ImagePGM));
  strcpy(PtrImagePGM -> magic, "P2");

  PtrImagePGM -> width = pImagePPM -> width;
  PtrImagePGM -> height = pImagePPM -> height;

  PtrImagePGM -> pixels = malloc(sizeof(Pixel *) * PtrImagePGM -> height);

  for (int i = 0; i < PtrImagePGM -> height; i++)
  {
    PtrImagePGM -> pixels[i] = malloc(sizeof(Pixel) * PtrImagePGM -> width);
  }

  for (int i=0; i<PtrImagePGM -> height; i++)
  {
      for (int j=0; j<PtrImagePGM -> width; j++)
       {
              PtrImagePGM->pixels[i][j] = pImagePPM -> pixels[i][j].red;
       }
  }

  int max = 0;
  for (int i=0; i<PtrImagePGM -> height; i++)
  {
      for (int j=0; j<PtrImagePGM -> width; j++)
       {
              if(max < PtrImagePGM->pixels[i][j]) max = PtrImagePGM -> pixels[i][j];
       }
  }

  PtrImagePGM -> max_value = max;

  return PtrImagePGM;
}

// grayscale = G
ImagePGM *extractGreen(ImagePPM *pImagePPM)
{
  ImagePGM *PtrImagePGM = malloc(sizeof(ImagePGM));
  strcpy(PtrImagePGM -> magic, "P2");

  PtrImagePGM -> width = pImagePPM -> width;
  PtrImagePGM -> height = pImagePPM -> height;

  PtrImagePGM -> pixels = malloc(sizeof(Pixel *) * PtrImagePGM -> height);

  for (int i = 0; i < PtrImagePGM -> height; i++)
  {
    PtrImagePGM -> pixels[i] = malloc(sizeof(Pixel) * PtrImagePGM -> width);
  }

  for (int i=0; i<PtrImagePGM -> height; i++)
  {
      for (int j=0; j<PtrImagePGM -> width; j++)
       {
              PtrImagePGM->pixels[i][j] = pImagePPM -> pixels[i][j].green;
       }
  }

  int max = 0;
  for (int i=0; i<PtrImagePGM -> height; i++)
  {
      for (int j=0; j<PtrImagePGM -> width; j++)
       {
              if(max < PtrImagePGM->pixels[i][j]) max = PtrImagePGM -> pixels[i][j];
       }
  }

  PtrImagePGM -> max_value = max;

  return PtrImagePGM;
}
// grayscale = B
ImagePGM *extractBlue(ImagePPM *pImagePPM)
{
  ImagePGM *PtrImagePGM = malloc(sizeof(ImagePGM));
  strcpy(PtrImagePGM -> magic, "P2");

  PtrImagePGM -> width = pImagePPM -> width;
  PtrImagePGM -> height = pImagePPM -> height;

  PtrImagePGM -> pixels = malloc(sizeof(Pixel *) * PtrImagePGM -> height);

  for (int i = 0; i < PtrImagePGM -> height; i++)
  {
    PtrImagePGM -> pixels[i] = malloc(sizeof(Pixel) * PtrImagePGM -> width);
  }

  for (int i=0; i<PtrImagePGM -> height; i++)
  {
      for (int j=0; j<PtrImagePGM -> width; j++)
       {
              PtrImagePGM->pixels[i][j] = pImagePPM -> pixels[i][j].blue;
       }
  }

  int max = 0;
  for (int i=0; i<PtrImagePGM -> height; i++)
  {
      for (int j=0; j<PtrImagePGM -> width; j++)
       {
              if(max < PtrImagePGM->pixels[i][j]) max = PtrImagePGM -> pixels[i][j];
       }
  }

  PtrImagePGM -> max_value = max;

  return PtrImagePGM;
}
// grayscale = (R + G + B) / 3
ImagePGM *computeAverage(ImagePPM *pImagePPM)
{
  ImagePGM *PtrImagePGM = malloc(sizeof(ImagePGM));
  strcpy(PtrImagePGM -> magic, "P2");

  PtrImagePGM -> width = pImagePPM -> width;
  PtrImagePGM -> height = pImagePPM -> height;

  PtrImagePGM -> pixels = malloc(sizeof(Pixel *) * PtrImagePGM -> height);

  for (int i = 0; i < PtrImagePGM -> height; i++)
  {
    PtrImagePGM -> pixels[i] = malloc(sizeof(Pixel) * PtrImagePGM -> width);
  }

  for (int i=0; i<PtrImagePGM -> height; i++)
  {
      for (int j=0; j<PtrImagePGM -> width; j++)
       {
              PtrImagePGM->pixels[i][j] = round((pImagePPM -> pixels[i][j].red + pImagePPM -> pixels[i][j].green + pImagePPM -> pixels[i][j].blue)/3.0);
       }
  }


  int max = 0;
  for (int i=0; i<PtrImagePGM -> height; i++)
  {
      for (int j=0; j<PtrImagePGM -> width; j++)
       {
              if(max < PtrImagePGM->pixels[i][j]) max = PtrImagePGM -> pixels[i][j];
       }
  }

  PtrImagePGM -> max_value = max;

  return PtrImagePGM;
}

// grayscale = (max(R, G, B) + min(R, G, B)) / 2
ImagePGM *computeLightness(ImagePPM *pImagePPM)
{
  ImagePGM *PtrImagePGM = malloc(sizeof(ImagePGM));
  strcpy(PtrImagePGM -> magic, "P2");

  PtrImagePGM -> width = pImagePPM -> width;
  PtrImagePGM -> height = pImagePPM -> height;

  PtrImagePGM -> pixels = malloc(sizeof(Pixel *) * PtrImagePGM -> height);

  for (int i = 0; i < PtrImagePGM -> height; i++)
  {
    PtrImagePGM -> pixels[i] = malloc(sizeof(Pixel) * PtrImagePGM -> width);
  }


  int redVal = 0;
  int greenVal = 0;
  int blueVal = 0;
  int maxPixelValue = 0;
  int minPixelValue = 0;

  for (int i=0; i<PtrImagePGM -> height; i++)
  {
      for (int j=0; j<PtrImagePGM -> width; j++)
       {
              redVal = pImagePPM -> pixels[i][j].red;
              greenVal = pImagePPM -> pixels[i][j].green;
              blueVal = pImagePPM -> pixels[i][j].blue;

              maxPixelValue = maximumValueFinder(redVal,greenVal,blueVal);
              minPixelValue = minimumValueFinder(redVal,greenVal,blueVal);
              PtrImagePGM->pixels[i][j] = round(((maxPixelValue + minPixelValue)/2.0));
        }
  }

  int max = 0;
  for (int i=0; i<PtrImagePGM -> height; i++)
  {
      for (int j=0; j<PtrImagePGM -> width; j++)
       {
              if(max < PtrImagePGM->pixels[i][j]) max = PtrImagePGM -> pixels[i][j];
       }
  }

  PtrImagePGM -> max_value = max;

 return PtrImagePGM;
}

// grayscale = 0.21 R + 0.72 G + 0.07 B
ImagePGM *computeLuminosity(ImagePPM *pImagePPM)
{

    ImagePGM *PtrImagePGM = malloc(sizeof(ImagePGM));
    strcpy(PtrImagePGM -> magic, "P2");

    PtrImagePGM -> width = pImagePPM -> width;
    PtrImagePGM -> height = pImagePPM -> height;

    PtrImagePGM -> pixels = malloc(sizeof(Pixel *) * PtrImagePGM -> height);

    for (int i = 0; i < PtrImagePGM -> height; i++)
    {
      PtrImagePGM -> pixels[i] = malloc(sizeof(Pixel) * PtrImagePGM -> width);
    }

    for (int i=0; i<PtrImagePGM -> height; i++)
    {
        for (int j=0; j<PtrImagePGM -> width; j++)
         {
                PtrImagePGM->pixels[i][j] = round ((0.21 * pImagePPM -> pixels[i][j].red) +  (0.72 * pImagePPM -> pixels[i][j].green) + (0.07 * pImagePPM -> pixels[i][j].blue));
         }
    }


    int max = 0;
    for (int i=0; i<PtrImagePGM -> height; i++)
    {
        for (int j=0; j<PtrImagePGM -> width; j++)
         {
                if(max < PtrImagePGM->pixels[i][j]) max = PtrImagePGM -> pixels[i][j];
         }
    }

    PtrImagePGM -> max_value = max;

    return PtrImagePGM;
}
// based on https://www.johndcook.com/blog/2009/08/24/algorithms-convert-color-grayscale/

// Free the space used by a ppm image.
void freeSpacePPM(ImagePPM *pImagePPM)
{
  for (int a=0; a<pImagePPM -> height; a++)
  {
		free(pImagePPM -> pixels[a]);
  }
  free(pImagePPM);
}
// Free the space used by a pgm image.
void freeSpacePGM(ImagePGM *pImagePGM)
{
  for (int a=0; a<pImagePGM -> height; a++)
  {
		free(pImagePGM -> pixels[a]);
  }
  free(pImagePGM);
}
