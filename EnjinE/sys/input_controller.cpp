#include "input_controller.h"

#include "imgui.h"
#include <entt/entity/registry.hpp>

#include "comp/Controllable.h"

void input_controller::step(entt::registry&reg)
{
	keyboard_inputs(reg);
}

void input_controller::keyboard_inputs(entt::registry&reg)
{
	// Принимаем нажатия и вносим их для конролируемого ентити
	const auto view = reg.view<Controllable>();
	if (view.begin() == view.end()) return;

	Controllable* ctrlable = &reg.get<Controllable>(view.front());

	ctrlable->w = ImGui::IsKeyDown(ImGuiKey_W);
	ctrlable->a = ImGui::IsKeyDown(ImGuiKey_A);
	ctrlable->s = ImGui::IsKeyDown(ImGuiKey_S);
	ctrlable->d = ImGui::IsKeyDown(ImGuiKey_D);
}
