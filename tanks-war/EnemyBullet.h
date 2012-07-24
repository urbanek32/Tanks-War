#include "stdafx.h"

#ifndef ENEMYBULLET_H
#define ENEMYBULLET_H
class EnemyBullet : public Bullet
{
public:
	EnemyBullet();
	EnemyBullet(sf::Vector2f StartPosition, sf::Vector2f TargetPosition, float Rotation, int BulletDamage);

private:
	// target XY
	sf::Vector2f m_TargetXY;
};
#endif