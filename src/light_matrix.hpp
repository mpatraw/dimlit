#ifndef LIGHT_MATRIX_HPP
#define LIGHT_MATRIX_HPP

#include <vector>

class LightMatrix
{
public:
    LightMatrix(int width, int height);

    int width() const;
    int height() const;
    bool inBounds(int x, int y) const;
    int brightness(int x, int y) const;
    int lightEmitted(int x, int y) const;

    void emitLight(int x, int y, int amount);
    void emitEnough(int x, int y, int range);

private:
    int mWidth;
    int mHeight;
    std::vector<int> mBrightness;
    std::vector<int> mLightEmitted;
};

#endif
