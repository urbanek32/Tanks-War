#include "stdafx.h"

#ifndef JOINLOBBY_H
#define JOINLOBBY_H
class JoinGameLobby : public cScreen
{
public:
	JoinGameLobby();
	// Main function to Draw and Update this class
	virtual int Run(sf::RenderWindow & App);

	// Returns instance to this class
	static JoinGameLobby* GetInstance();


private:
	sf::Event m_Event;
	bool m_running;

	sf::Sprite m_Background;

	class TextBox *m_serverIPBox;

	sf::String m_serverPing;

	void Init();
	bool m_Inited;

	bool m_StartGame;

	sf::Packet m_Packet;
	sf::IPAddress m_RecIP;
	unsigned short m_RecPort;
	sf::Uint8 m_Type;

	void RecivePackets();

	void SendPingRequest();

	void SendPlayersRequest();

	void SendNewPlayerJoin();

	sf::Clock m_pingclock, m_pingclock2;

	unsigned short m_ServerPing;
	int m_PlayerCount;
};
#endif