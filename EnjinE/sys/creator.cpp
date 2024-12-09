#include "creator.h"

#include <entt/entity/registry.hpp>
#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"

#include "comp/Player.h"
#include "comp/World.h"
#include <comp/SpriteComp.h>
#include <comp/Controllable.h>
#include <comp/AI.h>
#include <comp/OreHolder.h>
#include <comp/AncientDrone.h>
#include <comp/AncientDroneStation.h>

RenderScene creator::makeRenderScene(entt::registry&reg) {
	RenderScene rs;

	RenderWindow* rw = new RenderWindow(sf::VideoMode({ 1280, 800 }), "CosmoS");
	rw->setFramerateLimit(60);
	rs.rw = rw;
	
	if (!rs.mfont.loadFromFile("Resources\\fonts\\Hardpixel-nn51.otf"))
	{
		// error...
	}
	rs.mfont.setSmooth(false);

	ImGui::SFML::Init(*rw);

	const auto e = reg.create();
	reg.emplace<RenderScene>(e, rs);

	rs.rw->setActive();

	return rs;
}
TextureManager creator::makeTextureManager(entt::registry&reg) {
	TextureManager tm = TextureManager();
	tm.loadTexturesFromRootResources();

	const auto e = reg.create();
	reg.emplace<TextureManager>(e, tm);

	return tm;
}

void creator::makeWorld(entt::registry&reg) {
	const auto e = reg.create();
	
	World world;
	world.timeStep = 1.0f / 60.0f;
	world.SubStepCount = 4;

	b2WorldDef wdef = b2DefaultWorldDef();
	wdef.gravity = b2Vec2_zero;
	wdef.enableSleep = true;
	b2WorldId wid = b2CreateWorld(&wdef);
	
	reg.emplace<World>(e, world);
	reg.emplace<b2WorldId>(e, wid);
}

entt::entity creator::makePlayer(entt::registry&reg, b2Vec2 pos) {
	const auto tm = reg.view<TextureManager>();
	if (tm.begin() == tm.end()) return entt::null;
	TextureManager texmngr = reg.get<TextureManager>(tm.front());

	// Ищем первый попавшийся мир
	const auto view = reg.view<World, b2WorldId>();
	if (view.begin() == view.end()) return entt::null;
	b2WorldId wid = view.get<b2WorldId>(view.front());

	const auto e = reg.create();

	// Создаем тело игрока
	b2BodyDef bdef = b2DefaultBodyDef();
	bdef.type = b2_dynamicBody;
	bdef.position = pos;
	bdef.fixedRotation = true;
	b2BodyId bid = b2CreateBody(wid, &bdef);

	// Создаем коллизию игрока
	b2ShapeDef sdef = b2DefaultShapeDef();
	// Задаем коллизии форму капсулы

	b2Circle cir;
	cir.center = b2Vec2_zero;
	cir.radius = 18.0f;

	b2ShapeId sid = b2CreateCircleShape(bid, &sdef, &cir);

	SpriteComp sprite_c;
	sprite_c.id = texmngr.getIDbyName(L"a-drone");

	reg.emplace<Player>(e);
	reg.emplace<Controllable>(e);
	reg.emplace<SpriteComp>(e, sprite_c);
	reg.emplace<b2BodyId>(e, bid);

	return e;
}

