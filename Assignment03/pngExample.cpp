/*
 * A simple libpng example program
 * 
 * Modified by Yoshimasa Niwa to make it much simpler
 * and support all defined color_type.
 *
 * Modified by Eric Heisler to make it a minimal png writing
 * example.
 *
 * Copyright 2002-2010 Guillaume Cottenceau.
 *
 * This software may be freely redistributed under the terms
 * of the X11 license.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include "png.h"

// These dimensions are updated in main with user input
int width = 0;
int height = 0;
// Each pixel requires 4 bytes for [red, green, blue, alpha]
unsigned char* imageData; // unsigned char is equivalent to png_byte
png_bytep* imageRows; // png_bytep is a pointer type, so png_bytep* is a pointer to a pointer

/*
Writes the imageData to a png file with the given name.
Param: filename including ".png"
*/
void writePNGFile(char* filename) {
    FILE* fp = fopen(filename, "wb");
    if(!fp) abort();
    
    png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png) abort();
    
    png_infop info = png_create_info_struct(png);
    if (!info) abort();
    
    if (setjmp(png_jmpbuf(png))) abort();
    
    png_init_io(png, fp);
    // Output is 8bit depth, RGBA format.
    png_set_IHDR(
        png,
        info,
        width, height,
        8,
        PNG_COLOR_TYPE_RGBA,
        PNG_INTERLACE_NONE,
        PNG_COMPRESSION_TYPE_DEFAULT,
        PNG_FILTER_TYPE_DEFAULT
    );
    
    // pnglib requires the image stored as rows
    for(int y = 0; y < height; y++) {
        imageRows[y] = &imageData[y * width * 4]; // pointers to the first pixel of each row
    }
    
    // These three commands write the png file
    png_write_info(png, info);
    png_write_image(png, imageRows);
    png_write_end(png, NULL);
    
	// Close the file and clean up resources used by pnglib
    fclose(fp);
    png_destroy_write_struct(&png, &info);
}

/*
Makes a 5-banded test pattern:
red, green, blue, white, black
*/
void testPattern() {
    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            int offset = (y * width + x) * 4;
            imageData[offset + 0] = 0; // red
            imageData[offset + 1] = 0; // green
            imageData[offset + 2] = 0; // blue
            imageData[offset + 3] = 255; // alpha (keep at 255 for no transparency)
            switch(y * 5 / height){
                case 0: // red
                    imageData[offset + 0] = 255;
                    break;
                case 1: // green
                    imageData[offset + 1] = 255;
                    break;
                case 2: // blue
                    imageData[offset + 2] = 255;
                    break;
                case 3: // white
                    imageData[offset + 0] = 255;
                    imageData[offset + 1] = 255;
                    imageData[offset + 2] = 255;
            }
        }
    }
}

/*
Creates a png image file with a test pattern.
Three command line arguments are required: output file name, width, height
*/
int main(int argc, char* argv[]) {
  if(argc != 4){
    std::cout << "Requires 3 arguments: filename, width, height" << std::endl;
    return 0;
  }
  std::stringstream widthStream(argv[2]);
  std::stringstream heightStream(argv[3]);
  widthStream >> width;
  heightStream >> height;
  
  if(width < 1 || height < 1){
    std::cout << "Width and height were not valid values > 0" << std::endl;
    return 0;
  }
  
  imageData = new unsigned char[height * width * 4] {};
  imageRows = new png_bytep[height] {};
  
  testPattern();
  writePNGFile(argv[1]);
  
  delete[] imageData;
  delete[] imageRows;
  
  return 0;
}