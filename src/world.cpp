#include <sstream>

#include <termbox.h>

#include "basic_crystal_populator.hpp"
#include "world.hpp"

World::World()
    : mColoredLightMatrix{new ColoredLightMatrix(kWorldWidth, kWorldHeight)},
      mColoredCrystalMatrix{new ColoredCrystalMatrix(
          kWorldWidth, kWorldHeight,
          new BasicCrystalPopulator(*mColoredLightMatrix))},
      mTheRogue{new Rogue(mCrystallineStructures, *mColoredLightMatrix,
                          *mColoredCrystalMatrix)},
      mTheCreature{new Creature(*mTheRogue, *mColoredLightMatrix)},
      mStatusBar{23, kWorldWidth, *mTheRogue}
{
    PowerSource ps(Color::kWhite, 100);
    ps.givePower(50);
    ps.chargeToFull();
    auto eff =
        std::make_shared<LightProvider>(Color::kWhite, *mColoredLightMatrix);
    auto cs = std::make_unique<CrystallineStructure>("Light Structure",
                                                     ps, eff);

    cs->moveTo(40, 12);
    mCrystallineStructures.push_back(std::move(cs));
    mTheRogue->moveTo(40, 13);
}

void World::step()
{
    mStatusBar.setMessage("");
    for (auto &cs : mCrystallineStructures) {
        cs->step();
    }
    mColoredCrystalMatrix->step();
    mTheCreature->step();
    mStatusBar.step();
}

void World::draw()
{
    for (int x = 0; x < kWorldWidth; ++x) {
        for (int y = 0; y < kWorldHeight; ++y) {
            auto bg = mColoredLightMatrix->brightness(x, y, Color::kWhite)
                          ? TB_WHITE
                          : TB_BLACK;
            auto fg = mColoredCrystalMatrix->color(x, y);
            auto ch =
                mColoredCrystalMatrix->crystals(x, y) && mTheRogue->canSee(x, y)
                    ? '*'
                    : ' ';
            tb_change_cell(x, y, ch, static_cast<int>(fg) | TB_BOLD,
                           static_cast<int>(bg));
        }
    }

    int rx = mTheRogue->x();
    int ry = mTheRogue->y();
    if (mTheRogue->inLight()) {
        tb_change_cell(rx, ry, '@', TB_BLACK, TB_WHITE);
    } else {
        tb_change_cell(rx, ry, '@', TB_WHITE, TB_BLACK);
    }

    for (auto &cs : mCrystallineStructures) {
        auto &cell = tb_cell_buffer()[cs->y() * tb_width() + cs->x()];
        // XXX: Uses a hack. Termbox colors the same as dimlit's.
        int color = static_cast<int>(cs->powerSource().poweredBy());
        cell.ch = '&';
        cell.fg = TB_BOLD | color;
    }

    mStatusBar.draw();

    if (mDialog) {
        mDialog->draw();
    }
}

void World::process(Action action)
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
    case Action::kBack:
        mStatusBar.setMessage("");
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
    } else {
        int x = mTheRogue->x() + dX;
        int y = mTheRogue->y() + dY;
        auto b = std::begin(mCrystallineStructures);
        auto e = std::end(mCrystallineStructures);
        auto csi = std::find_if(
            b, e, [x, y](auto &i) { return i->x() == x && i->y() == y; });
        if (csi != e) {
            auto &cs = *csi;
            auto &ps = cs->powerSource();
            int max = ps.maxCrystalsFromBag(mTheRogue->bag());
            std::vector<BasicDialog<int>::Option> options;
            for (int i = 2; i < max; i *= 2) {
                std::stringstream ss;
                ss << "Give " << i;
                options.push_back(BasicDialog<int>::Option(ss.str(), i));
            }
            std::stringstream maxss;
            maxss << "Give " << max;
            options.push_back(BasicDialog<int>::Option(maxss.str(), max));
            std::stringstream ss;
            ss << cs->name() << " (" << ps.percentPowered() << "% of " << ps.maxCrystals()
               << ")";
            mDialog.reset(new BasicDialog<int>(
                x, y, kWorldWidth, kWorldHeight, ss.str(), options,
                [&cs, this](auto const &option, auto item) mutable {
                    this->mTheRogue->giveStructurePower(*cs, item);
                    // FIXME: Right now adds one to compensate for the step.
                    cs->refresh();
                }));
        }
    }
}
