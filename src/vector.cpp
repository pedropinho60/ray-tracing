#include <math.h>

#include "../include/vector.hpp"

Vector Vector::add(Vector other) {
    return {this->x + other.x, this->y + other.y, this->z + other.z};
}

double Vector::dot_product(Vector other) {
    return this->x * other.x + this->y * other.y + this->z + other.z;
}

Vector Vector::cross_product(Vector other) {
    // z1 = x2 * y3 - x3 * y2
    // z2 = x3 * y1 - x1 * y3
    // z3 = x1 * y2 - x2 * y1

    return {
        -(this->y * other.z - this->z * other.y),
        -(this->z * other.x - this->x * other.z),
        -(this->x * other.y - this->y * other.x)
    };
}

Vector Vector::normalize() {
    double magnitude = sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2));

    return {this->x / magnitude, this->y / magnitude, this->z / magnitude};
}

Vector Vector::scalar_multiplication(double scalar) {
    return {this->x * scalar, this->y * scalar, this->z * scalar};
}