#include "stdafx.h"

#ifndef BULLET_H
#define BULLET_H
class Bullet
{
public:
	Bullet();
	Bullet(sf::RenderWindow & App, sf::Vector2f StartPosition, float Rotation);

	// main function to draw and update bullet's position
	void Update(sf::RenderWindow & App);

	// returns if bullet is ready to delete
	bool toDelete();

protected:
	// bullet displacement
	sf::Vector2f m_BulletDis;

	// start position = cannon position
	sf::Vector2f m_StartPos;

	// rotation angle
	float m_Rotation;

	// bullet's speed
	float m_V;

	// if true delete bullet
	bool m_ToDelete;

	// sprite of bullet
	sf::Sprite m_Bullet;

	// range/lifetime of bullet
	int m_Lifetime;

private:
	// mouse vector position
	sf::Vector2f m_MousePos;



};
#endif