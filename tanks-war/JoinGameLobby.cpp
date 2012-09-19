#include "stdafx.h"

#define GMGI GameManager::GetInstance()


#ifdef CPP_0x11
JoinGameLobby* ptr=nullptr;
#else
JoinGameLobby* ptr=NULL;
#endif

JoinGameLobby* JoinGameLobby::GetInstance()
{
	if(ptr==NULL) ptr = new JoinGameLobby();
	return ptr;
}

JoinGameLobby::JoinGameLobby()
{
	
	m_Inited = false;
	m_running = true;
	
	m_ServerPing = 0;
	m_PlayerCount = 0;
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
			// BACK TO MAIN MENU
			if(m_Event.Type == sf::Event::KeyPressed && m_Event.Key.Code == sf::Key::Escape)
			{
				m_running = false;
				return 1;
			}
			// CHECK PLAYERS ON SERVER
			if(m_Event.Type == sf::Event::KeyPressed && m_Event.Key.Code == sf::Key::F1)
			{
				SendPlayersRequest();
			}
			// JOIN TO GAME
			if(m_Event.Type == sf::Event::KeyPressed && m_Event.Key.Code == sf::Key::F5)
			{
				SendNewPlayerJoin();
			}

			m_serverIPBox->HandleEvent(m_Event);

		} // end of events while loop

#pragma region debuginfo
std::ostringstream bufor;
sf::String tdebug;
tdebug.SetFont(sf::Font::GetDefaultFont());
tdebug.SetSize(20);
tdebug.SetColor(sf::Color(255,0,0,255));
bufor << "Port= " << GMGI->m_SocketUDP.GetPort() << "\nPing= " << m_ServerPing;
bufor << "\n" << "Players Count= " << m_PlayerCount;
tdebug.SetText(bufor.str());
App.Draw(tdebug);	
#pragma endregion

		// if server accept my connection. Go to OnlineGame
		if(m_StartGame)
			return 5;


		RecivePackets();

		// draw textbox for server ip
		m_serverIPBox->Show(App);

		// check ping every 5sec
		if(m_pingclock.GetElapsedTime() >= 5.f)
		{
			SendPingRequest();
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
	m_StartGame = false;

	m_serverIPBox = new TextBox(sf::Vector2f(100, 100), sf::String("127.0.0.1"), sf::Color(255,0,0,255), "ServerIP", 30.f);
	m_serverIPBox->SetLabel(sf::String("IP address: "), 30.f, sf::Color(255,100,0,255), 4.f);

	while( GMGI->m_SocketUDP.GetPort() == 0)
	{
		GMGI->m_SocketUDP.Bind(sf::Randomizer::Random(1500, 65000));
	}

	m_Inited = true;
}

void JoinGameLobby::SendPingRequest()
{
	m_Packet.Clear();
	m_Packet << sf::Uint8(1);
	GMGI->m_SocketUDP.Send(m_Packet, globals["ServerIP"], 6666);
}

void JoinGameLobby::SendPlayersRequest()
{
	m_Packet.Clear();
	m_Packet << sf::Uint8(3);
	GMGI->m_SocketUDP.Send(m_Packet, globals["ServerIP"], 6666);
}

void JoinGameLobby::SendNewPlayerJoin()
{
	m_Packet.Clear();
	m_Packet << sf::Uint8(2) << globals["PlayerNick"] << globals["TankType"] << globals["CannonType"];
	GMGI->m_SocketUDP.Send(m_Packet, globals["ServerIP"], 6666);
}

void JoinGameLobby::RecivePackets()
{
	m_Packet.Clear();

	GMGI->m_SocketUDP.Receive(m_Packet, m_RecIP, m_RecPort);
	m_Packet >> m_Type;

	switch(m_Type)
	{
	case sf::Uint8(1) : // ping request backed from server
		{
			m_ServerPing = (unsigned short)( std::ceil(m_pingclock2.GetElapsedTime() / 1000.f) );
			break;
		}

	case sf::Uint8(2) : // server accepted my join to server. GO TO GAME
		{
			m_StartGame = true;
			break;
		}

	case sf::Uint8(3) : // server resent numer of players on server
		{
			m_Packet >> m_PlayerCount;
			break;
		}
	}

}