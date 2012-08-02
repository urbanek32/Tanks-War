#include "stdafx.h"

#ifdef CPP_0x11
NetworkManager* ptr=nullptr;
#else
NetworkManager* ptr=NULL;
#endif

#define GLGI JoinGameLobby::GetInstance()
#define GMGI GameManager::GetInstance()

NetworkManager* NetworkManager::GetInstance()
{
	if(ptr==NULL) ptr = new NetworkManager();
	return ptr;
}

NetworkManager::NetworkManager()
{
	m_ServerIP = GLGI->GetServerIP();
	m_ServerPort = 6666;

	GMGI->m_SocketUDP.SetBlocking(false);
	m_Ping = 0;
}

void NetworkManager::SendPingPacket()
{
	m_Packet.Clear();
	m_Packet << sf::Uint8(1);

	m_clock.Reset();
	GMGI->m_SocketUDP.Send(m_Packet, m_ServerIP, m_ServerPort);


}

void NetworkManager::RecivePackets()
{

	GMGI->m_SocketUDP.Receive(m_PacketRec, m_IPRec, m_PortRec);

	if(m_PortRec == m_ServerPort && m_IPRec == m_ServerIP)
	{
		sf::Uint8 _type;
		m_PacketRec >> _type;

		switch(_type)
		{
		case sf::Uint8(1) :
			{
				m_Ping = std::ceil(m_clock.GetElapsedTime() / 1000.f);
				break;
			}


		}
	}


	
}

float NetworkManager::GetServerPing()
{
	return m_Ping;
}