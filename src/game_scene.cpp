
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

    if (mDialog) {
        mDialog->draw();
    }
}

void GameScene::process(Action action)
{
    if (mDialog) {
        if (!mDialog->shouldClose()) {
            mDialog->process(action);
            return;
        } else {
            mDialog.reset();
        }
    }

    int dX = 0;
    int dY = 0;
    switch (action) {
    case Action::kMoveNorth:
        dY = -1;
        break;
    case Action::kMoveSouth:
        dY = 1;
        break;
    case Action::kMoveEast:
        dX = 1;
        break;
    case Action::kMoveWest:
        dX = -1;
        break;
    default:
        break;
    }

    if (dX == 0 && dY == 0) {
        return;
    }

    bool moved = mTheRogue->moveBy(dX, dY);
    if (moved) {
        step();
    }
}
