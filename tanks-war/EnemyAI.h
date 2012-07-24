#include "stdafx.h"


#ifndef ENEMYAI_H
#define ENEMYAI_H
class EnemyAI
{
public:
	EnemyAI(sf::Vector2f StartPos, float Speed, float Range, int HealthPoints);

	// main function to draw and update AI and bullets
	void Update(sf::RenderWindow & App, sf::Vector2f TargetXY);

	// container of bullets
	std::list<class EnemyBullet*> m_Bullets;

	// returns sf::Sprite for Collision test
	sf::Sprite GetSprite();

	// set current enemy to immediately delete
	void SetToDelete();

	// returns current enemy's health
	int GetEnemyHP();

	// returns true if enemy is alive
	bool isAlive();

	// add damage to enemy. If less then HP auto-destroy
	void Hited(int Damage);

private:
	sf::Sprite m_enemy, m_enemyCannon;

	// actucal AI position
	sf::Vector2f m_Position;

	// AI speed
	float m_Speed;

	// vector of XY target's
	sf::Vector2f m_randomTarget;

	// vector of displacment
	sf::Vector2f m_enemyDis;

	// main function to determine target and do nessasary counts
	void ChooseTarget(sf::Vector2f TargetXY);

	// helpers to count rotation etc
	float m_xH, m_yH, m_rotation, _DLen;

	// helpful shape to display AI range
	sf::Shape m_shape;

	// range of AI atack
	float m_range;

	// to check if target is in range
	float _d;

	// shoot the bullet
	void Shoot(sf::RenderWindow & App);

	// update bullets
	void UpdateBullets(sf::RenderWindow & App);

	// to managment time
	sf::Clock m_Clock, m_Clock2;

	// pause between shoots
	float m_ReloadTime;

	// Enemy's health points
	int m_HP;

	// if true delete enemy
	bool m_ToDelete;
};
#endif