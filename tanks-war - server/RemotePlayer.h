#include "stdafx.h"

#ifndef REPLAYER_H
#define REPLAYER_H
class RemotePlayer
{
public:
	RemotePlayer();

	RemotePlayer(sf::IPAddress IP, unsigned short Port, float PosX, float PosY, float Rotation, float CannonRotation);

private:
	sf::Vector2f m_Pos;

	float m_Rotation;

	float m_CannonRotation;

	sf::IPAddress m_IP;

	unsigned short m_Port;

};
#endif