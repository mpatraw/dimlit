
#ifndef POWER_SOURCE_HPP
#define POWER_SOURCE_HPP

#include "color.hpp"
#include "colored_crystal_bag.hpp"

class PowerSource
{
public:
    PowerSource(Color power, double maxPower, double charge=1,
        double consumptionRate=1, double powerPerCrystal=1) :
        mMaxPower{maxPower}, mChargeRate{charge}, mConsumptionRate{consumptionRate},
        mPowerPerCrystal{powerPerCrystal}, mPoweredBy{power}
    {

    }

    Color poweredBy() const { return mPoweredBy; }
    int power() const { return mCurrentPower; }
    int maxPower() const { return mMaxPower; }
    int percentPowered() const { return (power() * 100) / maxPower(); }
    int maxCrystals() const { return mMaxPower * mPowerPerCrystal; }

    int maxCrystalsFromBag(const ColoredCrystalBag &bag) const
    {
        Color color = poweredBy();
        // Can't add more than what the structure can handler or what's in the
        // bag. Our maximum is a whatever is our lowest limit.
        int maxNeeded = std::min(bag.crystals(color),
            static_cast<int>((mMaxPower - mPower) / mPowerPerCrystal));
        return maxNeeded;
    }

    int giveCrystals(int amount)
    {
        int crystalAmount = std::min(amount,
            static_cast<int>((mMaxPower - mPower) / mPowerPerCrystal));
        mPower += crystalAmount * mPowerPerCrystal;
        return crystalAmount;
    }

    int giveCrystalsFromBag(ColoredCrystalBag &bag, int amount)
    {
        assert(amount >= 0);
        int maxNeeded = std::min(maxCrystalsFromBag(bag), amount);
        Color color = poweredBy();
        bag.setCrystals(color, bag.crystals(color) - maxNeeded);
        return giveCrystals(maxNeeded);
    }

    void givePower(int amount)
    {
        mPower = std::min(mPower + amount, mMaxPower);
    }

    void chargeToFull()
    {
        mCurrentPower = mPower;
    }

    void step()
    {
        if (mCurrentPower == mPower) {
            mPower = std::max(mPower - mConsumptionRate, 0.0);
        }
        mCurrentPower = std::min(mCurrentPower + mChargeRate, mPower);
    }

private:
    double mCurrentPower = 0;
    double mPower = 0;
    double mMaxPower;
    double mChargeRate;
    double mConsumptionRate;
    double mPowerPerCrystal;
    Color mPoweredBy;
};

#endif
