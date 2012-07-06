#include "stdafx.h"

#ifndef RESNAGER_H
#define RESNAGER_H
class ResourceManager
{
public:
	ResourceManager();

	// return const sf::Image
	const sf::Image & Get_Image(const std::string & filename);

	//	load images to memory via filename
	bool Load_Image(const std::string & filename);

	// remove image from memory via filename
	void Delete_Image(const std::string & filename);

	// return instnace to this object
	static ResourceManager* GetInstance();

	// return size of resource container
	int Get_MapSize();
	
private:
	std::map<std::string , sf::Image > images_;


};
// global var for access to ResourceManager
extern ResourceManager gResMng;
#endif