
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
    }

    int width() const { return mWidth; }
    int height() const { return mHeight; }

    int totalCrystals(Color color) const {
        return mCrystalCount[static_cast<int>(color)];
    }

    int totalCrystals() const {
        return totalCrystals(Color::kBlack) +
               totalCrystals(Color::kRed) +
               totalCrystals(Color::kGreen) +
               totalCrystals(Color::kYellow) +
               totalCrystals(Color::kBlue) +
               totalCrystals(Color::kMagenta) +
               totalCrystals(Color::kCyan) +
               totalCrystals(Color::kWhite);
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

    void setCrystals(int x, int y, Color clr, int to)
    {
        assert(x >= 0 && x < mWidth && y >= 0 && y < mHeight);
        if (crystals(x, y) > 0) {
            mCrystalCount[static_cast<int>(color(x, y))] -= crystals(x, y);
        }
        mCrystalCount[static_cast<int>(clr)] += to;
        mColorMatrix[y * mWidth + x] = clr;
        mCrystalMatrix[y * mWidth + x] += to;
    }

    void collectCrystals(int x, int y, ColoredCrystalBag &bag)
    {
        Color clr = color(x, y);
        int crys = crystals(x, y);
        if (clr == Color::kNone) {
            return;
        }
        bag.setCrystals(clr, bag.crystals(clr) + crys);
        mColorMatrix[y * mWidth + x] = Color::kNone;
        mCrystalMatrix[y * mWidth + x] = 0;
        mCrystalCount[static_cast<int>(clr)] -= crys;
    }

    void step() { mPopulator->populate(*this); }

private:
    int mWidth;
    int mHeight;
    std::array<int, static_cast<size_t>(Color::kCount)> mCrystalCount;
    std::vector<Color> mColorMatrix;
    std::vector<int> mCrystalMatrix;
    std::unique_ptr<Populator> mPopulator;
};

#endif
