
#ifndef CREATURE_PRESENCE_HPP
#define CREATURE_PRESENCE_HPP

#include "colored_light_matrix.hpp"
#include "rogue.hpp"

class CreaturePresence
{
public:
    enum class Death { kStarved, kLit };
    enum class Injury { kLit };
    enum class Danger { kSafe, kClose, kReallyClose, kFatal };
    CreaturePresence(const Rogue &rogue, const ColoredLightMatrix &lm)
        : mRogue{rogue}, mColoredLightMatrix{lm}
    {
        (void)mRogue;
        (void)mColoredLightMatrix;
    }

    bool alive() const { return mAlive; }
    bool starving() const
    {
        return alive() && mSustenance <= mStarvingThreshold;
    }
    Death causeOfDeath() const { return mCauseOfDeath; }

    void setGracePeriod(int turns) { mGracePeriod = turns; }

    Danger dangerLevel(int x, int y) const
    {
        if (mCenterX == x && mCenterY == y) {
            return Danger::kFatal;
        }
        auto sq = [](auto x) { return x * x; };
        auto dist = sq(mCenterX - x) + sq(mCenterY - y);
        if (dist <= sq(mInnerRange)) {
            return Danger::kReallyClose;
        } else if (dist <= sq(mOuterRange)) {
            return Danger::kClose;
        } else {
            return Danger::kSafe;
        }
    }

    void kill(Death death)
    {
        if (mAlive) {
            mAlive = false;
            mCauseOfDeath = death;
        }
    }

    void age(int by = 1)
    {
        mSustenance = std::max(mSustenance - by, 0);
        if (mSustenance <= 0) {
            kill(Death::kStarved);
        }
    }

    Danger touch(int x, int y)
    {
        Danger danger = dangerLevel(x, y);
        if (--mGracePeriod < 0 && danger == Danger::kFatal) {
            return Danger::kReallyClose;
        }
        return danger;
    }

    void moveTowards(int x, int y)
    {
        (void)x;
        (void)y;
    }

private:
    int mCenterX = 0;
    int mCenterY = 0;
    // The creature can move anywhere in this circle.
    int mInnerRange = 2;
    int mOuterRange = 6;
    int mGracePeriod = 0;
    bool mAlive = true;
    int mSustenance = 10000;
    int mStarvingThreshold = 1000;
    Death mCauseOfDeath;
    const Rogue &mRogue;
    const ColoredLightMatrix &mColoredLightMatrix;
};

#endif
