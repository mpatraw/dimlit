
#ifndef BOUNDED_STRUCTURE_MATRIX_HPP
#define BOUNDED_STRUCTURE_MATRIX_HPP

#include <memory>
#include <vector>

#include "crystalline_structure.hpp"
#include "obstruction_matrix.hpp"

class BoundedStructureMatrix : public ObstructionMatrix
{
public:
    BoundedStructureMatrix(
        int width, int height,
        const std::vector<std::shared_ptr<CrystallineStructure>>
            &crystallineStructures)
        : mWidth{width}, mHeight{height},
          mCrystallineStructures{crystallineStructures}
    {
    }

    bool hasObstruction(int x, int y) const override
    {
        if (x < 0 || x >= mWidth || y < 0 || y >= mHeight) {
            return true;
        }

        for (auto cs : mCrystallineStructures) {
            if (x == cs->x() && y == cs->y()) {
                return true;
            }
        }
        return false;
    }

public:
    int mWidth;
    int mHeight;
    const std::vector<std::shared_ptr<CrystallineStructure>>
        &mCrystallineStructures;
};

#endif
