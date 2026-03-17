#ifndef APP_HPP
#define APP_HPP

#include "background.hpp"
#include "film.hpp"

class App {
    // Background bg;
    const std::uint16_t width{400};
    const std::uint16_t height{200};
    const std::uint8_t max_channel_value{255};

    Background bg{{RGBColor(0, 255, 51), RGBColor(255, 255, 51),
                   RGBColor(255, 0, 51), RGBColor(0, 0, 51)}};
    Film film{width, height};

    public:
    void render() {
        std::cout << "P3\n";
        std::cout << width << ' ' << height << '\n';
        std::cout << (int)max_channel_value << '\n';

        for (std::uint16_t y{0}; y < height; ++y) {
          float v = static_cast<float>(y) / (height - 1);
          for (std::uint16_t x{0}; x < width; ++x) {
            float u = static_cast<float>(x) / (width - 1);
            RGBColor color = bg.sampleUV(u, v);
            film.add_sample({x, y}, color);

          }
        }

        film.write_out();
    }
};

#endif // APP_HPP
