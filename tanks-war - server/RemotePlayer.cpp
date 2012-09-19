#include "stdafx.h"

RemotePlayer::RemotePlayer()
{

}

RemotePlayer::RemotePlayer(sf::IPAddress IP, unsigned short Port, std::string PlayerNick, std::string TankType, std::string CannonType, float PosX, float PosY, float Rotation, float CannonRotation)
{
	m_IP = IP;
	m_Port = Port;
	m_PlayerNick = PlayerNick;
	m_TankType = TankType;
	m_CannonType = CannonType;
	m_Pos.x = PosX;
	m_Pos.y = PosY;
	m_Rotation = Rotation;
	m_CannonRotation = CannonRotation;
}

sf::IPAddress & RemotePlayer::GetIP()
{
	return m_IP;
}

unsigned short & RemotePlayer::GetPort()
{
	return m_Port;
}

sf::Vector2f & RemotePlayer::GetPosition()
{
	return m_Pos;
}

float & RemotePlayer::GetRotation()
{
	return m_Rotation;
}

float & RemotePlayer::GetCannonRotation()
{
	return m_CannonRotation;
}

std::string & RemotePlayer::GetPlayerNick()
{
	return m_PlayerNick;
}

void RemotePlayer::SetPosition(float &X, float &Y)
{
	m_Pos.x = X;
	m_Pos.y = Y;
}

void RemotePlayer::SetRotation(float & Rotation)
{
	m_Rotation = Rotation;
}

void RemotePlayer::SetCannonRotation(float & CannonRotation)
{
	m_CannonRotation = CannonRotation;
}

void RemotePlayer::SetNick(std::string & NewNick)
{
	m_PlayerNick = NewNick;
}

void RemotePlayer::SetTankType(std::string & TankType)
{
	m_TankType = TankType;
}

void RemotePlayer::SetCannonType(std::string & CannonType)
{
	m_CannonType = CannonType;
}

std::string & RemotePlayer::GetTankType()
{
	return m_TankType;
}

std::string & RemotePlayer::GetCannonType()
{
	return m_CannonType;
}