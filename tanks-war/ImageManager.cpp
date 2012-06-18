#include "stdafx.h"



const sf::Image& ImageManager::Get_Image(const std::string& nazwapliku)
{
	// checking is image exist in memory
	for(std::map<std::string, sf::Image>::const_iterator it = images_.begin(); it != images_.end(); it++)
	{
		if(nazwapliku == it->first)
			return it->second;
	}

	// adding image to memory if doesnt exist
	sf::Image obraz;
	if( obraz.LoadFromFile(nazwapliku) )
	{
		images_[nazwapliku] = obraz;
		return images_[nazwapliku];
	}

	// if not found nothing, use default blank
	images_[nazwapliku] = obraz;
	return images_[nazwapliku];
}

// remove image from memory via filename
void ImageManager::Delete_Image(const std::string& nazwapliku)
{
	std::map<std::string, sf::Image>::const_iterator it = images_.find(nazwapliku);
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