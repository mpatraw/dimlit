
#ifndef CREATURE_STATE_HPP
#define CREATURE_STATE_HPP

#include "colored_light_matrix.hpp"

class Creature;

class CreatureState
{
public:
    CreatureState(Creature &creature);
    virtual ~CreatureState() = default;

    virtual void step() = 0;
protected:
    Creature &mCreature;
};

class CreatureWandering : public CreatureState
{
public:
    CreatureWandering(Creature &creature, const ColoredLightMatrix &lm);

    void step() override;

private:
    const ColoredLightMatrix &mColoredLightMatrix;
};

class CreatureTeleporting : public CreatureState
{
public:
    CreatureTeleporting(Creature &creature, const ColoredLightMatrix &lm);

    void step() override;

private:
    const ColoredLightMatrix &mColoredLightMatrix;
};

#endif
