#include "stdafx.h"

#ifndef NETMNG_H
#define NETMNG_H
class NetworkManager
{
public:
	NetworkManager();

	// return instnace to this object
	static NetworkManager* GetInstance();

	// Send ping packet to server
	void SendPingPacket();

	// Send request for players list
	void SendRequestForPlayerList();

	// contain Server IP
	sf::IPAddress m_ServerIP;

	// contain Server Port
	unsigned short m_ServerPort;

	// main function to Recive all packets
	void RecivePackets();

	// Returns lasts know Server Ping
	float GetServerPing();

	// Change current server IP to NewServerIP
	void SetNewIPServer(std::string & NewServerIP);

	// Returns lst know Server Player's List
	int GetPlayerList();

	// Send data to server
	void SendData(sf::Packet & Packet);

private:
	sf::Clock m_clock;

	float m_Ping;

	unsigned short m_PortRec;

	sf::IPAddress m_IPRec;

	sf::Packet m_PacketRec, m_Packet;

	int m_PlayerList;

	// send ping packet back to server
	void ResendPing(sf::SocketUDP & SocketUDP, sf::Packet & Packet, sf::IPAddress & IPToSend, unsigned short PortToSend);

};
#endif