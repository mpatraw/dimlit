
#ifndef CRYSTALLINE_STRUCTURE_EFFECT_HPP
#define CRYSTALLINE_STRUCTURE_EFFECT_HPP

class CrystallineStructureEffect
{
public:
    virtual ~CrystallineStructureEffect() {}
    virtual void undo() = 0;
    virtual void apply(int x, int y, int power) = 0;
    virtual void redo(int x, int y, int power)
    {
        undo();
        apply(x, y, power);
    }
};

class LightProvider : public CrystallineStructureEffect
{
public:
    LightProvider(Color provides, std::shared_ptr<ColoredLightMatrix> lm)
        : mProvides{provides}, mColoredLightMatrix{lm}
    {
    }
    ~LightProvider() {}

    void undo() { mColoredLightMatrix->emitLight(mX, mY, 0, mProvides); }

    void apply(int x, int y, int power)
    {
        mX = x;
        mY = y;
        mPower = power;
        mColoredLightMatrix->emitLight(mX, mY, mPower, mProvides);
    }

private:
    int mX = 0;
    int mY = 0;
    int mPower = 0;
    Color mProvides;
    std::shared_ptr<ColoredLightMatrix> mColoredLightMatrix;
};

#endif
