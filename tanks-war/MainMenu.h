#include "stdafx.h"


class MainMenu : public cScreen
{
public:
	MainMenu();
	virtual int Run(tgui::Window & App);


private:
	sf::Sprite m_background;
	sf::Texture *_texture;

	sf::Event m_Event;

	bool m_Inited;
	sf::Text *m_joinGameLabel, *m_optionsLabel, *m_exitGameLabel;
	void ShowMainMenuLabels(tgui::Window & App);
	sf::FloatRect m_joinGameRect, m_optionsRect, m_exitGameRect;


	bool m_Running;
};