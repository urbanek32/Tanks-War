#include "stdafx.h"


static const double M_PI=3.14159265358979323846f;


EnemyAI::EnemyAI(sf::Vector2f StartPosition, float Speed, float Range, int HealthPoints)
{
	m_Position = StartPosition;
	m_Speed = Speed;
	m_range = Range;
	m_HP = HealthPoints;
	m_ToDelete = false;

	m_enemy.SetImage(gResMng.Get_Image("CONTENT//tank1.png"));
	m_enemy.SetCenter(m_enemy.GetSize().x/2, m_enemy.GetSize().y/2);
	m_enemy.SetPosition(m_Position);

	m_enemyCannon.SetImage(gResMng.Get_Image("CONTENT//cannon1.png"));
	m_enemyCannon.SetCenter(m_enemyCannon.GetSize().x /2, m_enemyCannon.GetSize().y /2);

	m_shape = sf::Shape::Circle(m_Position, m_range, sf::Color(0,0,0,0), 2.f, sf::Color(255,0,0,255));

	m_ReloadTime = 1.f;
}

void EnemyAI::Update(sf::RenderWindow & App, sf::Vector2f kTargetXY)
{
	if( isAlive() )
	{
		m_Position = m_enemy.GetPosition();
		m_enemyCannon.SetPosition(m_Position);
		UpdateBullets(App);

		_d = sqrt( (kTargetXY.x - m_enemy.GetPosition().x) * (kTargetXY.x - m_enemy.GetPosition().x) + (kTargetXY.y - m_enemy.GetPosition().y) * (kTargetXY.y - m_enemy.GetPosition().y) );

		// jak jestem w zasiêgu to mnie goñ i zmieñ kolor
		if(_d <= m_range && _d >= 10.f)
		{
			ChooseTarget(kTargetXY);
			Shoot(App);
			m_enemy.Move(-m_enemyDis);
			m_shape = sf::Shape::Circle(m_enemy.GetPosition(), m_range, sf::Color(255,0,0,75), 2.f, sf::Color(255,0,0,255));
		
		}
		else
		// jak NIE jestem w zasiêgu to stój i zmieñ kolor na domyœlny
		{
			m_shape = sf::Shape::Circle(m_enemy.GetPosition(), m_range, sf::Color(0,0,0,0), 2.f, sf::Color(255,0,0,255));
		}



	
		App.Draw(m_enemy);
		App.Draw(m_enemyCannon);
		App.Draw(m_shape);

#pragma region DEBUG INFO
std::ostringstream bufor;
sf::String tdebug;
tdebug.SetFont(LoadContent::GetInstance()->m_font2);
tdebug.SetSize(20); tdebug.SetColor(sf::Color::Red);
tdebug.SetPosition(m_enemy.GetPosition());
bufor << "Target = " << m_randomTarget.x <<" " << m_randomTarget.y << "\nHP= " << GetEnemyHP();
tdebug.SetText(bufor.str());
App.Draw(tdebug);		
#pragma endregion	

	} // end if isAlive
}

void EnemyAI::ChooseTarget(sf::Vector2f TargetXY)
{
	m_randomTarget = TargetXY;

	if(m_Clock2.GetElapsedTime() >= 0.25f)
	{
		m_enemyDis.x = m_Position.x - m_randomTarget.x;
		m_enemyDis.y = m_Position.y - m_randomTarget.y;

		_DLen = sqrt(m_enemyDis.x * m_enemyDis.x + m_enemyDis.y * m_enemyDis.y);
		m_enemyDis.x /= _DLen;
		m_enemyDis.y /= _DLen;

		m_enemyDis.x *= m_Speed;
		m_enemyDis.y *= m_Speed;

		m_Clock2.Reset();
	}

	m_xH = m_Position.x - m_randomTarget.x;
	m_yH = m_Position.y - m_randomTarget.y;
	m_rotation =(float)(atan2(m_yH,m_xH) * 180.f / M_PI + 180.f);

	m_enemy.SetRotation(-m_rotation);
	m_enemyCannon.SetRotation(-m_rotation);
}

void EnemyAI::Shoot(sf::RenderWindow & App)
{
	if(m_Clock.GetElapsedTime() > m_ReloadTime)
	{
		m_Bullets.push_back(new EnemyBullet(m_enemyCannon.GetPosition(), m_randomTarget, m_rotation, 5));
		m_Clock.Reset();
	}
}

void EnemyAI::UpdateBullets(sf::RenderWindow & App)
{
	if(m_Bullets.size() > 0)
	{
		for(std::list<class EnemyBullet*>::const_iterator iter = m_Bullets.begin(); iter != m_Bullets.end(); )
		{
			if( (*iter)->toDelete() )
			{
				delete (*iter);
				iter = m_Bullets.erase(iter);
			}
			else
			{
				(*iter)->Update(App);
				++iter;
			}

		} // end for
	} // end if
}

sf::Sprite EnemyAI::GetSprite()
{
	return m_enemy;
}

void EnemyAI::SetToDelete()
{
	m_ToDelete = true;
}

int EnemyAI::GetEnemyHP()
{
	return m_HP;
}

void EnemyAI::Hited(int Damage)
{
	m_HP -= Damage;

	if(m_HP <= 0)
		SetToDelete();
}

bool EnemyAI::isAlive()
{
	return !m_ToDelete;
}