#include "stdafx.h"
#include <math.h>

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

#ifdef CPP_0x11
Player* p_ptr=nullptr;
#else
Player* p_ptr=NULL;
#endif

Player* Player::GetInstance()
{
	if(p_ptr==NULL) p_ptr = new Player();
	return p_ptr;
}

Player::Player() : m_maxPlayerSpeed(400.0), m_maxPlayerBackSpeed(-300.0)
{
	m_inited = false;
	m_V = 0.f;
	m_rotation = 0;
	m_rotationDegree = 0;
}

void Player::Update(sf::RenderWindow & App, class Physic & physic)
{
	if(!m_inited)
		Init(physic);


	const sf::Input & _input = App.GetInput();

	physic.GetPlayer(0)->vel = physic.GetPlayer(0)->body->GetLinearVelocity();
	physic.GetPlayer(0)->rotation = physic.GetPlayer(0)->body->GetAngle();

		if(_input.IsKeyDown(sf::Key::A)) { physic.GetPlayer(0)->rotation += -1.0f * App.GetFrameTime(); physic.GetPlayer(0)->body->SetTransform(physic.GetPlayer(0)->body->GetPosition(), physic.GetPlayer(0)->rotation); /*m_rotationDegree -= 3; m_rotation = 3; m_player.Rotate( (float)m_rotation );*/ } // turn LEFT
		if(_input.IsKeyDown(sf::Key::D)) { physic.GetPlayer(0)->rotation += 1.0f * App.GetFrameTime(); physic.GetPlayer(0)->body->SetTransform(physic.GetPlayer(0)->body->GetPosition(), physic.GetPlayer(0)->rotation); /*m_rotationDegree += 3; m_rotation = -3; m_player.Rotate( (float)m_rotation  );*/ } // turn RIGHT

		if(_input.IsKeyDown(sf::Key::W)) { m_V += 2.00  ;    }
		if(_input.IsKeyDown(sf::Key::S)) { m_V -= 1.00  ;    }
		if(_input.IsKeyDown(sf::Key::Space)) { m_V = 0.0 ;  }

		physic.GetPlayer(0)->body->SetAngularVelocity(0.f);

/*		 
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
		
*/
//		UpdateBullets(App);

//		m_mousePozVec.x = _input.GetMouseX();
//		m_mousePozVec.y = _input.GetMouseY();

		m_mousePozVec = App.ConvertCoords(App.GetInput().GetMouseX(), App.GetInput().GetMouseY());

		m_xH = m_cannon.GetPosition().x - m_mousePozVec.x;
		m_yH = m_cannon.GetPosition().y - m_mousePozVec.y;
		m_cannonRotation =(float)(atan2(m_yH,m_xH) * 180.f / b2_pi + 180.f);


//		if(physic.GetPlayer(0)->rotation > 359) physic.GetPlayer(0)->rotation = 0;
//		if(physic.GetPlayer(0)->rotation < 0) physic.GetPlayer(0)->rotation = 359;
		

        if( m_V > m_maxPlayerSpeed ) m_V = m_maxPlayerSpeed;
        if( m_V <  m_maxPlayerBackSpeed ) m_V = m_maxPlayerBackSpeed;

		physic.GetPlayer(0)->vel.x = m_V * cos((b2_pi*(physic.GetPlayer(0)->rotation * RADTODEG ))/180.f);
        physic.GetPlayer(0)->vel.y = m_V * sin((b2_pi*(physic.GetPlayer(0)->rotation * RADTODEG ))/180.f);

//		if( m_disVec.x >= 1 || m_disVec.x <= - 1 ) { m_playerPozVec.x += int(m_disVec.x) * App.GetFrameTime(); m_disVec.x = m_disVec.x - int( m_disVec.x ); }
//      if( m_disVec.y >= 1 || m_disVec.y <= - 1 ) { m_playerPozVec.y += int(m_disVec.y) * App.GetFrameTime(); m_disVec.y = m_disVec.y - int( m_disVec.y ); }
		
		physic.GetPlayer(0)->body->SetLinearVelocity(physic.GetPlayer(0)->vel);
		
		m_player.SetPosition( physic.GetPlayer(0)->GetPosition() );
		m_player.SetRotation( -physic.GetPlayer(0)->rotation * RADTODEG );


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

//FIXME: This must be fixed or deleted!
void Player::Update(sf::RenderWindow & App)
{
	const sf::Input & _input = App.GetInput();

	if(_input.IsKeyDown(sf::Key::W)) { m_V += 2.00  ;    }
	if(_input.IsKeyDown(sf::Key::S)) { m_V -= 1.00  ;    }
	if(_input.IsKeyDown(sf::Key::Space)) { m_V = 0.0 ;  }

	m_mousePozVec = App.ConvertCoords(App.GetInput().GetMouseX(), App.GetInput().GetMouseY());

	m_xH = m_cannon.GetPosition().x - m_mousePozVec.x;
	m_yH = m_cannon.GetPosition().y - m_mousePozVec.y;
	m_cannonRotation =(float)(atan2(m_yH,m_xH) * 180.f / b2_pi + 180.f);

	if( m_V > m_maxPlayerSpeed ) m_V = m_maxPlayerSpeed;
	if( m_V <  m_maxPlayerBackSpeed ) m_V = m_maxPlayerBackSpeed;

	m_cannon.SetPosition(m_player.GetPosition());
	m_cannon.SetRotation(-m_cannonRotation);

	App.Draw(m_player);
	App.Draw(m_cannon);
}

void Player::Init(class Physic & physic)
{
	m_playerPozVec = sf::Vector2f(64, 64);


	m_player.SetImage(gResMng.Get_Image("CONTENT//tank.png"));
	m_player.SetCenter(m_player.GetSize().x / 2.f, m_player.GetSize().y / 2.f );
	m_player.SetPosition(m_playerPozVec);
	

	m_cannon.SetImage(gResMng.Get_Image("CONTENT//cannon.png"));
	m_cannon.SetCenter(m_cannon.GetSize().x / 3.5f, m_cannon.GetSize().y /2.f );
	
	m_Health = 100;

	physic.AddPlayer(m_player.GetPosition().x, m_player.GetPosition().y, m_player.GetSize().x, m_player.GetSize().y);

	m_inited = true;
}

bool Player::isReloading()
{
	return m_reload;
}

sf::Vector2f & Player::GetPlayerPosition()
{
	return m_playerPozVec;
}

double & Player::GetPlayerSpeed()
{
	return m_V;
}

float Player::GetPlayerRotation()
{
	return m_player.GetRotation();
}

float & Player::GetCannonRotation()
{
	return m_cannonRotation;
}

void Player::Shoot(sf::RenderWindow & App)
{
	m_Bullets.push_back(new Bullet(App, m_cannon.GetPosition(), m_cannonRotation, 50));
}

void Player::UpdateBullets(sf::RenderWindow & App)
{
	if(m_Bullets.size() > 0)
	{
		for(std::deque<class Bullet*>::const_iterator iter = m_Bullets.begin(); iter != m_Bullets.end(); )
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

sf::Sprite & Player::GetSprite()
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