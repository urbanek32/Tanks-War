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
	void run(tgui::Window & App);

	GameState _gameState;
	
private:
	LoadContent *m_loadContent;
	MainMenu *m_Menu;
	OptionsMenu *m_Options;

	std::vector<cScreen*> m_Screens;
	int m_screen;
};