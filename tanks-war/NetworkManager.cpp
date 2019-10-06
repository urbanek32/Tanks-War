#include "stdafx.h"

#ifdef CPP_0x11
NetworkManager* nm_ptr=nullptr;
#else
NetworkManager* nm_ptr=NULL;
#endif

#define GLGI JoinGameLobby::GetInstance()
#define GMGI GameManager::GetInstance()

NetworkManager* NetworkManager::GetInstance()
{
	if(nm_ptr==NULL) nm_ptr = new NetworkManager();
	return nm_ptr;
}

NetworkManager::NetworkManager()
{
	m_ServerIP = globals["ServerIP"];
	m_ServerPort = 6666;

	GMGI->m_SocketUDP.SetBlocking(false);
	m_Ping = 0;
	m_PlayerList = 0;
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
		case sf::Uint8(1) :	// ping packet
			{
				m_Ping = std::ceil(m_clock.GetElapsedTime() / 1000.f);
				break;
			}
		case sf::Uint8(2) : // new player's packet
			{
				
				break;
			}
		case sf::Uint8(3) : // player's list
			{
				m_PacketRec >> m_PlayerList;
				break;
			}
		case sf::Uint8(4) : // New data arrived
			{
				
				break;
			}
		case sf::Uint8(5) : // Ping from server
			{
				ResendPing(GMGI->m_SocketUDP, m_PacketRec, m_IPRec, m_PortRec);
				break;
			}

		} // end switch
	} // end if


	
}

float NetworkManager::GetServerPing()
{
	return m_Ping;
}

void NetworkManager::SetNewIPServer(std::string & NewServer)
{
	m_ServerIP = NewServer;
}

int NetworkManager::GetPlayerList()
{
	return m_PlayerList;
}

void NetworkManager::SendRequestForPlayerList()
{
	m_Packet.Clear();
	m_Packet << sf::Uint8(3);

	GMGI->m_SocketUDP.Send(m_Packet, m_ServerIP, m_ServerPort);
	
}

void NetworkManager::ResendPing(sf::SocketUDP & SocketUDP, sf::Packet & Packet, sf::IPAddress & IPToSend, unsigned short PortToSend)
{
	SocketUDP.Send(Packet, IPToSend, PortToSend);
}

void NetworkManager::SendData(sf::Packet & Packet)
{
	GMGI->m_SocketUDP.Send(Packet, m_ServerIP, m_ServerPort);
}