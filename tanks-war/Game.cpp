#include "stdafx.h"

Game::Game()
{
	m_running = true;
	m_inited = false;

}


int Game::Run(sf::RenderWindow & App)
{
	m_running = true;
	if(!m_inited)
		Init();


	while(m_running)
	{
		App.Clear();
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

			if(m_Event.Type == sf::Event::KeyPressed && m_Event.Key.Code == sf::Key::Right)
			{
				m_View->Move(5,0);
			}
			if(m_Event.Type == sf::Event::KeyPressed && m_Event.Key.Code == sf::Key::Left)
			{
				m_View->Move(-5,0);
			}
			if(m_Event.Type == sf::Event::KeyPressed && m_Event.Key.Code == sf::Key::Up)
			{
				m_View->Move(0,-5);
			}
			if(m_Event.Type == sf::Event::KeyPressed && m_Event.Key.Code == sf::Key::Down)
			{
				m_View->Move(0,5);
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
	
		App.SetView(*m_View);

		App.Draw(m_map);
		m_player->Update(App);
		m_View->SetCenter(m_player->GetPlayerPosition().x ,m_player->GetPlayerPosition().y);


		App.SetView(App.GetDefaultView());

float _Framerate = 1.f / App.GetFrameTime();	

#pragma region DEBUG INFO
std::ostringstream bufor;
sf::String tdebug;
tdebug.SetFont(LoadContent::GetInstance()->m_font2);
tdebug.SetSize(20);
bufor << "FPS = " << _Framerate <<"\nv= " << m_player->GetPlayerSpeed() << "\npoz= " << m_player->GetPlayerPosition().x << " " <<m_player->GetPlayerPosition().y;
bufor << "\n* = " << m_player->GetPlayerRotation() << "\nPociskow = " << m_player->m_Bullets.size();
tdebug.SetText(bufor.str());
App.Draw(tdebug);		
#pragma endregion		

sf::String test;
if(m_player->isReloading()) test.SetText("Reloading"); else test.SetText("");
test.SetPosition(App.GetInput().GetMouseX(),App.GetInput().GetMouseY()-30);
App.Draw(test);

		App.Display();
		sf::Sleep(0.01f);
	} // end of main loop

	return (-1);
}

void Game::Init()
{
	m_map.SetImage(gResMng.Get_Image("CONTENT//mapa-test.jpg"));

	m_player = new Player();

	m_View = new sf::View(sf::FloatRect(0,0,1300,700));

	

	m_inited = true;
}