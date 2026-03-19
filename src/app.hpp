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

        for (std::uint16_t row{0}; row < height; ++row) {
          float normalized_row = static_cast<float>(row) / (height - 1);
          for (std::uint16_t col{0}; col < width; ++col) {
            float normalized_col = static_cast<float>(col) / (width - 1);
            RGBColor color = bg.sampleUV(normalized_row, normalized_col);
            film.add_sample(row, col, color);
          }
        }

        film.write_ppm();
    }
};

#endif // APP_HPP
