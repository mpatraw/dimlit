
#ifndef CREATURE_PRESENCE_HPP
#define CREATURE_PRESENCE_HPP

#include "colored_light_matrix.hpp"

class CreaturePresence
{
public:
    enum class Death { kStarved, kLit };
    enum class Injury { kLit };
    enum class Danger { kSafe, kClose, kReallyClose, kFatal };
    enum class Reaction { kNothing, kSqueel, kDeath };
    CreaturePresence(const ColoredLightMatrix &lm) :
        mColoredLightMatrix{lm} {}

    bool alive() const { return mAlive; }
    bool starving() const { return alive() && mSustenance <= mStarvingThreshold; }
    int percentHealth() const { return (mHealth * 100) / mMaxHealth; }
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

    void age(int by=1)
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

    Reaction checkLight()
    {
        return Reaction::kNothing;
    }

    void moveTowards(int x, int y)
    {
        (void)mColoredLightMatrix;
    }
private:
    int mCenterX = 0;
    int mCenterY = 0;
    // The creature can move anywhere in this circle.
    int mInnerRange = 2;
    int mOuterRange = 6;
    int mHealth = 100;
    int mMaxHealth = 100;
    int mGracePeriod = 0;
    bool mAlive = true;
    int mSustenance = 10000;
    int mStarvingThreshold = 1000;
    Death mCauseOfDeath;
    const ColoredLightMatrix &mColoredLightMatrix;
};

#endif
