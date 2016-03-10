
#include "crystalline_structure.hpp"

CrystallineStructure::CrystallineStructure(std::string name,
                                           const PowerSource &powerSource,
                                           CrystallineStructureEffect *effect)
    : mName{name}, mEffect{effect}, mPowerSource{powerSource}
{
}
CrystallineStructure::~CrystallineStructure()
{
}

int CrystallineStructure::x() const
{
    return mX;
}
int CrystallineStructure::y() const
{
    return mY;
}

std::string CrystallineStructure::name() const
{
    return mName;
}

const PowerSource &CrystallineStructure::powerSource() const
{
    return mPowerSource;
}

PowerSource &CrystallineStructure::powerSource()
{
    return mPowerSource;
}

void CrystallineStructure::refresh()
{
    mEffect->redo(mX, mY, mPowerSource.power());
}

void CrystallineStructure::moveTo(int x, int y)
{
    mX = x;
    mY = y;
    refresh();
}

void CrystallineStructure::step()
{
    mPowerSource.step();
    refresh();
}
