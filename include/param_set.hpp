#ifndef PARAM_SET_HPP
#define PARAM_SET_HPP

#include <map>
#include <memory>
#include <string>

#include "object.hpp"
#include "value_type.hpp"

class ParamSet {
  using Dictionary = std::map<std::string, std::shared_ptr<Object>>;

  Dictionary dictionary;

public:
  template <typename T> void assign(const std::string &key, const T &value) {
    dictionary[key] = std::make_shared<ValueType<T>>(value);
  }
};

#endif // PARAM_SET_HPP
