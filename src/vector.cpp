#include <math.h>

#include "../include/vector.hpp"

Vector Vector::add(Vector other) {
    return {this->x + other.x, this->y + other.y, this->z + other.z};
}

double Vector::dot_product(Vector other) {
    return this->x * other.x + this->y * other.y + this->z + other.z;
}

Vector Vector::cross_product(Vector other) {
    return {
        other.y * this->z - other.z * this->y,
        other.z * this->x - other.x * this->z,
        other.x * this->y - other.y * this->x,
    };
}

Vector Vector::normalize() {
    double magnitude = sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2));

    return {this->x / magnitude, this->y / magnitude, this->z / magnitude};
}

Vector Vector::scalar_multiplication(double scalar) {
    return {this->x * scalar, this->y * scalar, this->z * scalar};
}
