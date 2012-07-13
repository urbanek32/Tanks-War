#include "stdafx.h"

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
enum GameState
{
	Loading, ShowingMenu, Options, Joining, Playing, Exiting
};

class GameManager
{
public:
	GameManager();
	static GameManager* GetInstance();
	void run(sf::RenderWindow & App);

	GameState _gameState;

	
private:
	// pointers to screens
	class LoadContent *m_loadContent;
	class MainMenu *m_Menu;
	class OptionsMenu *m_Options;
	class JoinGameLobby *m_joinGameLobby;
	class Game *m_game;

	std::vector<cScreen*> m_Screens;
	int m_screen;
};
#endif