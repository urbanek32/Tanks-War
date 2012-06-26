#include "stdafx.h"

JoinGameLobby::JoinGameLobby()
{
	Running = true;
	background.SetImage(LoadContent::GetInstance()->ImgMnr->Get_Image("CONTENT\\pokerface.jpg"));
}

int JoinGameLobby::Run(sf::RenderWindow & App)
{
	Running = true;

	while(Running)
	{
		App.Clear();

		while(App.GetEvent(m_Event))
		{
			if(m_Event.Type == sf::Event::Closed)
			{
				Running = false;
				return (-1);
			}

			if(m_Event.Type == sf::Event::KeyPressed && m_Event.Key.Code == sf::Key::Escape)
			{
				Running = false;
				return 1;
			}

		} // end of events while loop

		App.Draw(background);

		App.Display();
		sf::Sleep(0.01f);
	} // end of while loop

}