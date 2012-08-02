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
		App.Draw(m_Background);

		while(App.GetEvent(m_Event))
		{
			if(m_Event.Type == sf::Event::Closed)
			{
				m_Running = false;
				return (-1);
			}
			
			if(m_Event.Type == sf::Event::MouseButtonPressed && m_SinglePlayerRect.Contains(m_Event.MouseButton.X, m_Event.MouseButton.Y) )
			{
				// GO TO GAME
				return 4;
			}

			if(m_Event.Type == sf::Event::MouseButtonPressed && m_MultiPlayerRect.Contains(m_Event.MouseButton.X, m_Event.MouseButton.Y) )
			{
				// GO TO JOINLOBBY
				return 3;
			}

			if(m_Event.Type == sf::Event::MouseButtonPressed && m_OptionsRect.Contains(m_Event.MouseButton.X, m_Event.MouseButton.Y) )
			{
				// GO TO OPTIONS
				return 2;
			}

			if(m_Event.Type == sf::Event::MouseButtonPressed && m_ExitGameRect.Contains(m_Event.MouseButton.X, m_Event.MouseButton.Y) )
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
bufor << "BufforSize= " << gResMng.Get_MapSize();
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
		m_Background.SetImage(gResMng.Get_Image("CONTENT//tlo-test.png"));

		m_SinglePlayerLabel = new sf::String("Single player", LoadContent::GetInstance()->m_font, 50);
		m_SinglePlayerLabel->SetColor(sf::Color::Red);
		m_SinglePlayerLabel->SetPosition(800, 220);
		m_SinglePlayerRect = m_SinglePlayerLabel->GetRect();

		m_MultiPlayerLabel = new sf::String("Multi player", LoadContent::GetInstance()->m_font, 50);
		m_MultiPlayerLabel->SetColor(sf::Color::Red);
		m_MultiPlayerLabel->SetPosition(800, 300);
		m_MultiPlayerRect = m_MultiPlayerLabel->GetRect();

		m_OptionsLabel = new sf::String("Options", LoadContent::GetInstance()->m_font, 50);
		m_OptionsLabel->SetColor(sf::Color::Red);
		m_OptionsLabel->SetPosition(800, 380);
		m_OptionsRect = m_OptionsLabel->GetRect();

		m_ExitGameLabel = new sf::String("Exit Game", LoadContent::GetInstance()->m_font, 50);
		m_ExitGameLabel->SetColor(sf::Color::Red);
		m_ExitGameLabel->SetPosition(800, 460);
		m_ExitGameRect = m_ExitGameLabel->GetRect();

		m_Inited = true;
	}

	const sf::Input& Input = App.GetInput();

	if(m_SinglePlayerRect.Contains(Input.GetMouseX(), Input.GetMouseY()) )
	{
		m_SinglePlayerLabel->SetColor(sf::Color::Green);
	}
	else
	{
		m_SinglePlayerLabel->SetColor(sf::Color::Red);
	}

	if(m_MultiPlayerRect.Contains(Input.GetMouseX(), Input.GetMouseY()) )
	{
		m_MultiPlayerLabel->SetColor(sf::Color::Green);
	}
	else
	{
		m_MultiPlayerLabel->SetColor(sf::Color::Red);
	}

	if(m_OptionsRect.Contains(Input.GetMouseX(), Input.GetMouseY()) )
	{
		m_OptionsLabel->SetColor(sf::Color::Green);
	}
	else
	{
		m_OptionsLabel->SetColor(sf::Color::Red);
	}

	if(m_ExitGameRect.Contains(Input.GetMouseX(), Input.GetMouseY()) )
	{
		m_ExitGameLabel->SetColor(sf::Color::Green);
	}
	else
	{
		m_ExitGameLabel->SetColor(sf::Color::Red);
	}




	App.Draw(*m_SinglePlayerLabel);
	App.Draw(*m_MultiPlayerLabel);
	App.Draw(*m_OptionsLabel);
	App.Draw(*m_ExitGameLabel);
}