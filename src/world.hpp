
#ifndef WORLD_HPP
#define WORLD_HPP

#include "action.hpp"
#include "colored_crystal_matrix.hpp"
#include "colored_light_matrix.hpp"
#include "creature.hpp"
#include "crystalline_structure.hpp"
#include "dialog.hpp"
#include "rogue.hpp"
#include "status_bar.hpp"

const int kWorldWidth = 80;
const int kWorldHeight = 23;

class World
{
public:
    World();

    void step();
    void draw();

    void process(Action action);

private:
    std::unique_ptr<ColoredLightMatrix> mColoredLightMatrix;
    std::unique_ptr<ColoredCrystalMatrix> mColoredCrystalMatrix;
    std::unique_ptr<Rogue> mTheRogue;
    std::unique_ptr<Creature> mTheCreature;
    std::vector<std::unique_ptr<CrystallineStructure>> mCrystallineStructures;
    std::unique_ptr<Dialog> mDialog;
    StatusBar mStatusBar;
};

#endif
