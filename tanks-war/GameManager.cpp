#include "stdafx.h"

#ifdef CPP_0x11
GameManager* ptr=nullptr;
#else
GameManager* ptr=NULL;
#endif

GameManager::GameManager()
{
	_loadContent = new LoadContent();
	_gameState = ShowingMenu; screen = 1; // set int 1 : mean ShowingMenu
	_Menu = new MainMenu();
	_optionsMenu = new OptionsMenu();
	_joinLobby = new JoinGameLobby();

	Screens.push_back(_loadContent); // 0
	Screens.push_back(_Menu); // 1
	Screens.push_back(_optionsMenu); // 2
	Screens.push_back(_joinLobby); // 3
}


void GameManager::run(sf::RenderWindow& App)
{
	
		while(screen >= 0)
		{
			screen = Screens[screen]->Run(App);
		}
		


}

GameManager* GameManager::GetInstance()
{
	if(ptr==NULL) ptr = new GameManager();
	return ptr;
}