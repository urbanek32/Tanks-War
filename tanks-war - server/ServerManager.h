#include "stdafx.h"



#ifndef SERVERMNG_H
#define SERVERMNG_H
class ServerManager
{
public:
	ServerManager();

	ServerManager(sf::SocketUDP & SocketUDP, unsigned short ServerPort);

	void Run(sf::SocketUDP & SocketUDP);


private:
	bool m_Running;

	sf::Packet m_PacketRec;

	unsigned short m_PortRec;

	sf::IPAddress m_IPRec;

	sf::Uint8 m_PacketType;

	void ResendPing(sf::SocketUDP & SocketUDP, sf::Packet & Packet, sf::IPAddress & IPToSend, unsigned short PortToSend);

	void AddNewPlayer(sf::Packet & Packet, sf::IPAddress & IP, unsigned short Port);

	void SendPlayerList(sf::SocketUDP & SocketUDP, sf::IPAddress & IPToSend, unsigned short PortToSend);

	std::deque<class RemotePlayer*> m_Players;

	// just to unpack packet
	float m_PosX, m_PosY, m_Rotation, m_CannonRotation;

	int GetPlayerList();

};
#endif