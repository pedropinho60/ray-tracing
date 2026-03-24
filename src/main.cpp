#include <iostream>

#include "../include/app.hpp"

int main(int argc, char* argv[]) {
  if (argc <= 1) {
    std::cerr << "Error: Missing scene file name\n";
    return 1;
  }

  const char* filename = argv[1];

  App::run(filename);

  App::render();
}
