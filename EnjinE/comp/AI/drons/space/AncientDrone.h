#pragma once

struct AncientDrone {
	entt::entity station = entt::null; // ������� � ������� ������� ������ ���������
	entt::entity target = entt::null; // ������
	
	// �������� �����
	float speed = 5.0f;
};
struct AncientMiningDrone {};