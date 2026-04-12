#include <math.h>

#include "../include/vector.hpp"

Vector Vector::add(Vector other) const {
    return {this->x + other.x, this->y + other.y, this->z + other.z};
}

Vector Vector::sub(Vector other) const {
    return {this->x - other.x, this->y - other.y, this->z - other.z};
}

double Vector::dot_product(Vector other) const {
    return this->x * other.x + this->y * other.y + this->z * other.z;
}

Vector Vector::cross_product(Vector other) const {
    return {
        other.y * this->z - other.z * this->y,
        other.z * this->x - other.x * this->z,
        other.x * this->y - other.y * this->x,
    };
}

Vector Vector::normalize() const {
    double magnitude = sqrt(this->x * this->x + this->y * this->y + this->z * this->z);

    return {this->x / magnitude, this->y / magnitude, this->z / magnitude};
}

Vector Vector::scalar_multiplication(double scalar) const {
    return {this->x * scalar, this->y * scalar, this->z * scalar};
}
