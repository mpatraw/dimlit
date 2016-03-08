
#ifndef CRYSTALINE_STRUCTURE_HPP
#define CRYSTALINE_STRUCTURE_HPP

#include <memory>
#include <string>

#include "colored_crystal_bag.hpp"
#include "colored_light_matrix.hpp"
#include "crystalline_structure_effect.hpp"

class CrystallineStructure
{
public:
    CrystallineStructure(std::string name, Color powers, int maxCrystals,
                         std::shared_ptr<CrystallineStructureEffect> effect);
    ~CrystallineStructure();

    int x() const;
    int y() const;
    int crystals() const;
    int maxCrystals() const;
    Color poweredBy() const;
    std::string name() const;

    int givePower(int amount);
    int givePowerFromBag(ColoredCrystalBag &bag, int amount);
    void moveTo(int x, int y);

    void step();

    void draw(float dt);

private:
    int mX = 0;
    int mY = 0;
    int mCrystals = 0;
    int mMaxCrystals;
    Color mPoweredBy;
    std::string mName;
    std::shared_ptr<CrystallineStructureEffect> mEffect;
};

#endif
