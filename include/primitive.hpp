#ifndef PRIMITIVE_HPP
#define PRIMITIVE_HPP

#include <memory>

#include "ray.hpp"
#include "material.hpp"
#include "surfel.hpp"

class Primitive {
public:
    std::shared_ptr<Material> material;

    virtual ~Primitive() = default;
    virtual bool intersect(const Ray& ray, Surfel* surfel) = 0;
    virtual bool intersect_p(const Ray& ray) = 0;
};

#endif // PRIMITIVE_HPP
