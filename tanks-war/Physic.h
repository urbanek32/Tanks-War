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


class Physic
{
public:
	Physic();
	~Physic();

	void Tick(sf::RenderWindow & App, float frequency);

private:
	b2Vec2 *gravity;
	b2Vec2 *floor;
	b2World *world;

	sf::Sprite groundSprite;
	b2BodyDef *groundBodyDef;
	b2Body *groundBody;
	b2PolygonShape *groundBox;

	std::vector<PhysicObject> m_Objects;
	
	PhysicObject _PO;


};
