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
	void run(sf::RenderWindow& App);

	GameState _gameState;
	
private:
	MainMenu *_Menu;
	LoadContent *_loadContent;
	OptionsMenu *_optionsMenu;

	std::vector<cScreen*> Screens;
	int screen;
};