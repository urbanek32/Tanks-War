#include "stdafx.h"
#include <math.h>

static const double M_PI=3.14159265358979323846f;



Player::Player() : m_maxPlayerSpeed(400.0), m_maxPlayerBackSpeed(-300.0)
{
	m_inited = false;
	m_V = 0.f;
	m_rotation = 0;
	m_rotationDegree = 0;
}

void Player::Update(sf::RenderWindow & App)
{
	if(!m_inited)
		Init();

	float _ElapsedTime = m_clock.GetElapsedTime();
	m_clock.Reset();

	const sf::Input & _input = App.GetInput();

		if(_input.IsKeyDown(sf::Key::A)) { m_rotationDegree -= 1; m_rotation=1.0;  m_player.Rotate(m_rotation); } // turn LEFT
		if(_input.IsKeyDown(sf::Key::D)) { m_rotationDegree += 1; m_rotation=-1.0; m_player.Rotate(m_rotation); } // turn RIGHT

		if(_input.IsKeyDown(sf::Key::W)) { m_V += 3.00  ;    }
		if(_input.IsKeyDown(sf::Key::S)) { m_V -= 1.50  ;    }
		if(_input.IsKeyDown(sf::Key::Space)) { m_V = 0.0 ;  }

		 
			if(m_clock2.GetElapsedTime() > 1.0f)
			{
				if(_input.IsMouseButtonDown(sf::Mouse::Left))
				{
					Shoot(App);
					m_reload = true;
					m_clock2.Reset();
				}
				m_reload = false;
			}
			else
			{
				m_reload = true;
			}
		

		UpdateBullets(App);

//		m_mousePozVec.x = _input.GetMouseX();
//		m_mousePozVec.y = _input.GetMouseY();

		m_mousePozVec = App.ConvertCoords(App.GetInput().GetMouseX(), App.GetInput().GetMouseY());

		m_xH = m_cannon.GetPosition().x - m_mousePozVec.x;
		m_yH = m_cannon.GetPosition().y - m_mousePozVec.y;
		m_cannonRotation =(float)(atan2(m_yH,m_xH) * 180 / M_PI +180);


		if(m_rotationDegree > 359) m_rotationDegree = 0;
		if(m_rotationDegree < 0) m_rotationDegree = 359;
		
//		if( kierunek > 359 ) kierunek = 0;
//      if( kierunek < 0 ) kierunek = 359;

        if( m_V > m_maxPlayerSpeed ) m_V = m_maxPlayerSpeed;
        if( m_V <  m_maxPlayerBackSpeed ) m_V = m_maxPlayerBackSpeed;

		m_disVec.x += m_V * tab_cos[m_rotationDegree];
        m_disVec.y += m_V * tab_sin[m_rotationDegree];

		if( m_disVec.x >= 1 || m_disVec.x <= - 1 ) { m_playerPozVec.x += int(m_disVec.x) * App.GetFrameTime(); m_disVec.x = m_disVec.x - int( m_disVec.x ); }
        if( m_disVec.y >= 1 || m_disVec.y <= - 1 ) { m_playerPozVec.y += int(m_disVec.y) * App.GetFrameTime(); m_disVec.y = m_disVec.y - int( m_disVec.y ); }
		
		
		m_player.SetPosition(m_playerPozVec.x, m_playerPozVec.y);


		m_cannon.SetPosition(m_player.GetPosition());
		m_cannon.SetRotation(-m_cannonRotation);
/*
#pragma region DEBUG INFO
std::ostringstream bufor;
sf::String tdebug;
tdebug.SetFont(LoadContent::GetInstance()->m_font2);
tdebug.SetSize(20);
bufor << "\nFPS = " << _Framerate;
tdebug.SetText(bufor.str());
App.Draw(tdebug);		
#pragma endregion	
*/
		App.Draw(m_player);
		App.Draw(m_cannon);
}

void Player::Init()
{
	for(int i=0; i < 360; i ++)
     {
        tab_sin[i] = sin((M_PI*(i))/180);
        tab_cos[i] = cos((M_PI*(i))/180);
     } 

	m_player.SetImage(gResMng.Get_Image("CONTENT//tank.png"));
	m_player.SetCenter(m_player.GetSize().x / 2, m_player.GetSize().y / 2 );
	

	m_cannon.SetImage(gResMng.Get_Image("CONTENT//cannon.png"));
	m_cannon.SetCenter(m_cannon.GetSize().x / 3.5f, m_cannon.GetSize().y /2.f );
	
	m_playerPozVec = sf::Vector2f(200, 300);
	m_Health = 100;

	m_inited = true;
}

bool Player::isReloading()
{
	return m_reload;
}

sf::Vector2f Player::GetPlayerPosition()
{
	return m_playerPozVec;
}

double Player::GetPlayerSpeed()
{
	return m_V;
}

float Player::GetPlayerRotation()
{
	return m_player.GetRotation();
}

void Player::Shoot(sf::RenderWindow & App)
{
	m_Bullets.push_back(new Bullet(App, m_cannon.GetPosition(), m_cannonRotation, 50));
}

void Player::UpdateBullets(sf::RenderWindow & App)
{
	if(m_Bullets.size() > 0)
	{
		for(std::list<class Bullet*>::const_iterator iter = m_Bullets.begin(); iter != m_Bullets.end(); )
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

sf::Sprite Player::GetSprite()
{
	return m_player;
}

int Player::GetPlayerHP()
{
	return m_Health;
}

void Player::Hited(int Damage)
{
	m_Health -= Damage;
}