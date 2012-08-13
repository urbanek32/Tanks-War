#include "stdafx.h"

#ifndef REPLAYER_H
#define REPLAYER_H
class RemotePlayer
{
public:
	RemotePlayer();

	RemotePlayer(sf::IPAddress IP, unsigned short Port, std::string TankType, std::string CannonType, std::string PlayerNick = "Anon", float PosX = 0.0f, float PosY = 0.0f, float Rotation = 0.0f, float CannonRotation = 0.0f);

	sf::Vector2f & GetPosition();

	float & GetRotation();

	sf::IPAddress & GetIP();

	unsigned short & GetPort();

	float & GetCannonRotation();

	std::string & GetPlayerNick();

	void SetPosition(float & X, float & Y);

	void SetRotation(float & Rotation);

	void SetCannonRotation(float & CannonRotation);

	void SetNick(std::string & NewNick);

	void Draw(sf::RenderWindow & App);

	void Update(float & PosX, float & PosY, float & Rotation, float & CannonRotation);

private:
	sf::Sprite m_TankSprite, m_CannonSprite;

	sf::Vector2f m_Pos;

	float m_Rotation;

	float m_CannonRotation;

	std::string m_PlayerNick;

	sf::IPAddress m_IP;

	unsigned short m_Port;

};
#endif