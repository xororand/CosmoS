#include "creator.h"

#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"

#include "comp/Player.h"
#include "comp/worlds/World.h"
#include "comp/worlds/MainWorld.h"
#include <comp/SpriteComp.h>
#include <comp/Controllable.h>
#include <comp/AI/AI.h>
#include <comp/holders/OreHolder.h>
#include <comp/AI/drons/space/AncientDrone.h>
#include <comp/AI/drons/space/AncientDroneStation.h>

// return null entt and destroy created
entt::entity creator::retdes(entt::entity e)
{
	game::reg.destroy(e);
	return entt::null;
}

void creator::makeRenderScene() {
	game::rs = RenderScene();

	RenderWindow* rw = new RenderWindow(sf::VideoMode({ 1280, 800 }), "CosmoS");
	rw->setFramerateLimit(60);
	rw->setVerticalSyncEnabled(true);
	game::rs.rw = rw;
	
	if (!game::rs.mfont.loadFromFile("Resources\\fonts\\Hardpixel-nn51.otf"))
	{
		// error...
	}
	game::rs.mfont.setSmooth(false);

	ImGui::SFML::Init(*rw);

	game::rs.rw->setActive();
}
void creator::makeTextureManager() {
	game::texmngr = TextureManager();
	game::texmngr.loadTexturesFromRootResources();
}

void creator::makeMainWorld() {
	const auto e = game::reg.create();
	
	World world;
	world.timeStep = 1.0f / 60.0f;
	world.SubStepCount = 4;

	b2WorldDef wdef = b2DefaultWorldDef();
	wdef.gravity = b2Vec2_zero;
	wdef.enableSleep = true;
	b2WorldId wid = b2CreateWorld(&wdef);
	
	game::reg.emplace<World>(e, world);
	game::reg.emplace<MainWorld>(e, world);
	game::reg.emplace<b2WorldId>(e, wid);

	creator::makePlayer(e);
	creator::makeComposition_MiningAntientDrones(e, b2Vec2(64.0f, 0.0f));

}

entt::entity creator::makePlayer(entt::entity world, b2Vec2 pos) {
	// Ищем первый попавшийся мир
	b2WorldId wid = game::reg.get<b2WorldId>(world);

	const auto e = game::reg.create();

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
	sprite_c.id = game::texmngr.getIDbyName(L"a-drone");
	sprite_c.layer = 1;

	game::reg.emplace<Player>(e);
	game::reg.emplace<Controllable>(e);
	game::reg.emplace<SpriteComp>(e, sprite_c);
	game::reg.emplace<b2BodyId>(e, bid);

	return e;
}

entt::entity creator::makeAncientMiningDrone(entt::entity world, entt::entity station, b2Vec2 pos) {
	b2WorldId wid = game::reg.get<b2WorldId>(world);

	const auto e = game::reg.create();

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
	size_t id = game::texmngr.getIDbyName(L"a-drone");
	if (id == NO_TEXTURE) return retdes(e);
	sprite_c.id = id;
	sprite_c.layer = 1;

	AncientMiningDrone amd;
	amd.station = station;

	game::reg.emplace<AI>(e);
	game::reg.emplace<AncientDrone>(e);
	game::reg.emplace<AncientMiningDrone>(e, amd);
	game::reg.emplace<OreHolder>(e);
	game::reg.emplace<SpriteComp>(e, sprite_c);
	game::reg.emplace<b2BodyId>(e, bid);

	return e;
}
entt::entity creator::makeAncientMiningDroneStation(entt::entity world, b2Vec2 pos) {
	// Ищем первый попавшийся мир
	b2WorldId wid = game::reg.get<b2WorldId>(world);

	const auto e = game::reg.create();

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
	size_t id = game::texmngr.getIDbyName(L"asteroid-ancient-station");
	if (id == NO_TEXTURE) return retdes(e);
	sprite_c.id = id;
	sprite_c.layer = -1;

	// Вмещение начальной руды
	OreHolder ore_h;

	b2MassData mass_data;
	mass_data.center = b2Vec2_zero;
	mass_data.mass = 10 * STANDART_ORE_COUNT; // 10 кг - 1 кусок руды
	mass_data.rotationalInertia = 0.0f;

	b2Body_SetMassData(bid, mass_data);

	game::reg.emplace<AncientDroneStation>(e);
	game::reg.emplace<OreHolder>(e, ore_h);
	game::reg.emplace<SpriteComp>(e, sprite_c);
	game::reg.emplace<b2BodyId>(e, bid);
	return e;
}
entt::entity creator::makeAsteroid(entt::entity world, Ore::OreType type, b2Vec2 pos) {
	b2WorldId wid = game::reg.get<b2WorldId>(world);

	const auto e = game::reg.create();

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
	size_t texid = Ore::getTexIDbyOreType(game::reg, type);
	if (texid == NO_TEXTURE) return retdes(e);
	sprite_c.id = texid;
	sprite_c.layer = -1;

	// Вмещение руды
	OreHolder ore_h;

	// Вмещаем STANDART_ORE_COUNT штучек руды
	for (int i = 0; i < STANDART_ORE_COUNT; i++) {
		Ore ore;
		ore.count = MAX_ORE_COUNT;
		ore.type = type;
		ore_h.ores.push_back(ore);
	}

	b2MassData mass_data;
	mass_data.center = b2Vec2_zero;
	mass_data.mass = 100 * STANDART_ORE_COUNT; // 100 кг - 1 кусок руды
	mass_data.rotationalInertia = 0.0f;

	b2Body_SetMassData(bid, mass_data);

	game::reg.emplace<Asteroid>(e, aster);
	game::reg.emplace<OreHolder>(e, ore_h);
	game::reg.emplace<SpriteComp>(e, sprite_c);
	game::reg.emplace<b2BodyId>(e, bid);
	return e;
}

// КОМПОЗИЦИИ
entt::entity creator::makeComposition_MiningAntientDrones(entt::entity world, b2Vec2 pos) {
	entt::entity ds_e = makeAncientMiningDroneStation(world, pos);
	if (ds_e == entt::null) return entt::null;

	AncientDroneStation* station = &game::reg.get<AncientDroneStation>(ds_e);

	int asterc = rand() % 3 + 1;
	int dronc = 2 * asterc;

	// спавним дронов
	for (int i = 0; i < dronc; i++) {
		const auto e = makeAncientMiningDrone(world, ds_e, pos + b2Vec2(rand() % 256 - 128, rand() % 256 - 128));
		station->drones.push_back(e);
	}

	// спавним астероиды
	for (int i = 0; i < asterc; i++) {
		const auto e = makeAsteroid(world, Ore::getRand(), pos + b2Vec2(rand() % 256 - 128, rand() % 256 - 128));
		//station->drones.push_back(e);
	}

	return ds_e;
}


