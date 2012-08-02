#include "stdafx.h"


#ifndef MAINMENU_H
#define MAINMENU_H
class MainMenu : public cScreen
{
public:
	MainMenu();
	virtual int Run(sf::RenderWindow & App);


private:
	sf::Sprite m_Background;

	sf::Event m_Event;

	bool m_Inited;

	sf::String *m_SinglePlayerLabel, *m_MultiPlayerLabel, *m_OptionsLabel, *m_ExitGameLabel;

	void ShowMainMenuLabels(sf::RenderWindow & App);

	sf::FloatRect m_SinglePlayerRect, m_MultiPlayerRect, m_OptionsRect, m_ExitGameRect;

	

	bool m_Running;
};
#endif