#include "stdafx.h"

#ifndef BULLET_H
#define BULLET_H
class Bullet
{
public:
	Bullet(sf::RenderWindow & App, sf::Vector2f StartPosition, float Rotation);

	// main function to draw and update bullet's position
	void Update(sf::RenderWindow & App);

	// returns if bullet is ready to delete
	bool isAlive();


private:
	// mouse vector position
	sf::Vector2f m_MousePos;

	// bullet displacement
	sf::Vector2f m_BulletDis;

	// start position = cannon position
	sf::Vector2f m_StartPos;

	// rotation angle
	float m_rotation;

	// bullet's speed
	float m_V;

	// if true delete bullet
	bool m_alive;

	// sprite of bullet
	sf::Sprite m_bullet;

	// range/lifetime of bullet
	int m_lifetime;

};
#endif