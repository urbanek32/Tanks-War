#include "stdafx.h"

#ifndef REPLAYER_H
#define REPLAYER_H
class RemotePlayer
{
public:
	RemotePlayer();

	RemotePlayer(sf::IPAddress IP, unsigned short Port, std::string PlayerNick = "Anon", std::string TankType = "TankMedium", std::string CannonType = "CannonMedium", float PosX = 0.0f, float PosY = 0.0f, float Rotation = 0.0f, float CannonRotation = 0.0f);

	sf::IPAddress & GetIP();

	unsigned short & GetPort();

	sf::Vector2f & GetPosition();

	float & GetRotation();

	float & GetCannonRotation();

	std::string & GetPlayerNick();

	void SetPosition(float & X, float & Y);

	void SetRotation(float & Rotation);

	void SetCannonRotation(float & CannonRotation);

	void SetNick(std::string & NewNick);

	std::string & GetTankType();

	std::string & GetCannonType();

	void SetTankType(std::string & TankType);

	void SetCannonType(std::string & CannonType);

private:
	sf::Vector2f m_Pos;

	float m_Rotation;

	float m_CannonRotation;

	std::string m_PlayerNick, m_TankType, m_CannonType;

	sf::IPAddress m_IP;

	unsigned short m_Port;

};
#endif