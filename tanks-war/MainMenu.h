#include "stdafx.h"


class MainMenu : public cScreen
{
public:
	MainMenu();
	virtual int Run(sf::RenderWindow & App);


private:
	sf::Sprite m_background;

	sf::Event m_Event;

	bool m_Inited;
	sf::String *m_joinGameLabel, *m_optionsLabel, *m_exitGameLabel;
	void ShowMainMenuLabels(sf::RenderWindow & App);
	sf::FloatRect m_joinGameRect, m_optionsRect, m_exitGameRect;

	

	bool m_Running;
};