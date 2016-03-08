
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

    void populate(std::vector<Color> &colorMatrix,
                  std::vector<int> &crystalMatrix,
                  int width, int height) override
    {
        if (rand() % 100 < 50) {
            return;
        }

        int tries = 100;
        while (--tries) {
            int x = rand() % width;
            int y = rand() % height;
            if (mColoredLightMatrix.brightness(x, y, Color::kWhite) > 0) {
                continue;
            }
            colorMatrix[y * width + x] = Color::kWhite;
            crystalMatrix[y * width + x] = rand() % 50 + 10;
        }
    }

private:
    const ColoredLightMatrix &mColoredLightMatrix;
};

#endif
