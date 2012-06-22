#include "stdafx.h"


class MainMenu : public cScreen
{
public:
	MainMenu();
	virtual int Run(sf::RenderWindow& App);


private:
	sf::Sprite background;
	sf::Sprite logo;

	sf::Event m_Event;
	sf::Clock m_clock;
	
	sf::String m_text_joingame;
	sf::String m_text_options;
	sf::String m_text_exitgame;

	sf::FloatRect m_JoinRect, m_OptionsRect, m_QuitRect;

	bool Running;
};