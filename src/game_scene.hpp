
#ifndef GAME_SCENE_HPP
#define GAME_SCENE_HPP

#include "action.hpp"
#include "colored_light_matrix.hpp"
#include "creature.hpp"
#include "crystalline_structure.hpp"
#include "dialog.hpp"
#include "rogue.hpp"
#include "scene.hpp"
#include "status_bar.hpp"

const int kSceneWidth = 80;
const int kSceneHeight = 23;

class GameScene
{
public:
    GameScene();

    void step();
    void draw();

    void process(Action action);

private:
    std::shared_ptr<ColoredLightMatrix> mColoredLightMatrix;
    std::shared_ptr<Rogue> mTheRogue;
    std::shared_ptr<Creature> mTheCreature;
    std::vector<std::shared_ptr<CrystallineStructure>> mCrystallineStructures;
    std::unique_ptr<Dialog> mDialog;
    StatusBar mStatusBar;
};

#endif
