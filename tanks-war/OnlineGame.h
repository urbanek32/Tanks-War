#include "stdafx.h"

#ifndef ONLINEGAME_H
#define ONLINEGAME_H
class OnlineGame : public cScreen
{
public:
	OnlineGame();

	virtual int Run(sf::RenderWindow & App);

private:
	bool m_Inited, m_Running;
	void m_Init();

	sf::Event m_Event;

	sf::View *m_View;

	std::deque<class RemotePlayer*> m_RemotePlayers;

	sf::Clock m_FrameClock, m_DataClock;

	float m_FrameRate;

	class Player *m_Player;

	sf::Packet m_Packet;
	sf::IPAddress m_RecIP, m_IP;
	unsigned short m_RecPort, m_Port;
	sf::Uint8 m_Type;
	std::string _ip, _tanktype, _cannontype, _playernick;
	float _PosX, _PosY, _Rotation, _CannonRotation;

	void RecivePackets();

	void SendData(float & PosX, float & PosY, float  Rotation, float & CannonRotation);

	void UpdateData(sf::Packet & Packet);

	void SendPlayerLeave();

	void DrawAllPlayers(sf::RenderWindow & App);

	void DeletePlayer(sf::Packet & Packet);

	void AddNewPlayer(sf::Packet & Packet);

	void ManageLocalPlayer(sf::RenderWindow & App);
};
#endif