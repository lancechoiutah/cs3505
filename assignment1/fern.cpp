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

