
#ifndef CREATURE_HPP
#define CREATURE_HPP

#include <algorithm>
#include <functional>
#include <vector>

#include "colored_light_matrix.hpp"
#include "creature_presence.hpp"
#include "creature_state.hpp"
#include "rogue.hpp"

class Creature
{
public:
    class Listener
    {
    public:
        virtual ~Listener() = default;

        virtual void creatureDied(std::string reason) = 0;
        virtual void creatureInjured(std::string reason) = 0;
        virtual void creatureClose(bool reallyClose = false) = 0;
    };

    Creature(const Rogue &rogue, const ColoredLightMatrix &lm)
        : mPresence{rogue, lm}
    {
        mState.reset(new CreatureWandering(*this, mPresence));
    }
    const CreaturePresence &presence() const { return mPresence; }

    void setState(CreatureState *state) { mState.reset(state); }

    void addListener(Listener &listener) { mListeners.push_back(listener); }

    void removeListener(Listener &listener)
    {
        auto b = std::begin(mListeners);
        auto e = std::end(mListeners);
        auto it = std::find_if(
            b, e, [&listener](auto const &l) { return &listener == &l.get(); });
        if (it != e) {
            mListeners.erase(it);
        }
    }

    void step()
    {
        if (!mPresence.alive()) {
            return;
        }
        mState->step();
        if (!mPresence.alive()) {
            notifyCreatureDied(mPresence.causeOfDeath());
            return;
        }
    }

private:
    void notifyCreatureDied(CreaturePresence::Death how)
    {
        std::string howStrings[] = {"The Creature starved to death.",
                                    "The Creature disintigrated in the light."};
        for (auto l : mListeners) {
            l.get().creatureDied(howStrings[static_cast<int>(how)]);
        }
    }
    void notifyCreatureInjured(CreaturePresence::Injury how)
    {
        std::string howStrings[] = {"The Creature squeeled in the light."};
        for (auto l : mListeners) {
            l.get().creatureInjured(howStrings[static_cast<int>(how)]);
        }
    }
    void notifyCreatureClose(bool reallyClose = false)
    {
        for (auto l : mListeners) {
            l.get().creatureClose(reallyClose);
        }
    }

    std::vector<std::reference_wrapper<Listener>> mListeners;
    std::unique_ptr<CreatureState> mState;
    CreaturePresence mPresence;
};

#endif
