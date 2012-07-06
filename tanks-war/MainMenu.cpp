#include "stdafx.h"


MainMenu::MainMenu()
{
	

	m_Running = true;
	m_Inited = false;
}	


int MainMenu::Run(sf::RenderWindow & App)
{
	
	

	while(m_Running)
	{
		App.Clear();
		App.Draw(m_background);

		while(App.GetEvent(m_Event))
		{
			if(m_Event.Type == sf::Event::Closed)
			{
				m_Running = false;
				return (-1);
			}
			
			if(m_Event.Type == sf::Event::MouseButtonPressed && m_joinGameRect.Contains(m_Event.MouseButton.X, m_Event.MouseButton.Y) )
			{
				// GO TO JOINLOBBY
				return 3;
			}

			if(m_Event.Type == sf::Event::MouseButtonPressed && m_optionsRect.Contains(m_Event.MouseButton.X, m_Event.MouseButton.Y) )
			{
				// GO TO OPTIONS
				return 2;
			}

			if(m_Event.Type == sf::Event::MouseButtonPressed && m_exitGameRect.Contains(m_Event.MouseButton.X, m_Event.MouseButton.Y) )
			{
				// EXIT GAME
				m_Running = false;
				return (-1);
			}
		}

		ShowMainMenuLabels(App);

std::ostringstream bufor;
sf::String tdebug;
tdebug.SetFont(sf::Font::GetDefaultFont());
tdebug.SetSize(20);
tdebug.SetColor(sf::Color(255,0,0,255));
bufor << "MapSize= " << gResMng.Get_MapSize();
tdebug.SetText(bufor.str());
App.Draw(tdebug);			
		

		
		App.Display();
		sf::Sleep(0.01f);
	} // end of while(Running)
	


	return (-1);
}

void MainMenu::ShowMainMenuLabels(sf::RenderWindow & App)
{	
	if(!m_Inited)
	{	
		m_background.SetImage(gResMng.Get_Image("CONTENT//tlo-test.png"));

		m_joinGameLabel = new sf::String("Join Game", LoadContent::GetInstance()->m_font, 50);
		m_joinGameLabel->SetColor(sf::Color::Red);
		m_joinGameLabel->SetPosition(800, 300);
		m_joinGameRect = m_joinGameLabel->GetRect();

		m_optionsLabel = new sf::String("Options", LoadContent::GetInstance()->m_font, 50);
		m_optionsLabel->SetColor(sf::Color::Red);
		m_optionsLabel->SetPosition(800, 380);
		m_optionsRect = m_optionsLabel->GetRect();

		m_exitGameLabel = new sf::String("Exit Game", LoadContent::GetInstance()->m_font, 50);
		m_exitGameLabel->SetColor(sf::Color::Red);
		m_exitGameLabel->SetPosition(800, 460);
		m_exitGameRect = m_exitGameLabel->GetRect();

		m_Inited = true;
	}

	const sf::Input& Input = App.GetInput();

	if(m_joinGameRect.Contains(Input.GetMouseX(), Input.GetMouseY()) )
	{
		m_joinGameLabel->SetColor(sf::Color::Green);
	}
	else
	{
		m_joinGameLabel->SetColor(sf::Color::Red);
	}

	if(m_optionsRect.Contains(Input.GetMouseX(), Input.GetMouseY()) )
	{
		m_optionsLabel->SetColor(sf::Color::Green);
	}
	else
	{
		m_optionsLabel->SetColor(sf::Color::Red);
	}

	if(m_exitGameRect.Contains(Input.GetMouseX(), Input.GetMouseY()) )
	{
		m_exitGameLabel->SetColor(sf::Color::Green);
	}
	else
	{
		m_exitGameLabel->SetColor(sf::Color::Red);
	}




	App.Draw(*m_joinGameLabel);
	App.Draw(*m_optionsLabel);
	App.Draw(*m_exitGameLabel);
}