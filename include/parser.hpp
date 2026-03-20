#ifndef PARSER_HPP
#define PARSER_HPP

#include "param_set.hpp"

class Parser {
public:
  void parse(ParamSet &ps, const char *file);
};

#endif // PARSER_HPP
