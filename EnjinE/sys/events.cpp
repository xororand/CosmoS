#include "events.h"
#include <comp/RenderScene.h>

void gui_events::step(RenderWindow*rw) {
    Event event;
    while (const auto eventbool = rw->pollEvent(event)) {
        ImGui::SFML::ProcessEvent(*rw, event);
        if (event.type == Event::Closed) {
            rw->close();
        }
    }
}
