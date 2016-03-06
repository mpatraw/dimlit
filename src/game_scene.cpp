
#include <termbox.h>

#include "bounded_structure_matrix.hpp"
#include "game_scene.hpp"

GameScene::GameScene()
    : mColoredLightMatrix{new ColoredLightMatrix(kSceneWidth, kSceneHeight)},
      mTheRogue{new Rogue(std::make_shared<BoundedStructureMatrix>(
          kSceneWidth, kSceneHeight, mCrystallineStructures))},
      mTheCreature{new Creature}, mStatusBar{23, kSceneWidth, mTheRogue}
{
    auto eff =
        std::make_shared<LightProvider>(Color::kWhite, mColoredLightMatrix);
    auto cs = std::make_shared<CrystallineStructure>(Color::kWhite, 100, eff);
    mCrystallineStructures.push_back(cs);

    cs->givePower(50);
    cs->moveTo(40, 12);
    mTheRogue->moveTo(40, 13);
}

void GameScene::step()
{
    mStatusBar.setMessage("");
    for (auto cs : mCrystallineStructures) {
        cs->step();
    }
}

void GameScene::draw()
{
    for (int x = 0; x < mColoredLightMatrix->width(); ++x) {
        for (int y = 0; y < mColoredLightMatrix->height(); ++y) {
            if (mColoredLightMatrix->brightness(x, y, Color::kWhite)) {
                tb_change_cell(x, y, ' ', TB_DEFAULT, TB_WHITE);
            } else {
                tb_change_cell(x, y, ' ', TB_DEFAULT, TB_BLACK);
            }
        }
    }

    int rx = mTheRogue->x();
    int ry = mTheRogue->y();
    if (mColoredLightMatrix->brightness(rx, ry, Color::kWhite)) {
        tb_change_cell(rx, ry, '@', TB_BLACK, TB_WHITE);
    } else {
        tb_change_cell(rx, ry, '@', TB_WHITE, TB_BLACK);
    }

    for (auto cs : mCrystallineStructures) {
        auto &cell = tb_cell_buffer()[cs->y() * tb_width() + cs->x()];
        // XXX: Uses a hack. Termbox colors are +1 of dimlit's.
        int color = static_cast<int>(cs->poweredBy()) + 1;
        cell.ch = '&';
        cell.fg = TB_BOLD | color;
    }

    mStatusBar.draw();
}

void GameScene::process(Action action)
{
    bool moved = false;

    switch (action) {
    case Action::kMoveNorth:
        moved = mTheRogue->moveBy(0, -1);
        break;
    case Action::kMoveSouth:
        moved = mTheRogue->moveBy(0, 1);
        break;
    case Action::kMoveEast:
        moved = mTheRogue->moveBy(1, 0);
        break;
    case Action::kMoveWest:
        moved = mTheRogue->moveBy(-1, 0);
        break;
    default:
        break;
    }

    if (moved) {
        step();
    }
}
