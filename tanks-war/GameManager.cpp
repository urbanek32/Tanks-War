#include "stdafx.h"

#ifdef CPP_0x11
GameManager* ptr=nullptr;
#else
GameManager* ptr=NULL;
#endif

std::map<std::string, std::string>globals;

GameManager::GameManager()
{
	_gameState = ShowingMenu; m_screen = 0; // set int 1 : mean ShowingMenu || set int 0 : mean LoadContent
	
	m_loadContent = new LoadContent();
	m_Menu = new MainMenu();
	m_Options = new OptionsMenu();
	m_joinGameLobby = new JoinGameLobby();
	m_game = new Game();
//	m_OnlineGame = new OnlineGame();
	

	m_Screens.push_back(m_loadContent); // 0
	m_Screens.push_back(m_Menu); // 1
	m_Screens.push_back(m_Options); // 2
	m_Screens.push_back(m_joinGameLobby); // 3
	m_Screens.push_back(m_game); // 4
//	m_Screens.push_back(m_OnlineGame); // 5
	
	m_SocketUDP.SetBlocking(false);
}


void GameManager::run(sf::RenderWindow & App)
{
		while(m_screen >= 0)
		{
			m_screen = m_Screens[m_screen]->Run(App);
		}

}

GameManager* GameManager::GetInstance()
{
	if(ptr==NULL) ptr = new GameManager();
	return ptr;
}