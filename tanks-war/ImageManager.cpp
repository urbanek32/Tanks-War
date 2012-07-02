#include "stdafx.h"



const sf::Image & ImageManager::Get_Image(const std::string & filename)
{
	//	//	checking is texture exist in memory
	for(std::map<std::string, sf::Image>::const_iterator it = images_.begin(); it != images_.end(); it++)
	{
		if(filename == it->first)
			return it->second;
	}

	//	//	adding texture to memory if doesnt exist
	sf::Image _image;
	if( _image.loadFromFile(filename) )
	{
		images_[filename] = _image;
		return images_[filename];
	}

	//	//	if not found nothing, use default blank
	images_[filename] = _image;
	return images_[filename];
}

//	//	remove texture from memory via filename
void ImageManager::Delete_Image(const std::string & filename)
{
	std::map<std::string, sf::Image>::const_iterator it = images_.find(filename);
	if( it != images_.end() )
		images_.erase( it );
}

ImageManager::ImageManager() {}

#ifdef CPP_0x11
ImageManager* ptr=nullptr;
#else
ImageManager* ptr=NULL;
#endif

ImageManager* ImageManager::GetInstance()
{
	if(ptr==NULL) ptr=new ImageManager();
	return ptr;
}