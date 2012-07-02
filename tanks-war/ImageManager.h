#include "stdafx.h"

#ifndef IMANAGER_H
#define IMANAGER_H
class ImageManager
{
public:
	ImageManager();
	// return const sf::Image
	const sf::Image & Get_Image(const std::string & filename);
	// remove image from memory via filename
	void Delete_Image(const std::string & filename);
	// return instnace to this object
	static ImageManager* GetInstance();
	
private:
	std::map<std::string , sf::Image > images_;

};
#endif