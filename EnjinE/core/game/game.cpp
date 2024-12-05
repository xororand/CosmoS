#include "game.h"

#include "sys/creator.h"
#include "sys/physics.h"


game::game() {
}

game::~game()
{
}

int game::run()
{
    sf::Clock deltaClock;
    RenderWindow* window = creator::makeWindow(reg);

    creator::makeWorld(reg);
    creator::makePlayer(reg);
    
    // Главный цикл
    while (window->isOpen()) {
        Event event;
        while (const auto eventbool = window->pollEvent(event)) {
            ImGui::SFML::ProcessEvent(*window, event);
            
            if (event.type == Event::Closed) {
                window->close();
            }
        }

        ImGui::SFML::Update(*window, deltaClock.restart());

        ImGui::ShowDemoWindow();

        ImGui::Begin("Hello, world!");
        ImGui::Button("Look at this pretty button");
        ImGui::End();

        window->clear();



        ImGui::SFML::Render(*window);
        window->display();
    }

    return 0;
}
