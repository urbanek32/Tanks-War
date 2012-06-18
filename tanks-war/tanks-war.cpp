// tanks-war.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

menu *Menu;
ImageManager ImgMan;

int main()
{
	Menu = new menu();

	sf::RenderWindow App(sf::VideoMode(1300,731,32), "Tanks War");
	App.SetPosition(0,-15);
	App.UseVerticalSync(false);
	

	Menu->run(App);


	App.Close();
	return 0;
}

