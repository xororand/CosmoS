#include "render.h"

void render::frame(entt::registry&reg, RenderScene rs) {
    ImGui::SFML::Update(*rs.rw, rs.deltaClock.restart());


    ImGui::ShowDemoWindow();

    ImGui::Begin("Hello, world!");
    ImGui::Button("Look at this pretty button");
    ImGui::End();

    rs.rw->clear();

    ImGui::SFML::Render(*rs.rw);
    rs.rw->display();
}
