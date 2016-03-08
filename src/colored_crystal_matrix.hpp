
#ifndef COLORED_CRYSTAL_MATRIX_HPP
#define COLORED_CRYSTAL_MATRIX_HPP

#include <memory>
#include <vector>

#include "colored_crystal_bag.hpp"
#include "color.hpp"

class ColoredCrystalMatrix
{
public:
    class Populator
    {
    public:
        virtual ~Populator() = default;
        virtual void populate(ColoredCrystalMatrix &crystalMatrix) = 0;
    };
    friend class Populator;
    ColoredCrystalMatrix(int width, int height, Populator *populator)
        : mWidth{width}, mHeight{height}, mPopulator{populator}
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

    void step() { mPopulator->populate(*this); }

private:
    int mWidth;
    int mHeight;
    std::vector<Color> mColorMatrix;
    std::vector<int> mCrystalMatrix;
    std::unique_ptr<Populator> mPopulator;
};

#endif
