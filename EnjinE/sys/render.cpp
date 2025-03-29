#include "render.h"
#include <box2d/box2d.h>

#include "core/game/game.h"

#include "comp/Player.h"
#include "comp/SpriteComp.h"
#include <comp/TextureManager.h>
#include <comp/Controllable.h>

void render::frame() {
    ImGui::SFML::Update(*game::rs.rw, game::rs.deltaClock.restart());

    if (ImGui::Begin("Debug")) {
        const auto p = game::reg.view<Player, b2BodyId>();
        if (p.begin() != p.end()) {
            b2BodyId bid = game::reg.get<b2BodyId>(p.front());
            b2Vec2  pos = b2Body_GetPosition(bid);
            b2Vec2  vel = b2Body_GetLinearVelocity(bid);
            b2Rot   rot = b2Body_GetRotation(bid);
            ImGui::Text("Player DEBUG:");
            ImGui::Text(std::format("Posisiton:\tx:{:.4f}, y:{:.4f}", pos.x, pos.y).c_str());
            ImGui::Text(std::format("Velocity:\tx:{:.4f}, y:{:.4f}", vel.x, vel.y).c_str());
            ImGui::Text(std::format("Rotation:\tcos:{:.4f}, sin:{:.4f}", rot.c, rot.s).c_str());
        }

        const auto c = game::reg.view<Controllable>();
        if (p.begin() != p.end()) {
            Controllable* ctrla = &game::reg.get<Controllable>(p.front());
            ImGui::Text(std::format("WASD:\t{},{},{},{}", ctrla->w, ctrla->a, ctrla->s, ctrla->d).c_str());
        }

        ImGui::Checkbox("Debug physics", &game::rs.is_debug_physics);

        ImGui::End();
    }
    
    game::rs.rw->clear(Color(150, 150, 150));

    set_controllable_view();
    render_physics();

    ImGui::SFML::Render(*game::rs.rw);
    game::rs.rw->display();
}

void render::render_physics() {
    const auto view = game::reg.view<SpriteComp, b2BodyId>();

    std::vector<std::pair<entt::entity, Int8>> sprites;

    for (auto e : view) {
        SpriteComp s = game::reg.get<SpriteComp>(e);
        sprites.push_back({ e, s.layer });
    }

    // Сортируем по возрастанию значения (Int8)
    std::sort(sprites.begin(), sprites.end(), [](const auto& a, const auto& b) {
        return a.second > b.second; // Для убывания: `a.second > b.second`
    });

    for (auto s : sprites) {
        auto e = s.first;
        SpriteComp sprite_c = game::reg.get<SpriteComp>(e);
        b2BodyId bid = game::reg.get<b2BodyId>(e);

        b2Vec2 b2pos = b2Body_GetPosition(bid);
        Vector2f pos = Vector2f(b2pos.x, b2pos.y);

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

        Texture* texture = game::texmngr.getTexture(sprite_c.id);

        if (texture == nullptr) continue;
        texture->setSrgb(true);

        Sprite sprite;
        sprite.setTexture(*texture);
        
        sprite.setPosition(pos);
        sprite.setRotation(angle);
        sprite.setOrigin(Vector2f(texture->getSize().x / 2.0f, texture->getSize().y / 2.0f));
        game::rs.rw->draw(sprite);

        if (game::rs.is_debug_physics) {
            // Рисуем бокс
            sf::Vertex line[] =
            {
                sf::Vertex(sf::Vector2f(pos.x + dbg_size, pos.y + dbg_size)), sf::Vertex(sf::Vector2f(pos.x - dbg_size, pos.y + dbg_size)),
                sf::Vertex(sf::Vector2f(pos.x - dbg_size, pos.y + dbg_size)), sf::Vertex(sf::Vector2f(pos.x - dbg_size, pos.y - dbg_size)),
                sf::Vertex(sf::Vector2f(pos.x - dbg_size, pos.y - dbg_size)), sf::Vertex(sf::Vector2f(pos.x + dbg_size, pos.y - dbg_size)),
                sf::Vertex(sf::Vector2f(pos.x + dbg_size, pos.y - dbg_size)), sf::Vertex(sf::Vector2f(pos.x + dbg_size, pos.y + dbg_size)),
            };
            game::rs.rw->draw(line, 8, sf::Lines);

            Text text_position = Text(std::format("p:\t{:.4f},{:.4f}", pos.x, pos.y), game::rs.mfont, 24);
            Text text_rotation = Text(std::format("r:\t{:.4f},s:{:.4f}", rot.c, rot.s), game::rs.mfont, 24);
            Text text_velocity = Text(std::format("vel:\t{:.4f},{:.4f}", vel.x, vel.y), game::rs.mfont, 24);
            Text text_n_textur = Text(std::format(L"tex:\t{}", game::texmngr.getNamebyID(sprite_c.id)), game::rs.mfont, 24);

            const float text_scale = 0.2f;
            const Vector2f text_padding = Vector2f(2.5f, 0.0f);
            text_position.setScale(Vector2f(text_scale, text_scale));
            text_rotation.setScale(Vector2f(text_scale, text_scale));
            text_velocity.setScale(Vector2f(text_scale, text_scale));
            text_n_textur.setScale(Vector2f(text_scale, text_scale));

            pos += text_padding;

            text_position.setPosition(Vector2f(pos.x + dbg_size, pos.y - dbg_size));
            text_rotation.setPosition(Vector2f(pos.x + dbg_size, pos.y - dbg_size + 5));
            text_velocity.setPosition(Vector2f(pos.x + dbg_size, pos.y - dbg_size + 10));
            text_n_textur.setPosition(Vector2f(pos.x + dbg_size, pos.y - dbg_size + 15));

            game::rs.rw->draw(text_position);
            game::rs.rw->draw(text_rotation);
            game::rs.rw->draw(text_velocity);
            game::rs.rw->draw(text_n_textur);
        }
    }
}

void render::set_controllable_view()
{
    const auto v = game::reg.view<Controllable, b2BodyId>();
    if (v.begin() == v.end()) return;

    Controllable ctrla = v.get<Controllable>(v.front());
    b2BodyId bid = v.get<b2BodyId>(v.front());

    b2Vec2 pos = b2Body_GetPosition(bid);

    // Установка камеры на контролируемое
    Vector2u size = game::rs.rw->getSize();
    sf::View view_(sf::Vector2f(pos.x, pos.y), sf::Vector2f(size.x / 64.0f * 25, size.y / 64.0f * 25));
    game::rs.rw->setView(view_);
}
