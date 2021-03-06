#include "stdafx.h"

Bullet::Bullet() {}
Bullet::Bullet(sf::RenderWindow & App, sf::Vector2f StartPosition, float Rotation, int BulletDamage)
{
	m_V = 700.f;
	m_Lifetime = 0;
	m_Damage = BulletDamage;

	this->m_StartPos = StartPosition;
	this->m_ToDelete = false;
	this->m_Rotation = Rotation;

	m_MousePos = App.ConvertCoords(App.GetInput().GetMouseX(), App.GetInput().GetMouseY());

	m_BulletDis.x = m_StartPos.x - m_MousePos.x;
	m_BulletDis.y = m_StartPos.y - m_MousePos.y;

	DLen = sqrt(m_BulletDis.x * m_BulletDis.x + m_BulletDis.y * m_BulletDis.y);
	m_BulletDis.x /= DLen;
	m_BulletDis.y /= DLen;

	m_BulletDis.x *= m_V;
	m_BulletDis.y *= m_V;

	m_Bullet.SetImage(gResMng.Get_Image("CONTENT//bullet.png"));
	m_Bullet.SetScale(0.8f,0.8f);
	m_Bullet.SetCenter(m_Bullet.GetSize().x/2, m_Bullet.GetSize().y/2);
	m_Bullet.SetPosition(m_StartPos.x , m_StartPos.y );
	m_Bullet.SetRotation(-m_Rotation);

}

void Bullet::Update(sf::RenderWindow & App)
{

	if(m_Lifetime < 200 && !m_ToDelete)
	{
		m_Bullet.Move(-m_BulletDis * App.GetFrameTime() );
		App.Draw(m_Bullet);
		m_Lifetime++;
	}
	else
	{
		m_ToDelete = true;
	}

}

bool Bullet::toDelete()
{
	return m_ToDelete;
}

sf::Sprite & Bullet::GetSprite()
{
	return m_Bullet;
}

void Bullet::SetToDelete()
{
	m_ToDelete = true;
}

int Bullet::GetBulletDamage()
{
	return m_Damage;
}