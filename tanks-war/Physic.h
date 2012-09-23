#include "stdafx.h"


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


private:
	b2Vec2 *gravity;
	b2World *world;

	sf::Sprite groundSprite;
	b2BodyDef *groundBodyDef;
	b2Body *groundBody;
	b2PolygonShape *groundBox;

	sf::Sprite groundSprite2;
	b2BodyDef *groundBodyDef2;
	b2Body *groundBody2;
	b2PolygonShape *groundBox2;

	std::vector<PhysicObject> m_Objects;

	std::vector<WallObject*> m_WallObjects;
	
	PhysicObject _PO;

	float rot, v, force;
};
