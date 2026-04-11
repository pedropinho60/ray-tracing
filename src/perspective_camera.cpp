#include <cmath>

#include "../include/perspective_camera.hpp"

Ray PerspectiveCamera::generate_ray(int row, int col) {
    double h = tan(fovy * M_PI/ 360.0);

    double aspect_ratio = (double)film->width / film->height;

    double top = h;
    double bottom = -h;
    double left = -aspect_ratio * h;
    double right = aspect_ratio * h;

    double u = left + (right - left) * (row + 0.5) / film->width;
    double v = bottom + (top - bottom) * (row + 0.5) / film->height;

    Vector gaze = look_at.sub(look_from);
    Vector vector_w = gaze.normalize();
    Vector vector_u = up.cross_product(vector_w).normalize();
    Vector vector_v = vector_w.cross_product(vector_u).normalize();

    Vector direction = vector_w.add(vector_u.scalar_multiplication(u)).add(vector_v.scalar_multiplication(v));

    return {look_from, direction};
}

std::unique_ptr<PerspectiveCamera> create_perspective_camera(const ParamSet &ps, Point3D look_at,
                                  Point3D look_from, Vector up) {
    auto fovy = ps.retrieve<std::uint8_t>("fovy").value();

    return std::make_unique<PerspectiveCamera>(look_at, look_from, up, fovy);
}
