#ifndef SURFEL_HPP
#define SURFEL_HPP

#include "point_3d.hpp"

class Surfel {
public:
    Point3D point;

    Surfel(Point3D point) : point{point} {}
};

#endif // SURFEL_HPP
