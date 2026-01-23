/*
 * Point class for CS 3505 assignment 2.
 * A Point holds x and y values.
 * By Eric Heisler and Lance Choi
 * Jan 22, 2026
 */

#include "point.h"
#include <iostream>

// Implement the methods prototyped in point.h
// You can include comments here if desired,
// but they are already documented in point.h

Point::Point(): x(0.0), y(0.0) {}

Point::Point(double x, double y) : x(x), y(y) {}

Point::~Point() {}

// const getters
double Point::getX() const {
    return x;
}

// const getters
double Point::getY() const {
    return y;
}

// Operators
Point Point::operator*(double scaleFactor) {
    return Point(x * scaleFactor, y * scaleFactor);
}

// This doesn't start with Point:: so it is not in the scope of the class.
// However, it is a friend function, so it can access Point's variables.
// Note: Professor's version passes 'point' by value. We keep it that way.
std::ostream& operator<<(std::ostream& output, Point point) {
    output << point.x << ", " << point.y;
    return output;
}