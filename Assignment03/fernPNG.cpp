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
    // Check if the user provided the correct number of command line arguments
    if (argc != 5) {
        std::cout << "Usage: ./fernPNG <filename> <width> <height> <iterations>" << std::endl;
        return 0;
    }

    char* filename = argv[1];
    int width = std::atoi(argv[2]);
    int height = std::atoi(argv[3]);
    long iters = std::atol(argv[4]);

    // Ensure dimensions are valid
    if (width <= 0 || height <= 0) {
        std::cout << "Error: Width and height must be positive integers." << std::endl;
        return 0;
    }

    // Initialize the facade class for PNG creation
    PNGWriter writer(width, height);

    // Set up the four affine transforms for the Barnsley Fern
    // Logic: x' = ax + by + c, y' = dx + ey + f
    // Constructor: Transform(a, b, c, d, e, f)
    std::vector<Transform> transforms;

    // Transform 1: Stem (1% probability)
    transforms.push_back(Transform(0.0, 0.0, 0.0, 0.0, 0.16, 0.0));

    // Transform 2: Smaller Leaf (85% probability)
    transforms.push_back(Transform(0.85, 0.04, 0.0, -0.04, 0.85, 1.6));

    // Transform 3: Left Leaf (7% probability)
    transforms.push_back(Transform(0.2, -0.26, 0.0, 0.23, 0.22, 1.6));

    // Transform 4: Right Leaf (7% probability)
    transforms.push_back(Transform(-0.15, 0.28, 0.0, 0.26, 0.24, 0.44));

    // Start iteration from the origin
    Point p(0, 0);

    // Seed the random number generator (fixed seed for reproducibility)
    srand(1); 

    for (long i = 0; i < iters; i++) {
        int r = rand() % 100;

        // Select and apply a transform based on the standard Barnsley probability distribution
        if (r < 1) {
            p = transforms[0] * p;
        } else if (r < 86) {
            p = transforms[1] * p;
        } else if (r < 93) {
            p = transforms[2] * p;
        } else {
            p = transforms[3] * p;
        }

        // Map the simulation coordinates to pixel coordinates
        // Barnsley fern math bounds: x approx [-2.18, 2.65], y approx [0, 9.99]
        
        // Calculate scale to fit the fern height within the image height (with padding)
        double scale = height / 10.5;

        // Map X: Shift right to make positive, scale, and center in the image width
        int px = (int)((p.getX() * scale) + (width / 2.0));
        
        // Map Y: Flip Y axis (since image origin is top-left) and scale
        int py = height - (int)(p.getY() * scale);

        // Draw the pixel using the facade (Lime Green color)
        writer.setPixel(px, py, 50, 205, 50); // LimeGreenish
    }

    // Save the final image to the file
    writer.write(filename);
    std::cout << "Successfully generated " << filename << " with " << iters << " iterations." << std::endl;

    return 0;
}