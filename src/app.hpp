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
    Film film{width, height, max_channel_value};

    public:
    void render(); 
};

#endif // APP_HPP
