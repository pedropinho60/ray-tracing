#ifndef APP_HPP
#define APP_HPP

#include <memory>

#include "background.hpp"
#include "film.hpp"

class App {
  static std::unique_ptr<Background> bg;
  static std::unique_ptr<Film> film;

public:
  static void render();
};

#endif // APP_HPP
