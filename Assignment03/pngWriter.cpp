/*
 * pngWriter.cpp
 * Implementation of PNGWriter using libpng.
 * Logic adapted from pngExample.cpp
 * CS 3505 Assignment 3
 * By Lance Choi
 * Jan 28, 2026
 */

#include "pngWriter.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "png.h" // libpng header

PNGWriter::PNGWriter(int w, int h) : width(w), height(h) {
    // Allocate memory for the image (4 bytes per pixel: R,G,B,A)
    // Initialize to 0 (transparent black)
    imageData = new unsigned char[width * height * 4]();
}

PNGWriter::~PNGWriter() {
    if (imageData) {
        delete[] imageData;
    }
}

void PNGWriter::setPixel(int x, int y, int r, int g, int b) {
    // Boundary check
    if (x < 0 || x >= width || y < 0 || y >= height) return;

    // Calculate the index in the 1D array
    int offset = (y * width + x) * 4;
    
    imageData[offset + 0] = (unsigned char)r;   // Red
    imageData[offset + 1] = (unsigned char)g;   // Green
    imageData[offset + 2] = (unsigned char)b;   // Blue
    imageData[offset + 3] = 255;                // Alpha (255 = Opaque)
}

void PNGWriter::write(const char* filename) {
    FILE* fp = fopen(filename, "wb");
    if (!fp) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    // Initialize write structure
    png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png) {
        fclose(fp);
        abort();
    }

    // Initialize info structure
    png_infop info = png_create_info_struct(png);
    if (!info) {
        png_destroy_write_struct(&png, NULL);
        fclose(fp);
        abort();
    }

    // Setup error handling
    if (setjmp(png_jmpbuf(png))) {
        png_destroy_write_struct(&png, &info);
        fclose(fp);
        abort();
    }

    png_init_io(png, fp);

    // Set header info (8-bit depth, RGBA)
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

    // Create row pointers needed by libpng
    png_bytep* imageRows = new png_bytep[height];
    for (int y = 0; y < height; y++) {
        imageRows[y] = &imageData[y * width * 4];
    }

    // Write the actual data
    png_write_info(png, info);
    png_write_image(png, imageRows);
    png_write_end(png, NULL);

    // Cleanup
    delete[] imageRows;
    png_destroy_write_struct(&png, &info);
    fclose(fp);
}