/*
 * Name: Lance Choi
 * Date: 2026-01-22
 * Description: Test program to verify Point and Transform classes.
 */

#include <iostream>
#include <fstream>
#include "point.h"
#include "transform.h"

using namespace std;

int main() {
    Point p(1.0, 0.0);

    // Define a Transform object with specific parameters
    Transform t(1.0113, -0.1788, 0.0, 0.1788, 1.0113, 0.0);


    for (int i = 0; i < 200; i++) {
        p *= t;

        cout << p << endl;
    }

    return 0;
}