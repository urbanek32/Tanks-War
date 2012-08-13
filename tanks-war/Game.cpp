#include "stdafx.h"

Game::Game()
{
	m_running = true;
	m_inited = false;
	m_Score = 0;
}


int Game::Run(sf::RenderWindow & App)
{
	m_running = true;
	if(!m_inited)
		Init();


	while(m_running)
	{
		App.Clear();
		if(m_clock2.GetElapsedTime() >= 0.5f)
		{
		m_Framerate = 1.f / App.GetFrameTime();	
		m_clock2.Reset();
		}
		while(App.GetEvent(m_Event))
		{
			if(m_Event.Type == sf::Event::Closed)
			{
				// CLOSE THE APP
				m_running = false;
				return (-1);
			}

			if(m_Event.Type == sf::Event::KeyPressed && m_Event.Key.Code == sf::Key::Escape)
			{
				// BACK TO MAINMENU
				m_running = false;
				return 1;
			}


			if(m_Event.Type == sf::Event::MouseWheelMoved && m_Event.MouseWheel.Delta > 0)
			{
				m_View->Zoom(1.1f);
			}

			if(m_Event.Type == sf::Event::MouseWheelMoved && m_Event.MouseWheel.Delta < 0)
			{
				m_View->Zoom(0.9f);
			}

			
		} // end of events loop
	
		CheckCollision();
		SpawnRandomEnemy();

		// PUT HERE: game objects etc
		App.SetView(*m_View);

		//App.Draw(m_map);
		m_MapMng->DrawMap(App, *m_View);
		UpdateEnemies(App);
		m_player->Update(App);
		m_View->SetCenter(m_player->GetPlayerPosition().x ,m_player->GetPlayerPosition().y);

		

		// PUT HERE: static objects like interface etc
		App.SetView(App.GetDefaultView());


		
#pragma region DEBUG INFO
std::ostringstream bufor;
sf::String tdebug;
tdebug.SetFont(LoadContent::GetInstance()->m_font2);
tdebug.SetSize(20);
bufor << "FPS = " << m_Framerate << " " << App.GetFrameTime() <<"\nv= " << m_player->GetPlayerSpeed() << "\npoz= " << m_player->GetPlayerPosition().x << " " <<m_player->GetPlayerPosition().y;
bufor << "\nEnemies alive = " << m_Enemies.size() << "\n*= " << m_player->GetPlayerRotation();
bufor << "\nYour hp = " << m_player->GetPlayerHP();
bufor << "\nView = " << m_View->GetRect().Left << " " << m_View->GetRect().Top;
bufor << "\nScore = " << m_Score;
tdebug.SetText(bufor.str());
App.Draw(tdebug);		
#pragma endregion		


		App.Display();
		//sf::Sleep(0.01f);
	} // end of main loop

	return (-1);
}

void Game::Init()
{
	m_map.SetImage(gResMng.Get_Image("CONTENT//mapa-test.jpg"));

	m_MapMng = new MapManager();

	m_player = new Player();

	m_View = new sf::View(sf::FloatRect(0,0,1300,700));

	m_inited = true;
}

void Game::CheckCollision()
{
	// NAJPIERW SPRAWDè WSZYSTKIE POCISKI GRACZA VS ENEMY_AI
	
	for(std::deque<class Bullet*>::const_iterator iter = m_player->m_Bullets.begin(); iter != m_player->m_Bullets.end(); ++iter)
	{
		for(std::deque<class EnemyAI*>::const_iterator iterE = m_Enemies.begin(); iterE != m_Enemies.end(); ++iterE)
		{
			if(Collision::BoundingBoxTest( (*iter)->GetSprite(), (*iterE)->GetSprite() ) )
			{
				// add damage
				(*iterE)->Hited( (*iter)->GetBulletDamage() );
				// delete bullet
				(*iter)->SetToDelete();
			}
		}
	}



	// TERAZ SPRAWDè WSZYSTKIE POCISKI ENEMY_AI VS GRACZ

	for(std::deque<class EnemyAI*>::const_iterator iter = m_Enemies.begin(); iter != m_Enemies.end(); ++iter)
	{
		for(std::deque<class EnemyBullet*>::const_iterator iterB = (*iter)->m_Bullets.begin(); iterB != (*iter)->m_Bullets.end(); ++iterB)
		{
			if(Collision::BoundingBoxTest( (*iterB)->GetSprite(), m_player->GetSprite() ) )
			{
				// add damage
				m_player->Hited( (*iterB)->GetBulletDamage() );
				// delete bullet
				(*iterB)->SetToDelete();
			}
		}
	}



	// TERAZ SPRAWDè CZY ENEMY_AI NIE WJECHA£ NA GRACZA I ODWROTNIE

}

void Game::UpdateEnemies(sf::RenderWindow & App)
{
	if(m_Enemies.size() > 0)
	{
		for(std::deque<class EnemyAI*>::const_iterator iter = m_Enemies.begin(); iter != m_Enemies.end(); )
		{
			if( (*iter)->isAlive() )
			{
				(*iter)->Update(App, m_player->GetPlayerPosition() );
				iter++;
			}
			else
			{
				delete (*iter);
				iter = m_Enemies.erase(iter);
				m_Score++;
			}
		} // end for
	} // end if
}

void Game::SpawnRandomEnemy()
{
	if(m_Clock.GetElapsedTime() > 5.f)
	{
		m_Enemies.push_back(new EnemyAI(sf::Vector2f(rand()%1000, rand()%700), 300.f, 400.f, 200));
		m_Clock.Reset();
	}
}