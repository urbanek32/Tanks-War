#include "stdafx.h"


#ifndef ENEMYAI_H
#define ENEMYAI_H
class EnemyAI
{
public:
	EnemyAI(sf::Vector2f StartPos, float Speed, float Range);

	void Update(sf::RenderWindow & App, sf::Vector2f TargetXY);

	std::list<class Bullet*> m_Bullets;

private:
	sf::Sprite m_enemy, m_enemyCannon;

	sf::Vector2f m_Position;

	float m_Speed;

	sf::Vector2f m_randomTarget, m_prevRandomTarget;

	sf::Vector2f m_enemyDis;

	void ChooseTarget(sf::Vector2f TargetXY);

	float m_xH, m_yH, m_rotation, m_prevRotation;

	sf::Shape m_shape;

	float m_range;

	// shoot the bullet
	void Shoot(sf::RenderWindow & App);

	// update bullets
	void UpdateBullets(sf::RenderWindow & App);
};
#endif