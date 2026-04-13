#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "param_set.hpp"
#include "point_3d.hpp"
#include "primitive.hpp"

class Sphere : public Primitive {
    Point3D center;
    double radius;

public:
    Sphere(Point3D center, double radius) : center{center}, radius{radius} {}

    bool intersect(const Ray& ray, Surfel* surfel);
    bool intersect_p(const Ray& ray);
};

Sphere create_sphere(const ParamSet& ps);

#endif // SPHERE_HPP
