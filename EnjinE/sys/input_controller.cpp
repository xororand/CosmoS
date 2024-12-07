#include "input_controller.h"

#include "imgui.h"
#include <entt/entity/registry.hpp>

#include "comp/Controllable.h"

void input_controller::tick(entt::registry&reg)
{
	keyboard_inputs(reg);
}

void input_controller::keyboard_inputs(entt::registry&reg)
{
	// Принимаем нажатия и вносим их для конролируемого ентити
	const auto view = reg.view<Controllable>();
	if (view.begin() == view.end()) return;

	Controllable ctrlable = reg.get<Controllable>(view.front());

	ctrlable.w = ImGui::IsKeyPressed(ImGuiKey_W);
	ctrlable.a = ImGui::IsKeyPressed(ImGuiKey_A);
	ctrlable.s = ImGui::IsKeyPressed(ImGuiKey_S);
	ctrlable.d = ImGui::IsKeyPressed(ImGuiKey_D);

	reg.replace<Controllable>(view.front(), ctrlable);
}
