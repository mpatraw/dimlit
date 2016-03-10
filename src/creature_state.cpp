
#include "creature.hpp"
#include "creature_state.hpp"

CreatureState::CreatureState(Creature &creature) : mCreature{creature}
{
}

CreatureWandering::CreatureWandering(Creature &creature, CreaturePresence &cp)
    : CreatureState(creature), mPresence{cp}
{
}

void CreatureWandering::step()
{
    // mCreature.age();
    (void)mPresence;
}

CreatureTeleporting::CreatureTeleporting(Creature &creature,
                                         CreaturePresence &cp)
    : CreatureState(creature), mPresence{cp}
{
}

void CreatureTeleporting::step()
{
    // mCreature.age();
    mCreature.setState(new CreatureWandering(mCreature, mPresence));
}
