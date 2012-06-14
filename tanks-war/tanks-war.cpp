// tanks-war.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int main()
{
	sf::RenderWindow okno(sf::VideoMode(800,600,32), "Tanks War");

	while(okno.IsOpened())
	{
		okno.Clear();




		okno.Display();
		sf::Sleep(0.01f);
	}

	return 0;
}

