#include "stdafx.h"



EnemyBullet::EnemyBullet() {}
EnemyBullet::EnemyBullet(sf::Vector2f StartPosition, sf::Vector2f TargetPosition, float Rotation, int BulletDamage)
{
	this->m_V = 700.f;
	this->m_Lifetime = 0;
	this->m_Damage = BulletDamage;

	this->m_StartPos = StartPosition;
	this->m_ToDelete = false;
	this->m_Rotation = Rotation;
	
	this->m_TargetXY = TargetPosition;

	this->m_BulletDis.x = m_StartPos.x - m_TargetXY.x;
	this->m_BulletDis.y = m_StartPos.y - m_TargetXY.y;

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
