// tanks-war.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

GameManager *gameMng = new GameManager();


int main()
{

	tgui::Window App(sf::VideoMode(1300,700,32), "Tanks War");
	App.setFramerateLimit(60);
	
	

	gameMng->run(App);


	App.clear();
	App.close();

	delete gameMng;

	return 0;
}

