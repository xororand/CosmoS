#include "render.h"
#include <box2d/box2d.h>

#include "comp/Player.h"
#include "comp/SpriteComp.h"
#include <comp/TextureManager.h>
#include <comp/Controllable.h>

void render::frame(entt::registry&reg, RenderScene& rs) {
    ImGui::SFML::Update(*rs.rw, rs.deltaClock.restart());

    if (ImGui::Begin("Debug")) {
        const auto p = reg.view<Player, b2BodyId>();
        if (p.begin() != p.end()) {
            b2BodyId bid = reg.get<b2BodyId>(p.front());
            b2Vec2  pos = b2Body_GetPosition(bid);
            b2Vec2  vel = b2Body_GetLinearVelocity(bid);
            b2Rot   rot = b2Body_GetRotation(bid);
            ImGui::Text("Player DEBUG:");
            ImGui::Text(std::format("Posisiton:\tx:{:.4f}, y:{:.4f}", pos.x, pos.y).c_str());
            ImGui::Text(std::format("Velocity:\tx:{:.4f}, y:{:.4f}", vel.x, vel.y).c_str());
            ImGui::Text(std::format("Rotation:\tcos:{:.4f}, sin:{:.4f}", rot.c, rot.s).c_str());
        }

        const auto c = reg.view<Controllable>();
        if (p.begin() != p.end()) {
            Controllable* ctrla = &reg.get<Controllable>(p.front());
            ImGui::Text(std::format("WASD:\t{},{},{},{}", ctrla->w, ctrla->a, ctrla->s, ctrla->d).c_str());
        }

        ImGui::Checkbox("Debug physics", &rs.is_debug_physics);

        ImGui::End();
    }
    
    rs.rw->clear(Color(150, 150, 150));

    set_controllable_view(reg, rs);
    render_physics(reg, rs);

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

        b2Vec2 pos = b2Body_GetPosition(bid);
        b2Rot rot = b2Body_GetRotation(bid);
        b2Vec2 vel = b2Body_GetLinearVelocity(bid);

        float dbg_size = 0.0f;

        b2ShapeId shapeIds[1];
        b2Body_GetShapes(bid, shapeIds, 1);

        b2ShapeType shapetype = b2Shape_GetType(shapeIds[0]);
        
        switch (shapetype) {
        case b2ShapeType::b2_circleShape:
            b2Circle cirle =  b2Shape_GetCircle(shapeIds[0]);
            dbg_size = cirle.radius;
            break;
        }

        float angle = acos(rot.c) / (b2_pi / 180);

        Texture* texture = texmngr.getTexture(sprite_c.id);

        if (texture == nullptr) continue;
        texture->setSrgb(true);

        Sprite sprite;
        sprite.setTexture(*texture);
        sprite.setPosition(Vector2f(pos.x, pos.y));
        sprite.setRotation(angle);
        sprite.setOrigin(Vector2f(texture->getSize().x / 2.0f, texture->getSize().y / 2.0f));
        rs.rw->draw(sprite);

        if (rs.is_debug_physics) {
            // Рисуем бокс
            sf::Vertex line[] =
            {
                sf::Vertex(sf::Vector2f(pos.x + dbg_size, pos.y + dbg_size)), sf::Vertex(sf::Vector2f(pos.x - dbg_size, pos.y + dbg_size)),
                sf::Vertex(sf::Vector2f(pos.x - dbg_size, pos.y + dbg_size)), sf::Vertex(sf::Vector2f(pos.x - dbg_size, pos.y - dbg_size)),
                sf::Vertex(sf::Vector2f(pos.x - dbg_size, pos.y - dbg_size)), sf::Vertex(sf::Vector2f(pos.x + dbg_size, pos.y - dbg_size)),
                sf::Vertex(sf::Vector2f(pos.x + dbg_size, pos.y - dbg_size)), sf::Vertex(sf::Vector2f(pos.x + dbg_size, pos.y + dbg_size)),
            };
            rs.rw->draw(line, 8, sf::Lines);

            Text position = Text(std::format("p:{:.4f},{:.4f}", pos.x, pos.y), rs.mfont, 24);
            Text rotation = Text(std::format("c:{:.4f},s:{:.4f}", rot.c, rot.s), rs.mfont, 24);
            Text velocity = Text(std::format("vel:{:.4f},{:.4f}", vel.x, vel.y), rs.mfont, 24);
            Text n_textur = Text(std::format(L"tex:{}", texmngr.getNamebyID(sprite_c.id)), rs.mfont, 24);

            const float text_scale = 0.15f;

            position.setScale(Vector2f(text_scale, text_scale));
            rotation.setScale(Vector2f(text_scale, text_scale));
            velocity.setScale(Vector2f(text_scale, text_scale));
            n_textur.setScale(Vector2f(text_scale, text_scale));

            position.setPosition(Vector2f(pos.x + dbg_size, pos.y - dbg_size));
            rotation.setPosition(Vector2f(pos.x + dbg_size, pos.y - dbg_size + 5));
            velocity.setPosition(Vector2f(pos.x + dbg_size, pos.y - dbg_size + 10));
            n_textur.setPosition(Vector2f(pos.x + dbg_size, pos.y - dbg_size + 15));

            rs.rw->draw(position);
            rs.rw->draw(rotation);
            rs.rw->draw(velocity);
            rs.rw->draw(n_textur);
        }
    }
}

void render::set_controllable_view(entt::registry&reg, RenderScene rs)
{
    const auto view = reg.view<Controllable, b2BodyId>();
    if (view.begin() == view.end()) return;

    Controllable ctrla = view.get<Controllable>(view.front());
    b2BodyId bid = view.get<b2BodyId>(view.front());

    b2Vec2 pos = b2Body_GetPosition(bid);

    // Установка камеры на контролируемое
    const auto t1 = reg.view<RenderScene>();
    if (t1.begin() != t1.end()) {
        const auto e = t1.front();
        RenderScene rs = reg.get<RenderScene>(e);
        Vector2u size = rs.rw->getSize();
        sf::View view(sf::Vector2f(pos.x, pos.y), sf::Vector2f(size.x / 64.0f * 25, size.y / 64.0f * 25));
        rs.rw->setView(view);
    }
}
