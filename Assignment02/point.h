#ifndef POINT_H
#define POINT_H

/*
 * Point class for CS 3505 assignment 2.
 * A Point holds x and y values.
 * By Eric Heisler and Lance Choi
 * Jan 22, 2026
 */

#include <iostream> // for ostream

class Transform;

class Point {
private:
    double x, y;

public:
    // default constructor initializes to (0, 0)
    Point();

    // This constructor takes initial values for x and y
    Point(double initX, double initY);

    // The destructor does nothing because we didn't allocate any new memory
    ~Point();

    // Getter for the x value
    double getX() const;

    // Getter for the y value
    double getY() const;

    // Operators
    Point operator*(double scaleFactor);

    // Friend insertion operator to make printing easy
    friend std::ostream& operator<<(std::ostream& output, Point point);

    // Transform class need to access Point's private members x and y. So we declare it as a friend.
    friend Point& operator*=(Point& point, const Transform& transform);
};

#endif // include guard for POINT_H