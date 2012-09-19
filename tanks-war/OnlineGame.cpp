#include "stdafx.h"

#define GMGI GameManager::GetInstance()


OnlineGame::OnlineGame()
{
	m_Running = true;
	m_Inited = false;
}

void OnlineGame::m_Init()
{
	m_Player = new Player();
	m_View = new sf::View(sf::FloatRect(0,0, 1300, 700) );

	m_Inited = true;

	bylgracz=0;
	bylydane=0;

}

int OnlineGame::Run(sf::RenderWindow & App)
{
	if( !m_Inited )
		m_Init();

	while(m_Running)
	{
		App.Clear();

		if(m_FrameClock.GetElapsedTime() >= 0.5f)
		{
			m_FrameRate = 1.f / App.GetFrameTime();	
			m_FrameClock.Reset();
		}

		while(App.GetEvent(m_Event))
		{
			if(m_Event.Type == sf::Event::Closed)
			{
				// CLOSE THE APP
				m_Running = false;
				return (-1);
			}

			if(m_Event.Type == sf::Event::KeyPressed && m_Event.Key.Code == sf::Key::Escape)
			{
				// BACK TO MAINMENU
				//m_Running = false;
				SendPlayerLeave();
				return 1;
			}


		} // end of events loop

#pragma region debuginfo
std::ostringstream bufor;
sf::String tdebug;
tdebug.SetFont(sf::Font::GetDefaultFont());
tdebug.SetSize(20);
tdebug.SetColor(sf::Color(255,0,0,255));
bufor << "FPS = " << m_FrameRate;
bufor << "\nByl nowy gracz = " << bylgracz;
bufor << "\nDane otrzymane = " << bylydane;
tdebug.SetText(bufor.str());
App.Draw(tdebug);	
#pragma endregion


		RecivePackets();

		// PUT HERE: game objects etc
		App.SetView(*m_View);

		DrawAllPlayers(App);
		ManageLocalPlayer(App);



		// PUT HERE: static objects like interface etc
		App.SetView(App.GetDefaultView());


		App.Display();
	} // end of main while

	return (-1);
}

void OnlineGame::DrawAllPlayers(sf::RenderWindow & App)
{
	for(std::deque<class RemotePlayer*>::const_iterator it = m_RemotePlayers.begin(); it != m_RemotePlayers.end(); ++it)
	{
		(*it)->Draw(App);
	}
}

void OnlineGame::RecivePackets()
{
	m_Packet.Clear();

	GMGI->m_SocketUDP.Receive(m_Packet, m_RecIP, m_RecPort);
	m_Packet >> m_Type;

	switch(m_Type)
	{
	case sf::Uint8(1) : // server sent ping request
		{
			// Send ping back to server
			break;
		}

	case sf::Uint8(2) : // new player join to game
		{
			// Add new player
			AddNewPlayer(m_Packet);
			bylgracz++;
			break;
		}

	case sf::Uint8(3) : // server resent numer of players on server
		{
			// Data with player count (Draw/Display/Update etc)
			break;
		}
	case sf::Uint8(4) : // new data income from server
		{
			UpdateData(m_Packet);
			bylydane++;
			break;
		}
	case sf::Uint8(5) : // players leave
		{
			// Delete player from list
			DeletePlayer(m_Packet);
			break;
		}
	} // end switch


}

void OnlineGame::DeletePlayer(sf::Packet & Packet)
{
	Packet >> _ip >> m_Port;
	m_IP = _ip;

	for(std::deque<class RemotePlayer*>::const_iterator it = m_RemotePlayers.begin(); it != m_RemotePlayers.end(); )
	{
		if( (*it)->GetIP() == m_IP && (*it)->GetPort() == m_Port )
		{
			delete (*it);
			it = m_RemotePlayers.erase(it);
			break;
		}
		else
		{
			++it;
		}
	}
}

void OnlineGame::UpdateData(sf::Packet & Packet)
{
	Packet >> _ip >> m_Port >> _PosX >> _PosY >> _Rotation >> _CannonRotation;
	m_IP = _ip;

	for(std::deque<class RemotePlayer*>::const_iterator it = m_RemotePlayers.begin(); it != m_RemotePlayers.end(); )
	{
		if( (*it)->GetIP() == m_IP && (*it)->GetPort() == m_Port )
		{
			(*it)->Update(_PosX, _PosY, _Rotation, _CannonRotation);
			break;
		}
		else
		{
			++it;
		}
	}
}

void OnlineGame::AddNewPlayer(sf::Packet & Packet)
{
	Packet >> _ip >> m_Port >> _playernick >> _tanktype >> _cannontype;
	m_IP = _ip;

	m_RemotePlayers.push_back( new RemotePlayer( m_IP, m_Port, _tanktype, _cannontype, _playernick) );

}

void OnlineGame::ManageLocalPlayer(sf::RenderWindow & App)
{
	m_Player->Update(App);

	if( m_DataClock.GetElapsedTime()  >= 0.04f )
	{
		SendData( globals["PlayerNick"], m_Player->GetPlayerPosition().x, m_Player->GetPlayerPosition().y, m_Player->GetPlayerRotation(), m_Player->GetCannonRotation() );
		m_DataClock.Reset();
	}

	m_View->SetCenter( m_Player->GetPlayerPosition() );
}

void OnlineGame::SendData(std::string & PlayerNick, float & PosX, float & PosY, float Rotation, float & CannonRotation)
{
	m_Packet.Clear();

	m_Packet << sf::Uint8(4) << PlayerNick << PosX << PosY << Rotation << CannonRotation;
	GMGI->m_SocketUDP.Send(m_Packet, globals["ServerIP"], 6666);
}

void OnlineGame::SendPlayerLeave()
{
	m_Packet.Clear();
	m_Packet << sf::Uint8(5);

	GMGI->m_SocketUDP.Send(m_Packet, globals["ServerIP"], 6666);

}