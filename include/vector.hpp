#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstdint>

struct Vector {
  double x;
  double y;
  double z;

  Vector(double x, double y, double z) : x{x}, y{y}, z{z} {}

  Vector add(Vector other);
  double dot_product(Vector other);
  Vector cross_product(Vector other);
  Vector normalize();
  Vector scalar_multiplication(double scalar);
};

#endif // VECTOR_HPP
