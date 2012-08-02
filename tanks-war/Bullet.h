#include "stdafx.h"

#ifndef BULLET_H
#define BULLET_H
class Bullet
{
public:
	Bullet();
	Bullet(sf::RenderWindow & App, sf::Vector2f StartPosition, float Rotation, int BulletDamage);

	// main function to draw and update bullet's position
	void Update(sf::RenderWindow & App);

	// returns if bullet is ready to delete
	bool toDelete();

	// returns sf::Sprite to test Collisions
	sf::Sprite & GetSprite();

	// set current bullet to immediately delete
	void SetToDelete();

	// returns bullet's damage
	int GetBulletDamage();

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

	// bullet's damage
	int m_Damage;

	// helpers to count displacement
	float DLen, Dx, Dy; 

private:
	// mouse vector position
	sf::Vector2f m_MousePos;



};
#endif