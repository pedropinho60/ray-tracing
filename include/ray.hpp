#ifndef RAY_HPP
#define RAY_HPP

#include "point_3d.hpp"
#include "vector.hpp"

struct Ray {
  Point3D origin;
  Vector direction;

  Ray(Point3D origin, Vector direction) : origin{origin}, direction{direction} {}
};

#endif // RAY_HPP