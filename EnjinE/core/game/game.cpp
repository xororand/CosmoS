#include "game.h"

#include "sys/events.h"
#include "sys/render.h"
#include "sys/creator.h"
#include "sys/physics.h"
#include "sys/input_controller.h"

game::game() {
}

game::~game()
{
}

int game::run()
{
    // TODO: �������� �������
    // TODO: ��������� �������� � sys/render.h
    RenderScene rs = creator::makeRenderScene(reg);
    TextureManager tm = creator::makeTextureManager(reg);

    creator::makeWorld(reg);
    creator::makePlayer(reg);
    
    // ������� ����
    while (rs.rw->isOpen()) {
        events::tick(reg, rs.rw);
        input_controller::tick(reg);

        physics::step(reg);

        render::frame(reg, rs);
    }

    return 0;
}
