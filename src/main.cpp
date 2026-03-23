#include "../include/app.hpp"
#include "../include/parser.hpp"

int main(int argc, char* argv[]) {
  const char* filename;
  if (argc > 1) {
    filename = argv[1];
  } else {
    filename = "scenes/scene01.xml";
  }

  Parser::parse(filename);

  App::render();
}

// parser xml
//
// menu
