#include "stdafx.h"

#ifdef CPP_0x11
LoadContent* lc_ptr=nullptr;
#else
LoadContent* lc_ptr=NULL;
#endif

LoadContent::LoadContent()
{

	m_font.LoadFromFile("CONTENT//defused.ttf",50);
	m_font2.LoadFromFile("CONTENT//SinsBold.ttf",50);
	m_Inited = false;
	m_loadAll = new LoadAll();
}

void LoadContent::Init()
{

	m_text = new sf::String("Loading content...",m_font, 40);
	m_text->SetPosition(400, 200);
	m_text->SetColor(sf::Color::Yellow);
	
}

LoadContent* LoadContent::GetInstance()
{
	if(lc_ptr==NULL) lc_ptr=new LoadContent();
	return lc_ptr;
}

int LoadContent::Run(sf::RenderWindow &App)
{
	m_loadAll->Launch();
	Init();

	while(!m_loadAll->done)
	{
		App.Clear();
		while(App.GetEvent(m_Event))
		{
			if(m_Event.Type == sf::Event::Closed)
				return (-1);
		}
	

		App.Draw(*m_text);

		App.Display();
		sf::Sleep(0.01f);		
	}
	m_loadAll->Wait();
	
	delete m_text;
	return 1; // returns Go to MainMenu
}

LoadAll::LoadAll()
{
	done = false;
}

void LoadAll::Run()
{
	// PUT HERE ALL CONTENT TO LOAD

	gResMng.Load_Image("CONTENT//tlo-test.png");

	gResMng.Load_Image("CONTENT//cannon.png"); // Local player
	gResMng.Load_Image("CONTENT//bullet.png");
	gResMng.Load_Image("CONTENT//tank.png");

	gResMng.Load_Image("CONTENT//cannon1.png"); // AI player
	gResMng.Load_Image("CONTENT//tank1.png");

	gResMng.Load_Image("CONTENT//mapa-test.jpg");
	gResMng.Load_Image("CONTENT//mur.jpg");
	gResMng.Load_Image("CONTENT//mur3.jpg");

	gResMng.Load_Image("CONTENT//CannonMedium.png"); // Remote player
	gResMng.Load_Image("CONTENT//TankMedium.png");

	done = true;
}
