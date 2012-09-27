#include "stdafx.h"

#ifndef PHYSIC_H
#define PHYSIC_H
struct PhysicObject
{
	sf::Sprite sprite;
	sf::Vector2f position; // position in SFML
	float rotation;

	b2Vec2 physicVert[4]; // vertex position in box2d
	b2BodyDef bodyDef;
	b2Body *body;
	b2PolygonShape box;
	b2FixtureDef fixture;
};

struct WallObject
{
	b2Vec2 position;
	b2BodyDef *bodyDef;
	b2Body *body;
	b2PolygonShape *shape;
	b2FixtureDef *fixture;
};

struct PlayerObject
{
	// return player's position in sf::Vector2f
	sf::Vector2f GetPosition();

	b2BodyDef *bodyDef;
	b2Body *body;
	b2PolygonShape *shape;
	b2FixtureDef *fixture;
	
	// player's velocity
	b2Vec2 vel;

	// player's rotation
	float rotation;
};


class Physic
{
public:
	Physic();
	~Physic();

	// do physic's simulation
	void Tick(sf::RenderWindow & App, float frequency);

	// add map tiles to physic's engine
	void LoadStaticMapObjects(float OX, float OY, unsigned int TileWidth, unsigned int TileHeigth);

	// returns instance to this object
	static Physic* GetInstance();

	// add player to physic's engine
	void AddPlayer(float OX, float OY, unsigned int TileWidth, unsigned int TileHeigth);

	// return const pointer to PlayerObject. First player = [0]index
	PlayerObject* GetPlayer(unsigned int index);

private:
	// to init physic world
	b2Vec2 *gravity;
	b2World *world;

	// contains all players in game
	std::vector<PlayerObject*> m_PlayerObjects;

	// contains all map tiles
	std::vector<WallObject*> m_WallObjects;

};
#endif