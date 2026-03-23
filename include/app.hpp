#ifndef APP_HPP
#define APP_HPP

#include <memory>

#include "background.hpp"
#include "film.hpp"
#include "param_set.hpp"

class App {
  static std::unique_ptr<Background> bg;
  static std::unique_ptr<Film> film;

public:
  static void render();

  static void world_begin(const ParamSet &ps);
  static void world_end(const ParamSet &ps);
  static void create_background(const ParamSet &ps);
  static void create_film(const ParamSet &ps);
};

#endif // APP_HPP
