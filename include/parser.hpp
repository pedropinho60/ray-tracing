#ifndef PARSER_HPP
#define PARSER_HPP

#include <functional>

#include "param_set.hpp"

using ConverterFunction
  = std::function<bool(const std::string&, const std::string&, ParamSet*)>;

class Parser {
public:
  static void parse(const char *file);
};

#endif // PARSER_HPP
