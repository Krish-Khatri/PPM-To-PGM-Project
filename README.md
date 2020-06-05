# ppm-to-pgm-project
A simple c project that converts a ppm image to pgm image using multiple algorithms.
This program converts a color image in ppm format into a grayscale image in pgm format.
It uses one of the following six methods to convert the image:

  1. red (use the red intensity as the grayscale intensity)
  2. green (use the green intensity as the grayscale intensity)
  3. blue (use the blue intensity as the grayscale intensity)
  4. average (use the average of red, green and blue intensities as the grayscale intensity)
  5. ligntness (compute the lightness from red, green and blue intensities, and use the lightness
     as the grayscale intensity)
  6. luminosity (compute the luminosity from red, green and blue intensities, and use the
     luminosity as the grayscale intensity)
 
To Test the program with large files, it is recommended you use gimp to convert any image to a ppm format.
Simply load an existing image that you have into GIMP, then
select the File -> Export As option and use ppm as the file extension of the exported file. Make
sure to click ASCII when asked how to export. 

Please note when GIMP converts an image into a
ppm file, it puts a comment line (a line starting with #) after the magic identifier. You need to
delete that comment line. Once your program
has converted a ppm image into a pgm image, you can use GIMP again to view the pgm image.
