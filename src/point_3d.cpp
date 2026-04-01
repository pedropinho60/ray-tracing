#include "../include/point_3d.hpp"

Point3D Point3D::add(Vector vector) {
    return {this->x + vector.x, this->y + vector.y, this->z + vector.z};
}

Vector Point3D::sub(Point3D other) {
    return {this->x - other.x, this->y - other.y, this->z - other.z};
}
