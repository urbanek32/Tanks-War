#include "stdafx.h"


MainMenu::MainMenu()
{
		
	m_Running = true;
	m_Inited = false;
}	


int MainMenu::Run(tgui::Window & App)
{
	_texture = new sf::Texture();
	_texture->loadFromFile("CONTENT\\tlo-test.png");

	m_background.setTexture(*_texture);

	while(m_Running)
	{
		App.clear();
		App.draw(m_background);

		while(App.pollEvent(m_Event))
		{
			if(m_Event.type == sf::Event::Closed)
			{
				m_Running = false;
				return (-1);
			}

		}

		ShowMainMenuLabels(App);


		
		
		App.display();
		sf::sleep(sf::milliseconds(10));
	} // end of while(Running)
	
	delete _texture;
	delete m_joinGameLabel;
	delete m_optionsLabel;
	delete m_exitGameLabel;

	return (-1);
}

void MainMenu::ShowMainMenuLabels(tgui::Window & App)
{
	if(!m_Inited)
	{
		m_joinGameLabel = new sf::Text("Join Game", LoadContent::GetInstance()->m_font, 50);
		m_joinGameLabel->setColor(sf::Color::Red);
		m_joinGameLabel->setPosition(800, 300);
		m_joinGameRect = m_joinGameLabel->getLocalBounds();

		m_optionsLabel = new sf::Text("Options", LoadContent::GetInstance()->m_font, 50);
		m_optionsLabel->setColor(sf::Color::Red);
		m_optionsLabel->setPosition(800, 380);

		m_exitGameLabel = new sf::Text("Exit Game", LoadContent::GetInstance()->m_font, 50);
		m_exitGameLabel->setColor(sf::Color::Red);
		m_exitGameLabel->setPosition(800, 460);

		m_Inited = true;
	}
	App.draw(*m_joinGameLabel);
	App.draw(*m_optionsLabel);
	App.draw(*m_exitGameLabel);
}