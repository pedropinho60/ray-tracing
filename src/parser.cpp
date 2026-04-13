#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <cassert>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <sstream>

#include "../include/app.hpp"
#include "../include/window_size.hpp"
#include "../include/rgb_color.hpp"
#include "../include/parser.hpp"
#include "../lib_tinyxml2/tinyxml2.h"

namespace fs = std::filesystem;

static std::string str_to_lower(const char* c_str) {
  std::string str{c_str};
  std::transform(str.begin(), str.end(), str.begin(), ::tolower);

  return str;
}

template <typename T>
bool convert(const std::string& attr_name, const std::string& attr_content, ParamSet* ps) {
  assert(ps);
  std::istringstream iss{ attr_content };      // Make `attr_content` a stream to extract data from.
  T single_value{};                            // Stores a single value of type T...
  std::vector<T> multiple_values;              // ... or use this to try to store multiple values.
  bool input_string_still_has_values{ true };  // Assume we have values to read from.
  // [1]: Try to read several T-values from the input string `attr_content`.
  while (input_string_still_has_values and not iss.eof()) {
    // Slightly different treatment if T is bool
    if constexpr (std::is_same_v<T, bool>) {
      iss >> std::boolalpha >> single_value;  // Use std::boolalpha to read "true" ou "false"
    } else {
      iss >> single_value;  // Regular extraction.
    }
    // Failed while trying to extract value this time?
    if (iss.fail()) {
      if (multiple_values.empty()) {  // Is it completely empty?
        return false;                 // Failed! The input was empty all along.
      }
      // If we got here, at least one value was successfully extracted from `attr_content`
      input_string_still_has_values = false;
      break;
    }
    // Store the single value into a vector & look for more.
    multiple_values.push_back(single_value);
  }
  // [2]: If we found only one value in the vector, we get rid of the vector and store this single
  // value in the ParamSet. Otherwise, we store the entire vector.
  if (multiple_values.size() == 1) {
    single_value = multiple_values[0];
    ps->assign(attr_name, single_value);
  } else {
    ps->assign(attr_name, multiple_values);
  }
  return true;
}

bool convert_rgb_color(const std::string& attr_name, const std::string& attr_content, ParamSet* ps) {
  assert(ps);
  std::istringstream iss{ attr_content };
  int red, green, blue;

  if (!(iss >> red >> green >> blue)) {
    return false;
  }

  if (red < 0 || red > 255 ||
    green < 0 || green > 255 ||
    blue < 0 || blue > 255) {
    return false;
  }

  RGBColor color{static_cast<uint8_t>(red), static_cast<uint8_t>(green), static_cast<uint8_t>(blue)};
  ps->assign(attr_name, color);

  return true;
}

bool convert_point_3d(const std::string& attr_name, const std::string& attr_content, ParamSet* ps) {
  assert(ps);
  std::istringstream iss{ attr_content };
  double x, y, z;

  if (!(iss >> x >> y >> z)) {
    return false;
  }

  Point3D point = {x, y, z};
  ps->assign(attr_name, point);

  return true;
}

bool convert_vector_3d(const std::string& attr_name, const std::string& attr_content, ParamSet* ps) {
  assert(ps);
  std::istringstream iss{ attr_content };
  double x, y, z;

  if (!(iss >> x >> y >> z)) {
    return false;
  }

  Vector vec = {x, y, z};
  ps->assign(attr_name, vec);

  return true;
}

bool convert_window_size(const std::string& attr_name, const std::string& attr_content, ParamSet* ps) {
  assert(ps);
  std::istringstream iss{ attr_content };
  double l, r, b, t;

  if (!(iss >> l >> r >> b >> t)) {
    return false;
  }

  WindowSize ws = {l, r, b, t};
  ps->assign(attr_name, ws);

  return true;
}

std::unordered_map<std::string, std::vector<std::string>> tag_catalog{
  {
    "lookat",
    {
      "look_from",
      "look_at",
      "up",
    },
  },
  {
    "camera",
    {
      "type",
      "screen_window",
      "fovy",
    },
  },
  {
    "background",
    {
      "type",
      "filename",
      "mapping",
      "color",
      "tl",
      "tr",
      "bl",
      "br",
    },
  },
  {
    "object",
    {
      "type",
      "radius",
      "center",
    },
  },
  {
    "film",
    {
      "type",
      "filename",
      "img_type",
      "x_res",
      "y_res",
      "w_res",
      "h_res",
      "crop_window",
      "gamma_corrected",
    },
  },
  {
    "world_begin",
    { "" }, 
  },
  {
    "world_end",
    { "" },  
  },
};

