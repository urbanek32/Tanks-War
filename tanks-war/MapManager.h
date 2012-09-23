#include "stdafx.h"


#ifndef MAPMANAGER_H
#define MAPMANAGER_H
class MapManager
{
public:
	MapManager();

	void DrawMap(sf::RenderWindow & App, sf::View & View);

	void LoadMap(std::string pathfile, class Physic & physic);

	unsigned int GetMapWidth();

	unsigned int GetMapHeight();

private:
	sf::Sprite tiles[2];

	unsigned int mapWidth, mapHeight, tileID, imageWidth, imageHeight;

	unsigned int gameMap[100][100];

	const sf::Image* m_image;

	std::vector<sf::Sprite*> v_Map;
};
#endif