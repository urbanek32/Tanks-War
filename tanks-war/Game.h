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

	bool m_running;
	sf::Event m_Event;

	sf::Sprite m_map;

	sf::View *m_View;

	class Player *m_player;

	std::deque<class EnemyAI*> m_Enemies;
	
	float m_Framerate;

	void CheckCollision();

	void UpdateEnemies(sf::RenderWindow & App);

	void SpawnRandomEnemy();

	sf::Clock m_Clock, m_clock2;

	class MapManager *m_MapMng;

	unsigned short m_Score;
};
#endif