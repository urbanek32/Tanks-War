#include "stdafx.h"

#define GMGI GameManager::GetInstance()
#define NMGI NetworkManager::GetInstance()


#ifdef CPP_0x11
JoinGameLobby* ptr=nullptr;
#else
JoinGameLobby* ptr=NULL;
#endif

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
		App.Draw(m_Background);

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

std::ostringstream bufor;
sf::String tdebug;
tdebug.SetFont(sf::Font::GetDefaultFont());
tdebug.SetSize(20);
tdebug.SetColor(sf::Color(255,0,0,255));
bufor << "Port= " << GMGI->m_SocketUDP.GetPort() << "\n" << NMGI->GetServerPing();
tdebug.SetText(bufor.str());
App.Draw(tdebug);	

		NMGI->RecivePackets();

		m_serverIPBox->Show(App);

		if(m_pingclock.GetElapsedTime() > 5.f)
		{
			NMGI->SendPingPacket();
			m_pingclock.Reset();
		}

		App.Display();
		sf::Sleep(0.01f);
	} // end of while loop

	return (-1);
}

void JoinGameLobby::Init()
{
	m_Background.SetImage(gResMng.Get_Image("CONTENT//tlo-test.png"));

	m_serverIP.SetText("127.0.0.1");

	m_serverIPBox = new TextBox(sf::Vector2f(100, 100), m_serverIP, sf::Color(255,0,0,255), 30.f);
	m_serverIPBox->SetLabel(sf::String("IP address: "), 30.f, sf::Color(255,100,0,255), 4.f);

	while( GMGI->m_SocketUDP.GetPort() == 0)
	{
		GMGI->m_SocketUDP.Bind(sf::Randomizer::Random(1500, 65000));
	}

	m_Inited = true;
}

std::string JoinGameLobby::GetServerIP()
{
	return m_serverIP.GetText();
}

JoinGameLobby* JoinGameLobby::GetInstance()
{
	if(ptr==NULL) ptr = new JoinGameLobby();
	return ptr;
}