#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

using std::cout;
using std::endl;

const int  width = 128;
const int  height = 150;
const double xMax = 2.75;
const double yMax = 10.1;

const int probabilities[4] = {1, 7, 7, 85};
const double transformations[4][6] = {
    {0.0, 0.0, 0.0, 0.0, 0.16, 0.0},
    {0.2, -0.26, 0.0, 0.23, 0.22, 1.6},
    {-0.15, 0.28, 0.0, 0.26, 0.24, 0.44},
    {0.85, 0.04, 0.0, -0.04, 0.85, 1.6}
};

void performIterations(int iterations, unsigned char* image);
int selectTransformation();
void applyTransformation(double& x, double& y, const double* transformation);
void setPixel(double x, double y, unsigned char* image);
bool getPixel(int row, int col, unsigned char* image);
void drawImage(unsigned char* image);

int main(){

}

void performIterations(int iterations, unsigned char* image) {
    double x = 0.0;
    double y = 0.0;

    for (int i = 0; i < iterations; ++i) {
        int tIndex = selectTransformation();
        applyTransformation(x, y, transformations[tIndex]);
        setPixel(x, y, image);
    }
}

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

void applyTransformation(double& x, double& y, const double* trans) {
    double nextX = trans[0] * x + trans[1] * y + trans[4];
    double nextY = trans[2] * x + trans[3] * y + trans[5];
    x = nextX;
    y = nextY;
}

void setPixel(double x, double y, unsigned char* image) {
    int pixelX = (int)((width - 1) / 2 * (1 + x / xMax));
    int pixelY = (int)((height - 1) * (1 - y / yMax));

    if (pixelX < 0 || pixelX >= width || pixelY < 0 || pixelY >= height) {
        return;
    }
}

bool getPixel(int row, int col, unsigned char* image) {
    // Fallback
}

void drawImage(unsigned char* image){

}