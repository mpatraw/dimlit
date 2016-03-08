
#ifndef CREATURE_HPP
#define CREATURE_HPP

#include "colored_light_matrix.hpp"
#include "light_matrix.hpp"
#include "rogue.hpp"

class Creature
{
public:
    Creature(const Rogue &rogue, const ColoredLightMatrix &lm) : mRogue{rogue},
        mColoredLightMatrix{lm}, mArea{lm.width(), lm.height()} {}

    void step()
    {
        mArea.emitLight(mX, mY, 0);
        (void)mRogue;
        (void)mColoredLightMatrix;
        mArea.emitRange(mX, mY, mSize);
    }
private:
    int mX = 0;
    int mY = 0;
    int mSize = 5;
    const Rogue &mRogue;
    const ColoredLightMatrix &mColoredLightMatrix;
    LightMatrix mArea;
};

#endif
