//NOT EVEN USED
//DEPRECATED
#include "Ekran1.h"

Ekran1::Ekran1()
{
	tlo.SetImage(LoadContent::GetInstance()->ImgMnr->Get_Image("tlo-test.png"));
	playing = false;
}

int Ekran1::Run(sf::RenderWindow &App)
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

			if(Event.Type == sf::Event::MouseButtonPressed && Event.MouseButton.Button == sf::Mouse::Left)
			{
				return 1;
			}
		}

		App.Draw(tlo);

		App.Display();
		sf::Sleep(0.01f);


	}
	return (-1);
}