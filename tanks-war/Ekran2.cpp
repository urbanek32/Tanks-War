//NOT EVEN USED
//DEPRECATED
#include "stdafx.h"


Ekran2::Ekran2()
{
	tlo.SetImage(LoadContent::GetInstance()->ImgMnr->Get_Image("tlo-opcje-test.png"));
}

int Ekran2::Run(sf::RenderWindow &App)
{
	sf::Event Event;
	bool Running = true;

	while(Running)
	{
		App.Clear();
		while(App.GetEvent(Event))
		{
			// Window closed
            if (Event.Type == sf::Event::Closed)
            {
                return (-1);
            }

			if(Event.Type == sf::Event::MouseButtonPressed && Event.MouseButton.Button == sf::Mouse::Right)
			{
				return 0;
			}
		}

		App.Draw(tlo);
		App.Display();
		sf::Sleep(0.01f);
	}
	return (-1);
}