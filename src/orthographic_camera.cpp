#include "../include/orthographic_camera.hpp"
#include <cassert>

OrthographicCamera::OrthographicCamera(WindowSize dimensions, Point3D look_at,
                                       Point3D look_from, Vector up)
    : Camera(look_at, look_from, up), left{dimensions.left},
      right{dimensions.right}, bottom{dimensions.bottom}, top{dimensions.top} {}

Ray OrthographicCamera::generate_ray(int row, int col) {
    assert(film && "film is null");

    double u = left + (right - left) * (col + 0.5) / film->width;
    double v = bottom + (top - bottom) * (film->height - 1 - row + 0.5) / film->height;

    Vector gaze = look_at.sub(look_from);
    Vector vector_w = gaze.normalize();
    Vector vector_u = vector_w.cross_product(up).normalize();
    Vector vector_v = vector_u.cross_product(vector_w).normalize();

    Point3D origin = look_from.add(vector_u.scalar_multiplication(u))
                         .add(vector_v.scalar_multiplication(v));

    return {origin, vector_w};
}

std::unique_ptr<OrthographicCamera>
create_orthographic_camera(const ParamSet &ps, Point3D look_at,
                           Point3D look_from, Vector up) {
    auto screen_window = ps.retrieve<WindowSize>("screen_window").value();

    return std::make_unique<OrthographicCamera>(screen_window, look_at,
                                                look_from, up);
}
