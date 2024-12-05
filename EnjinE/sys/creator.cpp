#include "creator.h"

#include <entt/entity/registry.hpp>
#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"

#include "comp/Player.h"
#include "comp/World.h"


RenderScene creator::makeRenderScene(entt::registry&reg) {
	RenderScene rs;

	RenderWindow* rw = new RenderWindow(sf::VideoMode({ 1280, 800 }), "CosmoS");
	rw->setFramerateLimit(60);
	rs.rw = rw;
	
	ImGui::SFML::Init(*rw);

	const auto e = reg.create();
	reg.emplace<RenderScene>(e, rs);

	return rs;
}

void creator::makeWorld(entt::registry&reg) {
	const auto e = reg.create();
	
	World world;
	world.timeStep = 1.0f / 60.0f;
	world.SubStepCount = 4;

	b2WorldDef wdef = b2DefaultWorldDef();
	wdef.gravity = b2Vec2_zero;
	wdef.enableSleep = false;
	b2WorldId wid = b2CreateWorld(&wdef);
	
	reg.emplace<World>(e, world);
	reg.emplace<b2WorldId>(e, wid);
}

entt::entity creator::makePlayer(entt::registry&reg) {
	// Ищем первый попавшийся мир
	const auto view = reg.view<World, b2WorldId>();
	if (view.begin() == view.end()) return entt::null;
	b2WorldId wid = view.get<b2WorldId>(view.front());

	const auto e = reg.create();

	// Создаем тело игрока
	b2BodyDef bdef = b2DefaultBodyDef();
	bdef.type = b2_dynamicBody;
	bdef.position = b2Vec2_zero;
	b2BodyId bid = b2CreateBody(wid, &bdef);

	// Создаем коллизию игрока
	b2ShapeDef sdef = b2DefaultShapeDef();
	// Задаем коллизии форму капсулы

	b2Capsule cap;
	cap.center1 = b2Vec2(0.0f, 1.0f);
	cap.center2 = b2Vec2(0.0f, -1.0f);
	cap.radius = 0.25f;
	b2ShapeId sid = b2CreateCapsuleShape(bid, &sdef, &cap);

	reg.emplace<Player>(e);
	reg.emplace<b2BodyId>(e, bid);

	return e;
}
