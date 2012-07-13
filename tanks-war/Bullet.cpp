#include "stdafx.h"


Bullet::Bullet(sf::RenderWindow & App, sf::Vector2f StartPosition, float Rotation)
{
	m_V = 10.f;
	m_lifetime = 0;

	this->m_StartPos = StartPosition;
	this->m_alive = true;
	this->m_rotation = Rotation;

	this->m_MousePos = App.ConvertCoords(App.GetInput().GetMouseX(), App.GetInput().GetMouseY());

	this->m_BulletDis.x = m_StartPos.x - m_MousePos.x;
	this->m_BulletDis.y = m_StartPos.y - m_MousePos.y;

	float _DLen = sqrt(m_BulletDis.x * m_BulletDis.x + m_BulletDis.y * m_BulletDis.y);
	m_BulletDis.x /= _DLen;
	m_BulletDis.y /= _DLen;

	m_BulletDis.x *= m_V;
	m_BulletDis.y *= m_V;

	m_bullet.SetImage(gResMng.Get_Image("CONTENT//bullet.png"));
	m_bullet.SetScale(0.8f,0.8f);
	m_bullet.SetCenter(m_bullet.GetSize().x/2, m_bullet.GetSize().y/2);
	m_bullet.SetPosition(m_StartPos.x + (-m_BulletDis.x) * 2.8f, m_StartPos.y + (-m_BulletDis.y) * 2.8f);
	m_bullet.SetRotation(-m_rotation);

}

void Bullet::Update(sf::RenderWindow & App)
{

	if(m_lifetime < 200)
	{
		m_bullet.Move(-m_BulletDis);
		App.Draw(m_bullet);
		m_lifetime++;
	}
	else
	{
		m_alive = false;
	}

}

bool Bullet::isAlive()
{
	return m_alive;
}