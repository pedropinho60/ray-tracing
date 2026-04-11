#ifndef WINDOW_SIZE_HPP
#define WINDOW_SIZE_HPP

struct WindowSize {
    double left, right, bottom, top;

    WindowSize() {}
    WindowSize(double left, double right, double bottom, double top)
        : left{left}, right{right}, bottom{bottom}, top{top} {}
};

#endif // WINDOW_SIZE_HPP
