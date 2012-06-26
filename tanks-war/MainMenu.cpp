#include "stdafx.h"


int MainMenu::Run(sf::RenderWindow& App)
{
	m_clock.Reset();

	while(Running)
	{
		App.Clear();
		App.Draw(background);
		const sf::Input& input = App.GetInput();

#pragma region Events

		while(App.GetEvent(m_Event))
		{
			if(m_Event.Type == sf::Event::Closed)
			{
				Running = false;
				return (-1);
			}
			if(m_Event.Type == sf::Event::KeyPressed && m_Event.Key.Code == sf::Key::Escape)
			{
				Running = false;
				return (-1);
			}

			// event for Press Join Game label
			if(m_Event.Type == sf::Event::MouseButtonReleased && m_Event.MouseButton.Button == sf::Mouse::Left && m_JoinRect.Contains(m_Event.MouseButton.X,m_Event.MouseButton.Y))
			{
				// TO DO: change screen to JoinGameScreen and let user select server
				return 3;
			}

			// event for Press Options label
			if(m_Event.Type == sf::Event::MouseButtonReleased && m_Event.MouseButton.Button == sf::Mouse::Left && m_OptionsRect.Contains(m_Event.MouseButton.X,m_Event.MouseButton.Y))
			{
				// TO DO: change screen to OptionsScreen and let user change options
				//Running = false;
				return 2; // returns Options enum
				
			}

			// event for Press Exit Game label
			if(m_Event.Type == sf::Event::MouseButtonReleased && m_Event.MouseButton.Button == sf::Mouse::Left && m_QuitRect.Contains(m_Event.MouseButton.X,m_Event.MouseButton.Y))
			{
				Running = false;
				return (-1);
			}

		}

		if(m_JoinRect.Contains(input.GetMouseX(),input.GetMouseY()))
			m_text_joingame.SetColor(sf::Color::Green);
		else
			m_text_joingame.SetColor(sf::Color::Red);

		if(m_OptionsRect.Contains(input.GetMouseX(),input.GetMouseY()))
			m_text_options.SetColor(sf::Color::Green);
		else
			m_text_options.SetColor(sf::Color::Red);

		if(m_QuitRect.Contains(input.GetMouseX(),input.GetMouseY()))
			m_text_exitgame.SetColor(sf::Color::Green);
		else
			m_text_exitgame.SetColor(sf::Color::Red);

#pragma endregion
#pragma region DEBUG INFO
std::ostringstream bufor;
sf::String tdebug;
tdebug.SetFont(LoadContent::GetInstance()->m_font);
tdebug.SetSize(20); tdebug.SetColor(sf::Color::Red); tdebug.SetPosition(0,0);
bufor <<"gameState= "<<GameManager::GetInstance()->_gameState;
tdebug.SetText(bufor.str());
App.Draw(tdebug);
#pragma endregion

		logo.SetPosition(App.GetWidth()/3,0);
		logo.SetScale(0.9f,0.9f);
		//logo.SetColor(sf::Color(logo.GetColor().r,logo.GetColor().g, logo.GetColor().b, 130));

		m_text_joingame.SetText("JOIN GAME");
		m_text_joingame.SetPosition(800,300);
		m_JoinRect = m_text_joingame.GetRect();

		m_text_options.SetText("OPTIONS");
		m_text_options.SetPosition(800,400);
		m_OptionsRect = m_text_options.GetRect();

		m_text_exitgame.SetText("EXIT");
		m_text_exitgame.SetPosition(800, 500);
		m_QuitRect = m_text_exitgame.GetRect();
		
		

		

		//if(m_clock.GetElapsedTime() < 2.5f)
			App.Draw(logo);
		//if(m_clock.GetElapsedTime() > 2.0f)
		//{
			App.Draw(m_text_joingame);
			App.Draw(m_text_options);
			App.Draw(m_text_exitgame);
		//}
		
		App.Display();
		sf::Sleep(0.01f);
	} // end of while(Running)

	//return (-1);
}

MainMenu::MainMenu()
{
	background.SetImage(LoadContent::GetInstance()->ImgMnr->Get_Image("CONTENT\\tlo-test.png"));
	logo.SetImage(LoadContent::GetInstance()->ImgMnr->Get_Image("CONTENT\\tankswar-logo.png"));

	m_text_joingame.SetFont(LoadContent::GetInstance()->m_font);
	m_text_joingame.SetSize(80);
	m_text_joingame.SetColor(sf::Color::Red);

	m_text_options.SetFont(LoadContent::GetInstance()->m_font);
	m_text_options.SetSize(80);
	m_text_options.SetColor(sf::Color::Red);

	m_text_exitgame.SetFont(LoadContent::GetInstance()->m_font);
	m_text_exitgame.SetSize(80);
	m_text_exitgame.SetColor(sf::Color::Red);

	Running = true;
}