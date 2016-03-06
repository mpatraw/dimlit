
#include <termbox.h>

#include "game_scene.hpp"
#include "input.hpp"
#include "light_matrix.hpp"

// Guarantees proper shutdown.
struct TermboxGuard {
    TermboxGuard() { tb_init(); }
    ~TermboxGuard() { tb_shutdown(); }
};

int main()
{
    TermboxGuard tg;
    Input input;
    GameScene scene;

    tb_set_clear_attributes(TB_DEFAULT, TB_BLACK);

    bool running = true;
    while (running) {
        auto action = input.check();
        switch (action) {
        case Action::kQuit:
            running = false;
            break;
        default:
            scene.process(action);
            break;
        }

        tb_clear();
        scene.draw();
        tb_present();
    }
}
