/*
 * pngWriter.h
 * Facade class for libpng to simplify PNG creation.
 * CS 3505 Assignment 3
 * By Lance Choi
 * Jan 28, 2026
 */

#ifndef PNGWRITER_H
#define PNGWRITER_H

class PNGWriter {
private:
    int width;
    int height;
    unsigned char* imageData; // Stores RGBA pixel data

public:
    // Constructor: Allocates memory and sets dimensions
    PNGWriter(int width, int height);

    // Destructor: Frees memory
    ~PNGWriter();

    // Sets the color of a specific pixel (r, g, b are 0-255)
    void setPixel(int x, int y, int r, int g, int b);

    // Writes the current image data to a PNG file
    void write(const char* filename);
};

#endif