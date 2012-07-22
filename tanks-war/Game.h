#include "stdafx.h"

#ifndef GAME_H
#define GAME_H
class Game : public cScreen
{
public:
	Game();
	virtual int Run(sf::RenderWindow & App);
	

private:
	void Init();
	bool m_inited;

	bool m_running;
	sf::Event m_Event;

	sf::Sprite m_map;

	sf::View *m_View;

	class Player *m_player;
	class EnemyAI *m_enemy;
};
#endif