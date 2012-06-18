#include "stdafx.h"


extern ImageManager ImgMan;

void menu::run(sf::RenderWindow& App)
{
	while(App.IsOpened())
	{
		App.Clear();

		while(App.GetEvent(m_Event))
		{
			if(m_Event.Type == sf::Event::Closed)
				App.Close();
			if(m_Event.Type == sf::Event::KeyPressed && m_Event.Key.Code == sf::Key::Escape)
				App.Close();

		}

		logo.SetPosition(App.GetWidth()/3,30);
		logo.SetScale(0.9f,0.9f);


		App.Draw(background);
		App.Draw(logo);
		
		App.Display();
		sf::Sleep(0.01f);
	}

}

menu::menu()
{
	background.SetImage(ImgMan.Get_Image("tlo-test.png"));
	logo.SetImage(ImgMan.Get_Image("tankswar-logo.png"));
}