std::unordered_map<std::string, std::function<void(const ParamSet&)>> api_functions{
  { "lookat", App::lookat },
  { "camera", App::create_camera },
  { "background", App::create_background },
  { "world_begin", App::world_begin },
  { "object", App::create_object },
  { "world_end", App::world_end },
  { "film", App::create_film },
};

std::unordered_map<std::string, ConverterFunction> converters{
  { "type", convert<std::string> },  // "type" must be a string.
  { "name", convert<std::string> },  // "name" must be a string.
  //
  { "color", convert_rgb_color },  // "color" is a Color24 with 3 fields.
  { "flip", convert<bool> },
  // Background attributes.
  { "mapping", convert<std::string> },
  { "bl", convert_rgb_color },
  { "tl", convert_rgb_color },
  { "tr", convert_rgb_color },
  { "br", convert_rgb_color },
  // Image attributes
  { "x_res", convert<std::uint16_t> },
  { "y_res", convert<std::uint16_t> },
  { "w_res", convert<std::uint16_t> },
  { "h_res", convert<std::uint16_t> },
  { "filename", convert<std::string> },
  { "img_type", convert<std::string> },
  { "gamma_corrected", convert<bool> },
  // Lookat attributes.
  { "look_at", convert_point_3d },
  { "look_from", convert_point_3d },
  { "up", convert_vector_3d },
  // Camera attributes.
  { "screen_window", convert_window_size },
  { "fovy", convert<std::uint16_t> },
  // Sphere attributes.
  { "radius", convert<double> },
  { "center", convert_point_3d },
};

bool is_valid_tag(std::string_view tag_name) {
  auto tag_query{ tag_catalog.find((std::string)tag_name) };
  return tag_query != tag_catalog.end();
}

bool is_valid_attribute(std::string_view tag_name, std::string_view attribute_name) {
  auto attribute_list{tag_catalog[(std::string)tag_name]};
  auto attr_query = std::find(attribute_list.begin(), attribute_list.end(), attribute_name);

  return attr_query != attribute_list.end();
}

void parse_attribute(const std::string& attr_name /* IN value */,
                     const std::string& attr_content /* IN value */,
                     ParamSet* ps /* OUT value*/) {
  std::ostringstream oss;
  auto converter_func = converters[attr_name];
  if (converter_func) {  // Do we have one defined?
    converter_func(attr_name, attr_content, ps);
  }
}

void Parser::parse(const char* filename) {
  tinyxml2::XMLDocument doc;

  if (doc.LoadFile(filename) != tinyxml2::XML_SUCCESS) {
    std::cerr << "Error loading the XML file!" << '\n';
    return;
  }

  tinyxml2::XMLElement* root = doc.RootElement();

  if (root == nullptr) {
    std::cerr << "Root node of the XML tree was not found!" << '\n';
    return;
  }

  for (tinyxml2::XMLElement* child_node = root->FirstChildElement(); child_node != nullptr; child_node = child_node->NextSiblingElement()) {
    std::string tag_name = str_to_lower(child_node->Name());

    if (not is_valid_tag(tag_name)) {
      continue;  
    }

    ParamSet ps;

    for (const tinyxml2::XMLAttribute* attr = child_node->FirstAttribute(); attr != nullptr; attr = attr->Next()) {
      std::string attribute_name{str_to_lower(attr->Name())};

      if (not is_valid_attribute(tag_name, attribute_name)) {
        continue;
      }

      std::string attribute_value{ str_to_lower(attr->Value()) };
      parse_attribute(attribute_name, attribute_value, &ps);
    }
    // ================================================================================
    // Now we have gc::ParamSet object filled in and ready to be passed along to the API.
    // ================================================================================
    // ============================================================================
    /// HACK: If the tag is `include` we call `parse_scene_file()` recursively.
    // ----------------------------------------------------------------------------
    if (tag_name == "include") {
      auto filename = ps.retrieve<std::string>("filename");
      if (!filename) {
      }
      if (not fs::exists(fs::path{ filename.value().c_str() })) {
      }
      // Recursive call to process subfile.
      Parser::parse(filename.value().c_str());
      continue;  // This tag doesn't have an API function associated with; get next tag.
    }
    // ============================================================================

    // Check whether this tag_name has a proper API function.
    if (api_functions.count(tag_name) == 0) {
      continue;
    }

    // Call the api function associated with the tag name.
    api_functions[tag_name](ps);
  }
}
