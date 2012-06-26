// tanks-war.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

GameManager *gameMng = new GameManager();


int main()
{

	sf::RenderWindow App(sf::VideoMode(1300,700,32), "Tanks War");
	App.SetPosition(0,-15);
	App.UseVerticalSync(false);
	


	gameMng->run(App);

	App.Close();
	return 0;
}

