#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <ostream>

struct Vector {
  double x;
  double y;
  double z;

  Vector() {x = 0.0; y = 0.0; z = 0.0;}
  Vector(double x, double y, double z) : x{x}, y{y}, z{z} {}

  Vector add(Vector other) const;
  Vector sub(Vector other) const;
  double dot_product(Vector other) const;
  Vector cross_product(Vector other) const;
  Vector normalize() const;
  Vector scalar_multiplication(double scalar) const;

  friend std::ostream& operator<<(std::ostream& os, const Vector& vec) {
    os << "(" << vec.x << "," << vec.y << "," << vec.z << ")";
    return os;
  }
};

#endif // VECTOR_HPP
