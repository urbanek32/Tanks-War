#include "stdafx.h"

#ifndef MANAG_H
#define MANAG_H
class ImageManager
{
public:
	ImageManager();
	// return const sf::Image for sf::Sprite->SetImage or something
	const sf::Image & Get_Image(const std::string& nazwapliku);
	// remove image from memory via filename
	void Delete_Image(const std::string& nazwapliku);
	// return instnace to this object
	static ImageManager* GetInstance();
	
private:
	std::map<std::string , sf::Image > images_;

};
#endif