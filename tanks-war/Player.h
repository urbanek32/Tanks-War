#include "stdafx.h"

#ifndef PLAYER_H
#define PLAYER_H
class Player
{
public:
	Player();

	// returns instance to this object
	static Player* GetInstance();

	// main function to draw, update player's position and bullets
	void Update(sf::RenderWindow & App, class Physic & physic);

	// FIXME: Cut method of above one, just to compile this crap 
	void Update(sf::RenderWindow & App);

	// returns current player's position
	sf::Vector2f & GetPlayerPosition();

	// returns current player's speed
	double & GetPlayerSpeed();

	// return current player's rotation angle
	float GetPlayerRotation();

	// return current player's cannon's rotation angle
	float & GetCannonRotation();

	// player's bullet's container
	std::deque<class Bullet*> m_Bullets;

	// returns reloading state
	bool isReloading();

	// returns sf::Sprite for Collision test
	sf::Sprite & GetSprite();

	//returns player's health points
	int GetPlayerHP();

	// add damage to hp. Die if hp <= 0
	void Hited(int Damage);

private:
	sf::Sprite m_player, m_cannon;

	// once using function to init data
	bool m_inited;
	void Init(class Physic & physic);

	// to managment time
	sf::Clock m_clock, m_clock2;

	// shoot the bullet
	void Shoot(sf::RenderWindow & App);

	// update bullets
	void UpdateBullets(sf::RenderWindow & App);

	// player's speed
	double m_V; 

	// degree of rotation
	int m_rotationDegree;

	// variable to rotate player
	int m_rotation;

	// max player's speed and backspeed
	const double m_maxPlayerSpeed;
	const double m_maxPlayerBackSpeed;

	// player's displacement vector
	sf::Vector2<double> m_disVec;

	// vector of player's position
	sf::Vector2f m_playerPozVec;

	// mouse position
	sf::Vector2f m_mousePozVec;

	// helpers to calculate rotation angle for cannon
	float m_xH, m_yH, m_cannonRotation;

	// is reloading
	bool m_reload;

	// Player's HP
	int m_Health;

};
#endif