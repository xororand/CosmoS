#include "game.h"

#include "sys/events.h"
#include "sys/render.h"
#include "sys/creator.h"
#include "sys/physics.h"
#include "sys/logics.h"
#include "sys/input_controller.h"

game::game() {
    srand(time(0));
}

game::~game()
{
}

int game::run()
{
    RenderScene     rs   = creator::makeRenderScene(reg);
    TextureManager  tm   = creator::makeTextureManager(reg);

    creator::makeWorld(reg);

    creator::makePlayer(reg);

    creator::makeComposition_MiningAntientDrones(reg, b2Vec2(64.0f, 0.0f));
    
    // Главный цикл
    rs.rw->setVerticalSyncEnabled(true);
    while (rs.rw->isOpen()) {
        gui_events::step(reg, rs.rw);
        input_controller::step(reg);

        physics::step(reg);
        logics::step(reg);

        render::frame(reg, rs);
    }

    return 0;
}
