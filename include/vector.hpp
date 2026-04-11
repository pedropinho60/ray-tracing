#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <ostream>

struct Vector {
  double x;
  double y;
  double z;

  Vector() {x = 0.0; y = 0.0; z = 0.0;}
  Vector(double x, double y, double z) : x{x}, y{y}, z{z} {}

  Vector add(Vector other);
  double dot_product(Vector other);
  Vector cross_product(Vector other);
  Vector normalize();
  Vector scalar_multiplication(double scalar);

  friend std::ostream& operator<<(std::ostream& os, const Vector& vec) {
    os << "(" << vec.x << "," << vec.y << "," << vec.z << ")";
    return os;
  }
};

#endif // VECTOR_HPP
