#ifndef LIGHT_MATRIX_HPP
#define LIGHT_MATRIX_HPP

#include <vector>

class LightMatrix
{
public:
    LightMatrix(int width, int height);

    int width() const;
    int height() const;
    int brightness(int x, int y) const;
    int lightEmitted(int x, int y) const;

    void emitLight(int x, int y, int amount);

private:
    int mWidth;
    int mHeight;
    std::vector<int> mBrightness;
    std::vector<int> mLightEmitted;
};

#endif
