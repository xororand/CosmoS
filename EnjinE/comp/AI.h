#pragma once

struct AI {};

struct AncientMiningBase {
	// Дроны управляемые базой
	std::vector<entt::entity> drons;
};
struct AncientMiningDrone {
	// База у которой берется логика поведения
	entt::entity base;
};