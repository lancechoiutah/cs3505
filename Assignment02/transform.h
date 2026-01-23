/*
 * Name: Lance Choi
 * Date: 2026-01-22
 * Description: Header file for the Transform class representing an affine transformation.
 */

#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <iostream>

// Forward declaration to avoid circular dependency
class Point;

class Transform {
private:
    double a, b, c, d, e, f;

public:
    Transform(double aVal, double bVal, double cVal, double dVal, double eVal, double fVal);

    void getParameters(double* array) const;

    Point operator*(const Point& p) const;

    friend std::ostream& operator<<(std::ostream& out, const Transform& t);

    friend Point& operator*=(Point& p, const Transform& t);
};

#endif