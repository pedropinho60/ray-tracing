#ifndef POINT_3D_HPP
#define POINT_3D_HPP

#include "vector.hpp"
#include <ostream>

struct Point3D {
  double x;
  double y;
  double z;

  Point3D() {x = 0.0; y = 0.0; z = 0.0;}
  Point3D(double x, double y, double z) : x{x}, y{y}, z{z} {}

  Point3D add(Vector vector);
  Vector sub(Point3D other);

  friend std::ostream& operator<<(std::ostream& os, const Point3D& pt) {
    os << "(" << pt.x << "," << pt.y << "," << pt.z <<")";
    return os;
  }
};

#endif // POINT_3D_HPP
