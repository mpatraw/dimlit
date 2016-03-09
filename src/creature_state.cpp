
#include "creature.hpp"
#include "creature_state.hpp"

CreatureState::CreatureState(Creature &creature) : mCreature{creature} {}

CreatureWandering::CreatureWandering(Creature &creature, const ColoredLightMatrix &lm) :
    CreatureState(creature), mColoredLightMatrix{lm} {}

void CreatureWandering::step()
{
    //mCreature.age();
    (void)mColoredLightMatrix;
}

CreatureTeleporting::CreatureTeleporting(Creature &creature, const ColoredLightMatrix &lm) :
        CreatureState(creature), mColoredLightMatrix{lm} {}

void CreatureTeleporting::step()
{
    //mCreature.age();
    mCreature.setState(new CreatureWandering(mCreature, mColoredLightMatrix));
}
