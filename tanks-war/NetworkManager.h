#include "stdafx.h"

#ifndef NETMNG_H
#define NETMNG_H
class NetworkManager
{
public:
	NetworkManager();

	sf::SocketUDP m_SocketUDP;

	// return instnace to this object
	static NetworkManager* GetInstance();

	void SendPingPacket();

	sf::IPAddress m_ServerIP;

	unsigned short m_ServerPort;

	static std::string m_PlayerNick;

	void RecivePackets();

	float GetServerPing();

private:
	sf::Clock m_clock;

	float m_Ping;

	unsigned short m_PortRec;

	sf::IPAddress m_IPRec;

	sf::Packet m_PacketRec, m_Packet;

};
#endif