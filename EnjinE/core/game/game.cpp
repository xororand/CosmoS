#include "game.h"

#include "sys/events.h"
#include "sys/render.h"
#include "sys/creator.h"
#include "sys/physics.h"

game::game() {
}

game::~game()
{
}

int game::run()
{
    RenderScene rs = creator::makeRenderScene(reg);

    creator::makeWorld(reg);
    creator::makePlayer(reg);
    
    // Главный цикл
    while (rs.rw->isOpen()) {
        events::tick(reg, rs.rw);

        physics::step(reg);

        render::frame(reg, rs);
    }

    return 0;
}
