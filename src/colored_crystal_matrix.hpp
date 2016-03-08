
#ifndef COLORED_CRYSTAL_MATRIX_HPP
#define COLORED_CRYSTAL_MATRIX_HPP

#include <vector>

#include "colored_crystal_bag.hpp"
#include "color.hpp"

class ColoredCrystalMatrix
{
public:
    ColoredCrystalMatrix(int width, int height) :
        mWidth{width}, mHeight{height}
    {
        mColorMatrix.resize(mWidth * mHeight);
        mCrystalMatrix.resize(mWidth * mHeight);

        int x = 50;
        int y = 12;
        mColorMatrix[y * mWidth + x] = Color::kWhite;
        mCrystalMatrix[y * mWidth + x] = 10;
    }

    int crystals(int x, int y) const
    {
        assert(x >= 0 && x < mWidth && y >= 0 && y < mHeight);
        return mCrystalMatrix[y * mWidth + x];
    }

    Color color(int x, int y) const
    {
        assert(x >= 0 && x < mWidth && y >= 0 && y < mHeight);
        return mColorMatrix[y * mWidth + x];
    }

    void collectCrystals(int x, int y, ColoredCrystalBag &bag)
    {
        if (color(x, y) == Color::kNone) {
            return;
        }
        bag.setCrystals(color(x, y), crystals(x, y));
        mColorMatrix[y * mWidth + x] = Color::kNone;
        mCrystalMatrix[y * mWidth + x] = 0;
    }

private:
    int mWidth;
    int mHeight;
    std::vector<Color> mColorMatrix;
    std::vector<int> mCrystalMatrix;
};

#endif
