#include "stdafx.h"

#ifndef GAME_H
#define GAME_H
class Game : public cScreen
{
public:
	Game();
	// main loop function
	virtual int Run(sf::RenderWindow & App);
	

private:
	// once using function to init data
	void Init();
	bool m_inited;

	// main bool for main loop
	bool m_running;

	// events for window
	sf::Event m_Event;

	sf::Sprite m_map;
	 
	// center window on player,etc
	sf::View *m_View;

	class Player *m_player;

	// contain all enemy aI
	std::deque<class EnemyAI*> m_Enemies;
	
	// contain FPS
	float m_Framerate;

	// check collisions between objects
	void CheckCollision();

	// main method for all enemy AI
	void UpdateEnemies(sf::RenderWindow & App);

	// spawn enemy AI in random position
	void SpawnRandomEnemy();

	sf::Clock m_Clock, m_clock2;

	class MapManager *m_MapMng;

	// contaion game's score <--- just 4 fun
	unsigned short m_Score;

	// all physic's calc are doing here, physic engine
	class Physic *m_Physic;
};
#endif