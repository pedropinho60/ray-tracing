#ifndef POINT_3D_HPP
#define POINT_3D_HPP

#include <cstdint>

#include "vector.hpp"

struct Point3D {
  double x;
  double y;
  double z;

  Point3D(double x, double y, double z) : x{x}, y{y}, z{z} {}

  Point3D add(Vector vector);
  Vector sub(Point3D other);
};

#endif // POINT_3D_HPP
