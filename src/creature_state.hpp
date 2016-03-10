
#ifndef CREATURE_STATE_HPP
#define CREATURE_STATE_HPP

#include "colored_light_matrix.hpp"
#include "creature_presence.hpp"

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
    CreatureWandering(Creature &creature, CreaturePresence &cp);

    void step() override;

private:
    CreaturePresence &mPresence;
};

class CreatureTeleporting : public CreatureState
{
public:
    CreatureTeleporting(Creature &creature, CreaturePresence &cp);

    void step() override;

private:
    CreaturePresence &mPresence;
};

#endif
