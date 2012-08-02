#include "stdafx.h"


MapManager::MapManager()
{
	map[0][0] = 0;
    map[0][1] = 1;
    map[0][2] = 0;
    map[0][3] = 0;
    map[1][0] = 0;
    map[1][1] = 0;
    map[1][2] = 0;
    map[1][3] = 0;
    map[2][0] = 0;
    map[2][1] = 0;
    map[2][2] = 0;
    map[2][3] = 0;
    map[3][0] = 0;
    map[3][1] = 0;
    map[3][2] = 0;
    map[3][3] = 1;


	tiles[0] = sf::Sprite(gResMng.Get_Image("CONTENT//mur.jpg")); // sciana
	tiles[1] = sf::Sprite(gResMng.Get_Image("CONTENT//mur3.jpg")); // droga
}

void MapManager::DrawMap(sf::RenderWindow & App, sf::View & View)
{
	
	for(int x = 0; x <= 3 ; x++)
	{
		for(int y = 0; y <= 3; y++)
		{
			int tileId = map[x][y];

			const sf::Image* image = tiles[tileId].GetImage();

			int width = image->GetWidth();
			int height = image->GetHeight();

			tiles[tileId].SetPosition(x * width, y * height);

			App.Draw(tiles[tileId]);
		}
	}

}