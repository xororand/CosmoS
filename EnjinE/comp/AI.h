#pragma once

struct AI {};

struct AncientMiningBase {
	// ����� ����������� �����
	std::vector<entt::entity> drons;
};
struct AncientMiningDrone {
	// ���� � ������� ������� ������ ���������
	entt::entity base;
};