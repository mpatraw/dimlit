
#include "colored_light_matrix.hpp"

ColoredLightMatrix::ColoredLightMatrix(int width, int height)
    : mLightMatrices{{LightMatrix(width, height), LightMatrix(width, height),
                      LightMatrix(width, height), LightMatrix(width, height),
                      LightMatrix(width, height), LightMatrix(width, height),
                      LightMatrix(width, height), LightMatrix(width, height)}}
{
}

int ColoredLightMatrix::width() const
{
    return mLightMatrices[static_cast<size_t>(Color::kWhite)].width();
}

int ColoredLightMatrix::height() const
{
    return mLightMatrices[static_cast<size_t>(Color::kWhite)].height();
}

int ColoredLightMatrix::brightness(int x, int y, Color color) const
{
    return mLightMatrices[static_cast<size_t>(color)].brightness(x, y);
}

int ColoredLightMatrix::lightEmitted(int x, int y, Color color) const
{
    return mLightMatrices[static_cast<size_t>(color)].lightEmitted(x, y);
}

void ColoredLightMatrix::emitLight(int x, int y, int amount, Color color)
{
    mLightMatrices[static_cast<size_t>(color)].emitLight(x, y, amount);
}
