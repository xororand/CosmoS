#include "events.h"
#include <comp/RenderScene.h>

void events::tick(entt::registry&reg, RenderWindow*rw)
{
    Event event;
    while (const auto eventbool = rw->pollEvent(event)) {
        ImGui::SFML::ProcessEvent(*rw, event);
        if (event.type == Event::Closed) {
            rw->close();
        }
    }
}
