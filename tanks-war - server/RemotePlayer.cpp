#include "stdafx.h"

RemotePlayer::RemotePlayer()
{

}

RemotePlayer::RemotePlayer(sf::IPAddress IP, unsigned short Port, float PosX, float PosY, float Rotation, float CannonRotation)
{
	m_IP = IP;
	m_Port = Port;
	m_Pos.x = PosX;
	m_Pos.y = PosY;
	m_Rotation = Rotation;
	m_CannonRotation = CannonRotation;
}