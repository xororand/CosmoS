#include "game.h"

#include <entt/entity/registry.hpp>

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
    creator::makeRenderScene();
    creator::makeTextureManager();

    creator::makeMainWorld();
    
    // Главный цикл
    while ( rs.rw->isOpen() ) {
        gui_events::step(rs.rw);
        input_controller::step();
        
        ChunkSystem::update_chunk_members();

        physics::step();
        logics::step();

        render::frame();
    }
    
    return 0;
}
