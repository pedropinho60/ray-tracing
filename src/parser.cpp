#include "../include/parser.hpp"
#include "../include/tinyxml2.h"
#include <iostream>

void Parser::parse(ParamSet &ps, const char *filename) {
  tinyxml2::XMLDocument doc;
  if (doc.LoadFile(filename) != tinyxml2::XML_SUCCESS) {
    std::cerr << "Error loading the XML file!\n";
    return;
  }
}
