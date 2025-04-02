#pragma once

struct AncientDrone {
	entt::entity station = entt::null; // Станция у которой берется логика поведения
	entt::entity target = entt::null; // Таргет
	
	// Скорость дрона
	float speed = 5.0f;
};
struct AncientMiningDrone {};