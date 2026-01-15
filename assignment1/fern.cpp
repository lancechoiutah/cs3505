/*
    Name: Lance Choi
    Date: Jan 15, 2026
    Description: This program generates and displays a Sierpinski fern using
                 an Iterated Function System (IFS) approach. The fern is created
                 by applying a set of affine transformations to points in a 2D
*/


#include <iostream>
#include <cstdlib>  // For rand(), srand()
#include <ctime> // For time()
#include <cmath>

using std::cout;
using std::endl;

//using #ifndef to prevent conflicts with the autograder's definitions
#ifndef width
const int width = 128;
#endif

#ifndef height
const int height = 150;
#endif
const double xMax = 2.75;
const double yMax = 10.1;

const int probabilities[4] = {1, 7, 7, 85};
const double transformations[4][6] = {
    {0.0, 0.0, 0.0, 0.0, 0.16, 0.0},
    {0.2, -0.26, 0.0, 0.23, 0.22, 1.6},
    {-0.15, 0.28, 0.0, 0.26, 0.24, 0.44},
    {0.85, 0.04, 0.0, -0.04, 0.85, 1.6}
};

// Function prototypes
void performIterations(int iterations, unsigned char* image);
int selectTransformation();
void applyTransformation(double& x, double& y, const double* transformation);
void setPixel(double x, double y, unsigned char* image);
bool getPixel(int row, int col, unsigned char* image);
void drawImage(unsigned char* image);

int main(){

    // Calculate size in bytes (8 pixels per byte)
    int Size = (width * height) / 8;
    unsigned char* image = new unsigned char[Size];
    
    // Initialize image to all zeros
    for (int i = 0; i < Size; i++)
    {
        image[i] = 0;
    }

    int iterations;
    cout << "Enter number of iterations: ";
    std::cin >> iterations;

    if (iterations <=0){
        cout << "Iterations must be a positive integer." << endl;
        delete[] image;
        return 0;
    }
    
    std::srand(time(0));

    performIterations(iterations, image);

    drawImage(image);

    delete[] image;

    return 0;
}

// Execute the IFS for a given number of iterations
void performIterations(int iterations, unsigned char* image) {
    double x = 0.0;
    double y = 0.0;

    for (int i = 0; i < iterations; ++i) {
        int tIndex = selectTransformation();
        applyTransformation(x, y, transformations[tIndex]);
        setPixel(x, y, image);
    }
}

// Randomly select a transformation based on defined probabilities
int selectTransformation() {
    int randNum = rand() % 100;
    if (randNum == 0) {
        return 0;
    } else if (randNum < 8) {
        return 1;
    } else if (randNum < 15) {
        return 2;
    } else {
        return 3;
    }
}

// Apply the selected affine transformation to the point (x, y)
void applyTransformation(double& x, double& y, const double* trans) {
    // The 'trans' array represents a 2x3 matrix flattened into a 1D array.
    // Indices [0, 1, 2] correspond to the 1st row: used to calculate the new X.
    // Indices [3, 4, 5] correspond to the 2nd row: used to calculate the new Y.
    
    // Calculate new X using the first 3 coefficients (a, b, c)
    double nextX = trans[0] * x + trans[1] * y + trans[2];

    // Calculate new Y using the last 3 coefficients (d, e, f)
    double nextY = trans[3] * x + trans[4] * y + trans[5];
    x = nextX;
    y = nextY;
}

// Maps the (x, y) coordinate to a specific bit in the image array and sets it to 1.
void setPixel(double x, double y, unsigned char* image) {

    // Map continuous coordinates to discrete pixel grid
    int pixelX = (int)((width - 1) / 2.0   * (1 + x / xMax));
    int pixelY = (int)((height - 1) * (1 - y / yMax));

    // Boundary check to prevent writing outside the array  
    if (pixelX < 0 || pixelX >= width || pixelY < 0 || pixelY >= height) {
        return;
    }

    // Calculate byte index and bit offset
    int index = pixelY * width + pixelX;
    int byteIndex = index / 8;
    int bitIndex = index % 8;

    image[byteIndex] = image[byteIndex] | (1 << bitIndex);
}

// Checks if the pixel at (row, col) is set in the image array
bool getPixel(int row, int col, unsigned char* image) {
    int index = row * width + col;
    int byteIndex = index / 8;
    int bitIndex = index % 8;
    return (image[byteIndex] & (1 << bitIndex)) != 0;
}

// Renders the image to the console
void drawImage(unsigned char* image){
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            if (getPixel(row, col, image)) {
                cout << "#";
            } else {
                cout << " ";
            }
        }
        cout << endl;
    }

}