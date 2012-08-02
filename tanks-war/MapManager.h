#include "stdafx.h"


#ifndef MAPMANAGER_H
#define MAPMANAGER_H
class MapManager
{
public:
	MapManager();

	void DrawMap(sf::RenderWindow & App, sf::View & View);


private:
	sf::Sprite tiles[2];

	int map[4][4];

	std::vector<std::vector<int> > mape;

};
#endif