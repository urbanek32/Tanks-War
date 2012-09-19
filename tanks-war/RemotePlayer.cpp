#include "stdafx.h"

RemotePlayer::RemotePlayer()
{

}

RemotePlayer::RemotePlayer(sf::IPAddress IP, unsigned short Port, std::string TankType, std::string CannonType, std::string PlayerNick, float PosX, float PosY, float Rotation, float CannonRotation)
{
	m_TankSprite.SetImage( gResMng.Get_Image(TankType) );
	m_CannonSprite.SetImage( gResMng.Get_Image(CannonType) );

	m_IP = IP;
	m_Port = Port;
	m_PlayerNick = PlayerNick;
	m_Pos.x = PosX;
	m_Pos.y = PosY;
	m_Rotation = Rotation;
	m_CannonRotation = CannonRotation;

	m_TankSprite.SetCenter( m_TankSprite.GetSize().x / 2.f, m_TankSprite.GetSize().y / 2.f);
	m_CannonSprite.SetCenter( m_CannonSprite.GetSize().x / 3.5f, m_CannonSprite.GetSize().y / 2.f);

	m_TankSprite.SetPosition(PosX, PosY);
	m_CannonSprite.SetPosition(PosX, PosY);

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

sf::IPAddress & RemotePlayer::GetIP()
{
	return m_IP;
}

unsigned short & RemotePlayer::GetPort()
{
	return m_Port;
}

void RemotePlayer::SetPosition(float &X, float &Y)
{
	m_Pos.x = X;
	m_Pos.y = Y;

	m_TankSprite.SetPosition( X , Y );
}

void RemotePlayer::SetRotation(float & Rotation)
{
	m_Rotation = Rotation;
	m_TankSprite.SetRotation( Rotation );
}

void RemotePlayer::SetCannonRotation(float & CannonRotation)
{
	m_CannonRotation = CannonRotation;
	m_CannonSprite.SetRotation( -CannonRotation);
}

void RemotePlayer::SetNick(std::string & NewNick)
{
	m_PlayerNick = NewNick;
}

void RemotePlayer::Draw(sf::RenderWindow & App)
{
	App.Draw(m_TankSprite);
	App.Draw(m_CannonSprite);
}

void RemotePlayer::Update(float & PosX, float & PosY, float & Rotation, float & CannonRotation)
{
	SetPosition(PosX, PosY);
	SetRotation(Rotation);
	SetCannonRotation(CannonRotation);

	m_CannonSprite.SetPosition( GetPosition().x, GetPosition().y );
}