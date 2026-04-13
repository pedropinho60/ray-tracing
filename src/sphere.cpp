#include "../include/sphere.hpp"

bool Sphere::intersect(const Ray& ray, Surfel* surfel) {
    return true;
}

bool Sphere::intersect_p(const Ray& ray) {
  Point3D o = ray.origin;
  Vector d_hat = ray.direction.normalize();

  Vector oc = o.sub(center);

  double parallel_len = oc.dot_product(d_hat);
  Vector oc_perp = oc.sub(d_hat.scalar_multiplication(parallel_len));

  double delta = radius*radius - oc_perp.dot_product(oc_perp);

  return delta >= 0;
}

Sphere create_sphere(const ParamSet& ps) {
    auto radius = ps.retrieve<double>("radius").value();
    auto center = ps.retrieve<Point3D>("center").value();

    return {center, radius};
}
