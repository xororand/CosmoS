#include "render.h"
#include <box2d/box2d.h>

#include "comp/Player.h"
#include "comp/SpriteComp.h"
#include <comp/TextureManager.h>
#include <comp/Controllable.h>

void render::frame(entt::registry&reg, RenderScene rs) {
    ImGui::SFML::Update(*rs.rw, rs.deltaClock.restart());

    if (ImGui::Begin("Player debug")) {
        const auto p = reg.view<Player, b2BodyId>();
        if (p.begin() != p.end()) {
            b2BodyId bid = reg.get<b2BodyId>(p.front());
            b2Vec2 pos = b2Body_GetPosition(bid);
            ImGui::Text(std::format("Pos: x:{}, y:{}", pos.x, pos.y).c_str());
        }

        const auto c = reg.view<Controllable>();
        if (p.begin() != p.end()) {
            Controllable ctrla = reg.get<Controllable>(p.front());
            ImGui::Text(std::format("WASD: {},{},{},{}", ctrla.w, ctrla.a, ctrla.s, ctrla.d).c_str());
        }
        ImGui::End();
    }

    render_physics(reg, rs);

    rs.rw->clear();

    ImGui::SFML::Render(*rs.rw);
    rs.rw->display();
}

void render::render_physics(entt::registry&reg, RenderScene rs) {

    const auto tm = reg.view<TextureManager>();
    if (tm.begin() == tm.end()) return;
    TextureManager texmngr = reg.get<TextureManager>(tm.front());

    const auto view = reg.view<SpriteComp, b2BodyId>();
    for (auto e : view) {
        SpriteComp sprite_c = reg.get<SpriteComp>(e);
        b2BodyId bid = reg.get<b2BodyId>(e);

        Texture* texture = texmngr.getTexture(sprite_c.id);
        if (texture == nullptr) continue;
        Sprite sprite;
        sprite.setTexture(*texture);

        rs.rw->draw(sprite);
    }
}
