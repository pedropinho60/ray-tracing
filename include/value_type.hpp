#ifndef VALUE_TYPE_HPP
#define VALUE_TYPE_HPP

#include "object.hpp"

template <typename T> class ValueType : Object {
public:
  T value;

  ValueType(const T &value = T{}) { this->value = value; }
};

#endif // VALUE_TYPE_HPP
