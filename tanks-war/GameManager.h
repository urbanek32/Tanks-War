#include "stdafx.h"

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
	LoadContent *m_loadContent;
	MainMenu *m_Menu;
	OptionsMenu *m_Options;
	class JoinGameLobby *m_joinGameLobby;

	std::vector<cScreen*> m_Screens;
	int m_screen;
};