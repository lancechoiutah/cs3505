/*
 * Name: Lance Choi
 * Date: 2026-01-22
 * Description: Implementation of the Transform class logic.
 */

#include "transform.h"
#include "point.h"

Transform::Transform(double aVal, double bVal, double cVal, double dVal, double eVal, double fVal)
    : a(aVal), b(bVal), c(cVal), d(dVal), e(eVal), f(fVal) {}

void Transform::getParameters(double* array) const {
    array[0] = a; array[1] = b; array[2] = c;
    array[3] = d; array[4] = e; array[5] = f;
}


// X' = ax + by + c 
// Y' = dx + ey + f
Point Transform::operator*(const Point& p) const {
    double nextX = a * p.getX() + b * p.getY() + c;
    double nextY = d * p.getX() + e * p.getY() + f;
    return Point(nextX, nextY);
}

std::ostream& operator<<(std::ostream& out, const Transform& t) {
    out << "[" << t.a << ", " << t.b << ", " << t.c << ", " 
        << t.d << ", " << t.e << ", " << t.f << "]";
    return out;
}

Point& operator*=(Point& p, const Transform& t) {
    double nextX = t.a * p.x + t.b * p.y + t.c;
    double nextY = t.d * p.x + t.e * p.y + t.f;

    p.x = nextX;
    p.y = nextY;

    return p;
}