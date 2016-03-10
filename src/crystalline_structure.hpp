
#ifndef CRYSTALINE_STRUCTURE_HPP
#define CRYSTALINE_STRUCTURE_HPP

#include <memory>
#include <string>

#include "colored_crystal_bag.hpp"
#include "crystalline_structure_effect.hpp"
#include "power_source.hpp"

class CrystallineStructure
{
public:
    CrystallineStructure(std::string name, const PowerSource &powerSource,
                         CrystallineStructureEffect *effect);
    ~CrystallineStructure();

    int x() const;
    int y() const;
    std::string name() const;
    const PowerSource &powerSource() const;
    PowerSource &powerSource();

    void refresh();
    void moveTo(int x, int y);
    void step();

private:
    int mX = 0;
    int mY = 0;
    std::string mName;
    std::unique_ptr<CrystallineStructureEffect> mEffect;
    PowerSource mPowerSource;
};

#endif
