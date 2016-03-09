
#ifndef ROGUE_HPP
#define ROGUE_HPP

#include <memory>
#include <vector>

#include "colored_crystal_matrix.hpp"
#include "colored_crystal_bag.hpp"
#include "crystalline_structure.hpp"

class Rogue
{
public:
    Rogue(const std::vector<std::unique_ptr<CrystallineStructure>> &cs,
          const ColoredLightMatrix &lm, ColoredCrystalMatrix &cm)
        : mCrystallineStructures{cs}, mColoredLightMatrix{lm},
          mColoredCrystalMatrix{cm}, mVisibility{lm.width(), lm.height()}
    {
    }

    int x() const { return mX; }
    int y() const { return mY; }
    const ColoredCrystalBag &bag() const { return mColoredCrystalBag; }
    bool inLight() const
    {
        return mColoredLightMatrix.brightness(mX, mY, Color::kWhite) > 0;
    }

    bool moveTo(int x, int y)
    {
        if (!mColoredLightMatrix.inBounds(x, y)) {
            return false;
        }

        for (auto const &cs : mCrystallineStructures) {
            if (x == cs->x() && y == cs->y()) {
                return false;
            }
        }
        mVisibility.emitLight(mX, mY, 0);
        mX = x;
        mY = y;
        mVisibility.emitRange(mX, mY, mSightRange);
        mColoredCrystalMatrix.collectCrystals(mX, mY, mColoredCrystalBag);
        return true;
    }
    bool moveBy(int dx, int dy) { return moveTo(mX + dx, mY + dy); }

    bool canSee(int x, int y)
    {
        if (mColoredLightMatrix.brightness(x, y, Color::kWhite) > 0) {
            return true;
        }
        return mVisibility.brightness(x, y) > 0;
    }

    void giveStructurePower(CrystallineStructure &cs, int amount)
    {
        cs.powerSource().giveCrystalsFromBag(mColoredCrystalBag, amount);
    }

private:
    int mX = 0;
    int mY = 0;
    int mSightRange = 2;
    const std::vector<std::unique_ptr<CrystallineStructure>>
        &mCrystallineStructures;
    const ColoredLightMatrix &mColoredLightMatrix;
    ColoredCrystalMatrix &mColoredCrystalMatrix;
    LightMatrix mVisibility;
    ColoredCrystalBag mColoredCrystalBag;
};

#endif
