
#include <termbox.h>

#include "input.hpp"
#include "world.hpp"

// Guarantees proper shutdown.
struct TermboxGuard {
    TermboxGuard() { tb_init(); }
    ~TermboxGuard() { tb_shutdown(); }
};

int main()
{
    TermboxGuard tg;
    Input input;
    World world;

    tb_set_clear_attributes(TB_DEFAULT, TB_BLACK);

    bool running = true;
    while (running) {
        auto action = input.check();
        switch (action) {
        case Action::kQuit:
            running = false;
            break;
        default:
            world.process(action);
            break;
        }

        tb_clear();
        world.draw();
        tb_present();
    }
}
