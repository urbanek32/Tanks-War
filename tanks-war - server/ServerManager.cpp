#include "stdafx.h"

ServerManager::ServerManager()
{

}

ServerManager::ServerManager(sf::SocketUDP & SocketUDP, unsigned short ServerPort)
{
	SocketUDP.Bind(ServerPort);

	m_Running = true;

	std::cout<<"Server is running on port: "<<SocketUDP.GetPort()<<std::endl;
}

void ServerManager::Run(sf::SocketUDP & SocketUDP)
{
	while(m_Running)
	{
		SocketUDP.Receive(m_PacketRec, m_IPRec, m_PortRec);

		(m_PacketRec >> m_PacketType);

		switch(m_PacketType)
		{
		case sf::Uint8(1):	// PING packet
			{
				ResendPing(SocketUDP, m_PacketRec, m_IPRec, m_PortRec);
				std::cout<<" PING sent\n";
				break;
			}
		case '2' :	// New Player Packet
			{
				AddNewPlayer(m_PacketRec, m_IPRec, m_PortRec);
				break;
			}
		case '3' :	// Player list packet
			{
				SendPlayerList(SocketUDP, m_IPRec, m_PortRec);
				break;
			}

		}

	}
}

void ServerManager::ResendPing(sf::SocketUDP & SocketUDP, sf::Packet & Packet, sf::IPAddress & IPToSend, unsigned short PortToSend)
{
	SocketUDP.Send(Packet, IPToSend, PortToSend);
}

void ServerManager::AddNewPlayer(sf::Packet & Packet, sf::IPAddress & IP, unsigned short Port)
{
	Packet >> m_PosX >> m_PosY >> m_Rotation >> m_CannonRotation;
	m_Players.push_back(new RemotePlayer(IP, Port, m_PosX, m_PosY, m_Rotation, m_CannonRotation));
}

void ServerManager::SendPlayerList(sf::SocketUDP & SocketUDP, sf::IPAddress & IPToSend, unsigned short PortToSend)
{
	sf::Packet *_packet = new sf::Packet();
	sf::Uint8 _type = '3';

	*_packet << _type << GetPlayerList();

	SocketUDP.Send(*_packet, IPToSend, PortToSend);

	delete _packet;
}

int ServerManager::GetPlayerList()
{
	return m_Players.size();
}