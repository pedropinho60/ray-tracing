#ifndef PARAM_SET_HPP
#define PARAM_SET_HPP

#include <map>
#include <memory>
#include <optional>
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

  template <typename T>
  std::optional<T> retrieve(const std::string &key) const {
    auto result = dictionary.find(key);

    if (result == dictionary.end()) { 
      return std::nullopt;
    }

    const auto& [the_key, sptr] = *result;

    try {
      auto data = dynamic_cast<ValueType<T>&>(*sptr);

      return data.value;
    } catch (const std::bad_cast& e) {
      return std::nullopt;
    }
  }
};

#endif // PARAM_SET_HPP
