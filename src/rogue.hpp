
#ifndef ROGUE_HPP
#define ROGUE_HPP

#include <memory>

#include "colored_crystal_bag.hpp"
#include "obstruction_matrix.hpp"

class Rogue
{
public:
    Rogue(std::shared_ptr<const ObstructionMatrix> om);

    int health() const { return mHealth; }
    int x() const { return mX; }
    int y() const { return mY; }
    const ColoredCrystalBag &bag() const { return mColoredCrystalBag; }
    ColoredCrystalBag &bag() { return mColoredCrystalBag; }

    bool moveTo(int x, int y)
    {
        if (mObstructionMatrix->hasObstruction(x, y)) {
            return false;
        }
        mX = x;
        mY = y;
        return true;
    }
    bool moveBy(int dx, int dy) { return moveTo(mX + dx, mY + dy); }

private:
    const std::shared_ptr<const ObstructionMatrix> mObstructionMatrix;
    int mHealth;
    int mX;
    int mY;
    ColoredCrystalBag mColoredCrystalBag;
};

#endif
