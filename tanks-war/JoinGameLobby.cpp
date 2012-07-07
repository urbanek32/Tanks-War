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
			m_serverIPBox->HandleEvent(m_Event);

		} // end of events while loop

		m_serverIPBox->Show(App);

		App.Display();
		sf::Sleep(0.01f);
	} // end of while loop

	return (-1);
}

void JoinGameLobby::Init()
{
	//m_background.SetImage(gResMng.Get_Image("CONTENT//pokerface.png"));

	m_serverIP.SetText("127.0.0.1");

	m_serverIPBox = new TextBox(sf::Vector2f(100, 100), m_serverIP, sf::Color(255,0,0,255), 30.f);
	m_serverIPBox->SetLabel(sf::String("IP address: "), 30.f, sf::Color(255,100,0,255), 4.f);

	m_Inited = true;
}