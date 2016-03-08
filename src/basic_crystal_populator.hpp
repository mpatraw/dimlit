
#ifndef BASIC_CRYSTAL_POPULATOR_HPP
#define BASIC_CRYSTAL_POPULATOR_HPP

#include "colored_crystal_matrix.hpp"
#include "colored_light_matrix.hpp"

class BasicCrystalPopulator : public ColoredCrystalMatrix::Populator
{
public:
    BasicCrystalPopulator(const ColoredLightMatrix &lm)
        : mColoredLightMatrix{lm}
    {
    }
    ~BasicCrystalPopulator() = default;

    void populate(ColoredCrystalMatrix &crystalMatrix) override
    {
        (void)mColoredLightMatrix;
    }

private:
    const ColoredLightMatrix &mColoredLightMatrix;
};

#endif
