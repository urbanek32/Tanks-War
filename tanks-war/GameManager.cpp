#include "stdafx.h"

#ifdef CPP_0x11
GameManager* ptr=nullptr;
#else
GameManager* ptr=NULL;
#endif

GameManager::GameManager()
{
	_gameState = ShowingMenu; m_screen = 0; // set int 1 : mean ShowingMenu
	
	m_loadContent = new LoadContent();
	m_Menu = new MainMenu();
	m_Options = new OptionsMenu();
	

	m_Screens.push_back(m_loadContent); // 0
	m_Screens.push_back(m_Menu); // 1
	m_Screens.push_back(m_Options); // 2
	
}


void GameManager::run(tgui::Window & App)
{
		while(m_screen >= 0)
		{
			m_screen = m_Screens[m_screen]->Run(App);
		}

		delete m_loadContent;
		delete m_Menu;
		delete m_Options;
}

GameManager* GameManager::GetInstance()
{
	if(ptr==NULL) ptr = new GameManager();
	return ptr;
}