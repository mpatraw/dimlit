
#include "crystalline_structure.hpp"

CrystallineStructure::CrystallineStructure(
    std::string name, Color powers, int maxCrystals,
    std::shared_ptr<CrystallineStructureEffect> effect)
    : mMaxCrystals{maxCrystals}, mPoweredBy{powers}, mName{name},
      mEffect{effect}
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

int CrystallineStructure::crystals() const
{
    return mCrystals;
}

int CrystallineStructure::maxCrystals() const
{
    return mMaxCrystals;
}

Color CrystallineStructure::poweredBy() const
{
    return mPoweredBy;
}

std::string CrystallineStructure::name() const
{
    return mName;
}

int CrystallineStructure::givePower(int amount)
{
    int realAmount = std::min(amount, mMaxCrystals - mCrystals);
    mCrystals += realAmount;
    return realAmount;
}

int CrystallineStructure::givePowerFromBag(ColoredCrystalBag &bag, int amount)
{
    assert(amount >= 0);
    Color color = poweredBy();
    // Can't add more than what the structure can handler or what's in the
    // bag. Our maximum is a whatever is our lowest limit.
    int realAmount = std::min(bag.crystals(color), amount);
    realAmount = givePower(realAmount);
    bag.setCrystals(color, bag.crystals(color) - realAmount);
    return realAmount;
}

void CrystallineStructure::moveTo(int x, int y)
{
    mX = x;
    mY = y;
    mEffect->redo(mX, mY, mCrystals);
}

void CrystallineStructure::step()
{
    mEffect->undo();
    mCrystals--;
    if (mCrystals > 0) {
        mEffect->redo(mX, mY, mCrystals);
    }
}
