/*
 * fernPNG.cpp
 * Generates a Barnsley Fern image using Transform, Point, and PNGWriter classes.
 * CS 3505 Assignment 3
 * By Lance Choi
 * Jan 28, 2026
 */

#include <iostream>
#include <cstdlib>
#include <vector>
#include "pngWriter.h"
#include "point.h"
#include "transform.h"

int main(int argc, char* argv[]) {
    // 1. Argument Validation
    if (argc != 5) {
        std::cout << "Usage: ./fernPNG <filename> <width> <height> <iterations>" << std::endl;
        return 0;
    }

    char* filename = argv[1];
    int width = std::atoi(argv[2]);
    int height = std::atoi(argv[3]);
    long iters = std::atol(argv[4]);

    if (width <= 0 || height <= 0) {
        std::cout << "Error: Width and height must be positive integers." << std::endl;
        return 0;
    }

    // 2. Setup PNGWriter
    PNGWriter writer(width, height);

    // 3. Setup Barnsley Fern Transforms
    // Your Transform logic is: x' = ax + by + c, y' = dx + ey + f
    // So the constructor is Transform(a, b, c, d, e, f)
    
    std::vector<Transform> transforms;

    // T1: Stem (1% probability)
    // 0x + 0y + 0, 0x + 0.16y + 0
    transforms.push_back(Transform(0.0, 0.0, 0.0, 0.0, 0.16, 0.0));

    // T2: Smaller Leaf (85% probability)
    // 0.85x + 0.04y + 0, -0.04x + 0.85y + 1.6
    transforms.push_back(Transform(0.85, 0.04, 0.0, -0.04, 0.85, 1.6));

    // T3: Left Leaf (7% probability)
    // 0.2x - 0.26y + 0, 0.23x + 0.22y + 1.6
    transforms.push_back(Transform(0.2, -0.26, 0.0, 0.23, 0.22, 1.6));

    // T4: Right Leaf (7% probability)
    // -0.15x + 0.28y + 0, 0.26x + 0.24y + 0.44
    transforms.push_back(Transform(-0.15, 0.28, 0.0, 0.26, 0.24, 0.44));

    // 4. Run Iterations
    Point p(0, 0); // Start at origin

    // Use a fixed seed for reproducibility, or time(0) for randomness
    srand(1); 

    for (long i = 0; i < iters; i++) {
        int r = rand() % 100;

        // Apply transform based on probability
        if (r < 1) {
            p = transforms[0] * p;
        } else if (r < 86) {
            p = transforms[1] * p;
        } else if (r < 93) {
            p = transforms[2] * p;
        } else {
            p = transforms[3] * p;
        }

        // 5. Map coordinates to pixel space
        // Barnsley fern bounds are approx: x [-2.18, 2.65], y [0, 9.99]
        
        // Scale factor: fit the height of the fern (approx 10) into the image height
        // Leaving a small margin by dividing by 10.5
        double scale = height / 10.5;

        // X: Shift right by 2.18 to make positive, scale, then center horizontally
        // We add width/2 and subtract half the fern's scaled width roughly
        int px = (int)((p.getX() * scale) + (width / 2.0));
        
        // Y: Flip Y axis (because image (0,0) is top-left), and scale
        int py = height - (int)(p.getY() * scale);

        // Draw the pixel (Green color)
        writer.setPixel(px, py, 50, 205, 50); // LimeGreenish
    }

    // 6. Write output
    writer.write(filename);
    std::cout << "Successfully generated " << filename << " with " << iters << " iterations." << std::endl;

    return 0;
}