
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
        if (crystalMatrix.totalCrystals() > 200) {
            return;
        }
        if (rand() % 100 < 50) {
            return;
        }

        int width = crystalMatrix.width();
        int height = crystalMatrix.height();

        int tries = 100;
        while (--tries) {
            int x = rand() % width;
            int y = rand() % height;
            if (mColoredLightMatrix.brightness(x, y, Color::kWhite) > 0) {
                continue;
            }
            if (crystalMatrix.crystals(x, y) > 0) {
                continue;
            }
            crystalMatrix.setCrystals(x, y, Color::kWhite, rand() % 50 + 10);
            break;
        }
    }

private:
    const ColoredLightMatrix &mColoredLightMatrix;
};

#endif
