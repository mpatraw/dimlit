
#ifndef COLORED_LIGHT_MATRIX_HPP
#define COLORED_LIGHT_MATRIX_HPP

#include <array>

#include "color.hpp"
#include "light_matrix.hpp"

class ColoredLightMatrix
{
public:
    ColoredLightMatrix(int width, int height);

    int width() const;
    int height() const;
    bool inBounds(int x, int y) const;
    int brightness(int x, int y, Color color) const;
    int lightEmitted(int x, int y, Color color) const;

    void emitLight(int x, int y, int amount, Color color);

private:
    std::array<LightMatrix, static_cast<size_t>(Color::kCount)> mLightMatrices;
};

#endif
