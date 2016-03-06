
#ifndef COLORED_CRYSTAL_BAG_HPP
#define COLORED_CRYSTAL_BAG_HPP

#include <cassert>
#include <array>

#include "color.hpp"

class ColoredCrystalBag
{
public:
    ColoredCrystalBag() : mCrystals{{0, 0, 0, 0, 0, 0, 0, 0}} {}

    int crystals(Color color) const
    {
        return mCrystals[static_cast<size_t>(color)];
    }
    void setCrystals(Color color, int to)
    {
        assert(to >= 0);
        mCrystals[static_cast<size_t>(color)] = to;
    }

private:
    std::array<int, static_cast<size_t>(Color::kCount)> mCrystals;
};

#endif
