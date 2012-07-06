// tanks-war.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

GameManager *gameMng = new GameManager();


int main()
{

	sf::RenderWindow App(sf::VideoMode(1300,700,32), "Tanks War");
	App.SetFramerateLimit(60);
	

	gameMng->run(App);


	App.Clear();
	App.Close();

	delete gameMng;

	return 0;
}

