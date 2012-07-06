#include "stdafx.h"

JoinGameLobby::JoinGameLobby()
{
	
	m_Inited = false;
	m_running = true;
	
}

int JoinGameLobby::Run(sf::RenderWindow & App)
{
	m_running = true;

	if(!m_Inited)
		Init();

	while(m_running)
	{
		App.Clear();
		App.Draw(m_background);

		while(App.GetEvent(m_Event))
		{
			if(m_Event.Type == sf::Event::Closed)
			{
				m_running = false;
				return (-1);
			}

			if(m_Event.Type == sf::Event::KeyPressed && m_Event.Key.Code == sf::Key::Escape)
			{
				m_running = false;
				return 1;
			}
			// GO TO GAME
			if(m_Event.Type == sf::Event::KeyPressed && m_Event.Key.Code == sf::Key::Return)
			{
				m_running = false;
				return 4;
			}

		} // end of events while loop


		App.Display();
		sf::Sleep(0.01f);
	} // end of while loop

	return (-1);
}

void JoinGameLobby::Init()
{
	m_background.SetImage(gResMng.Get_Image("CONTENT//pokerface.png"));
	m_Inited = true;
}