entt::entity creator::makeAncientMiningDrone(entt::registry&reg, entt::entity station, b2Vec2 pos) {
	const auto tm = reg.view<TextureManager>();
	if (tm.begin() == tm.end()) return entt::null;
	TextureManager texmngr = reg.get<TextureManager>(tm.front());

	// Ищем первый попавшийся мир
	const auto view = reg.view<World, b2WorldId>();
	if (view.begin() == view.end()) return entt::null;
	b2WorldId wid = view.get<b2WorldId>(view.front());

	const auto e = reg.create();

	// Создаем тело
	b2BodyDef bdef = b2DefaultBodyDef();
	bdef.type = b2_dynamicBody;
	bdef.position = pos;
	bdef.fixedRotation = true;
	b2BodyId bid = b2CreateBody(wid, &bdef);

	// Создаем коллизию
	b2ShapeDef sdef = b2DefaultShapeDef();
	// Задаем коллизии форму капсулы

	b2Circle cir;
	cir.center = b2Vec2_zero;
	cir.radius = 18.0f;

	b2ShapeId sid = b2CreateCircleShape(bid, &sdef, &cir);

	SpriteComp sprite_c;
	sprite_c.id = texmngr.getIDbyName(L"a-drone");

	AncientMiningDrone amd;
	amd.station = station;

	reg.emplace<AI>(e);
	reg.emplace<AncientDrone>(e);
	reg.emplace<AncientMiningDrone>(e, amd);
	reg.emplace<OreHolder>(e);
	reg.emplace<SpriteComp>(e, sprite_c);
	reg.emplace<b2BodyId>(e, bid);

	return e;
}
entt::entity creator::makeAncientMiningDroneStation(entt::registry&reg, b2Vec2 pos)
{
	const auto tm = reg.view<TextureManager>();
	if (tm.begin() == tm.end()) return entt::null;
	TextureManager texmngr = reg.get<TextureManager>(tm.front());

	// Ищем первый попавшийся мир
	const auto view = reg.view<World, b2WorldId>();
	if (view.begin() == view.end()) return entt::null;
	b2WorldId wid = view.get<b2WorldId>(view.front());

	const auto e = reg.create();

	// Создаем тело
	b2BodyDef bdef = b2DefaultBodyDef();
	bdef.type = b2_dynamicBody;
	bdef.position = pos;
	float degree = (float)(rand() % 360) - 180.0f;
	bdef.rotation = b2MakeRot(degree * (b2_pi / 180));

	b2BodyId bid = b2CreateBody(wid, &bdef);

	// Создаем коллизию
	b2ShapeDef sdef = b2DefaultShapeDef();
	// Задаем коллизии форму капсулы

	b2Circle cir;
	cir.center = b2Vec2_zero;
	cir.radius = 52.0f;

	b2ShapeId sid = b2CreateCircleShape(bid, &sdef, &cir);

	// Выбор текстуры
	SpriteComp sprite_c;
	sprite_c.id = texmngr.getIDbyName(L"asteroid");

	// Вмещение начальной руды
	OreHolder ore_h;

	b2MassData mass_data;
	mass_data.center = b2Vec2_zero;
	mass_data.mass = 10 * STANDART_ORE_COUNT; // 10 кг - 1 кусок руды
	mass_data.rotationalInertia = 0.0f;

	b2Body_SetMassData(bid, mass_data);

	reg.emplace<AncientDroneStation>(e);
	reg.emplace<OreHolder>(e, ore_h);
	reg.emplace<SpriteComp>(e, sprite_c);
	reg.emplace<b2BodyId>(e, bid);
	return e;
}
entt::entity creator::makeComposition_MiningAntientDrones(entt::registry& reg, b2Vec2 pos) {
	entt::entity ds_e = makeAncientMiningDroneStation(reg, pos);
	if (ds_e == entt::null) return entt::null;

	AncientDroneStation* station = &reg.get<AncientDroneStation>(ds_e);

	// спавним дронов
	for (int i = 0; i < rand() % 10 + 1; i++) { 
		const auto e = makeAncientMiningDrone(reg, ds_e, pos + b2Vec2(rand() % 256 - 128, rand() % 256 - 128));
		station->drones.push_back(e);
	}

	return ds_e;
}

entt::entity creator::makeAsteroid(entt::registry&reg, Asteroid::AsteroidType type, b2Vec2 pos)
{
	const auto tm = reg.view<TextureManager>();
	if (tm.begin() == tm.end()) return entt::null;
	TextureManager texmngr = reg.get<TextureManager>(tm.front());

	// Ищем первый попавшийся мир
	const auto view = reg.view<World, b2WorldId>();
	if (view.begin() == view.end()) return entt::null;
	b2WorldId wid = view.get<b2WorldId>(view.front());

	const auto e = reg.create();

	// Создаем тело
	b2BodyDef bdef = b2DefaultBodyDef();
	bdef.type = b2_dynamicBody;
	bdef.position = pos;
	float degree = (float)(rand() % 360) - 180.0f;
	bdef.rotation = b2MakeRot(degree * (b2_pi / 180) );

	b2BodyId bid = b2CreateBody(wid, &bdef);

	// Создаем коллизию
	b2ShapeDef sdef = b2DefaultShapeDef();
	// Задаем коллизии форму капсулы

	b2Circle cir;
	cir.center = b2Vec2_zero;
	cir.radius = 52.0f;

	b2ShapeId sid = b2CreateCircleShape(bid, &sdef, &cir);

	Asteroid aster;
	aster.type = type;

	// Выбор текстуры
	SpriteComp sprite_c;
	switch (type) {
		case Asteroid::AsteroidType::STONE:
			sprite_c.id = texmngr.getIDbyName(L"asteroid");
			break;
		case Asteroid::AsteroidType::IRON:
			sprite_c.id = texmngr.getIDbyName(L"asteroid-iron");
			break;
		case Asteroid::AsteroidType::URANIUM:
			sprite_c.id = texmngr.getIDbyName(L"asteroid-uranium");
			break;
	}

	// Вмещение руды
	OreHolder ore_h;
	switch (type) {
		case Asteroid::AsteroidType::IRON:
			// Вмещаем STANDART_ORE_COUNT штучек руды
			for (int i = 0; i < STANDART_ORE_COUNT; i++) {
				Ore ore;
				ore.count = MAX_ORE_COUNT;
				ore.type = Ore::OreType::IRON;
				ore_h.ores.push_back(ore);
			}
			break;
		case Asteroid::AsteroidType::URANIUM:
			// Вмещаем STANDART_ORE_COUNT штучек руды
			for (int i = 0; i < STANDART_ORE_COUNT; i++) {
				Ore ore;
				ore.count = MAX_ORE_COUNT;
				ore.type = Ore::OreType::URANIUM;
				ore_h.ores.push_back(ore);
			}
			break;
	}

	b2MassData mass_data;
	mass_data.center = b2Vec2_zero;
	mass_data.mass = 100 * STANDART_ORE_COUNT; // 100 кг - 1 кусок руды
	mass_data.rotationalInertia = 0.0f;

	b2Body_SetMassData(bid, mass_data);

	reg.emplace<Asteroid>(e, aster);
	reg.emplace<OreHolder>(e, ore_h);
	reg.emplace<SpriteComp>(e, sprite_c);
	reg.emplace<b2BodyId>(e, bid);
	return e;
}

