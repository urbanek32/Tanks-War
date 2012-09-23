#include "stdafx.h"

#define PGI Physic::GetInstance()

MapManager::MapManager()
{
	tiles[0] = sf::Sprite(gResMng.Get_Image("CONTENT//mur.jpg")); // sciana
	tiles[1] = sf::Sprite(gResMng.Get_Image("CONTENT//mur3.jpg")); // droga

	tiles[0].SetCenter( tiles[0].GetSize().x /2, tiles[0].GetSize().y /2);
	tiles[1].SetCenter( tiles[1].GetSize().x /2, tiles[1].GetSize().y /2);
}

void MapManager::LoadMap(std::string pathfile, class Physic &physic)
{
	std::ifstream file(pathfile);
	if(file.fail()) 
	{
		std::cout<<"File does not exist\n";
		mapWidth = 0;
		mapHeight = 0;
	}

	file >> mapWidth >> mapHeight;

	for(unsigned int y = 0; y < mapHeight; y++)
	{
		for(unsigned int x = 0; x < mapWidth; x++)
		{
			file >> gameMap[x][y];
			tileID = gameMap[x][y];

			sf::Sprite *sprite = new sf::Sprite();

			m_image = tiles[tileID].GetImage();
			imageWidth = m_image->GetWidth();
			imageHeight = m_image->GetHeight();

			sprite->SetImage( *m_image );
			sprite->SetCenter(imageWidth / 2.f, imageHeight / 2.f);
			sprite->SetPosition( x * imageWidth, y * imageHeight);

			v_Map.push_back(sprite);

			if(tileID == 0)
			{
				physic.LoadStaticMapObjects(sprite->GetPosition().x, sprite->GetPosition().y, imageWidth, imageHeight);
			}
		}
	}
}

void MapManager::DrawMap(sf::RenderWindow & App, sf::View & View)
{
	/*
	for(unsigned int y = 0; y < mapHeight; y++)
	{
		for(unsigned int x = 0; x < mapWidth; x++)
		{
			tileID = gameMap[x][y];

			m_image = tiles[tileID].GetImage();
			imageWidth = m_image->GetWidth();
			imageHeight = m_image->GetHeight();

			tiles[tileID].SetPosition( x * imageWidth, y * imageHeight);
			
			App.Draw(tiles[tileID]);
		}
	}
	*/
	
	for(unsigned int i = 0; i < v_Map.size(); i++)
	{
		App.Draw(*v_Map[i]);
	}
}

unsigned int MapManager::GetMapWidth()
{
	return mapWidth;
}

unsigned int MapManager::GetMapHeight()
{
	return mapHeight;
}