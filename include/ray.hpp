#ifndef RAY_HPP
#define RAY_HPP

#include "point_3d.hpp"
#include "vector.hpp"

struct Ray {
  Point3D origin;
  Vector direction;

  Ray(Point3D origin, Vector direction) : origin{origin}, direction{direction} {}

  Point3D expand(double t) {
    return origin.add(direction.scalar_multiplication(t));
  }

  friend std::ostream& operator<<(std::ostream& os, const Ray& ray) {
    os << "[o=" << ray.origin << ", d=" << ray.direction << "]";
    return os;
  }
};

#endif // RAY_HPP
