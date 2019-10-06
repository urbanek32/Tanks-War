#include "stdafx.h"

// global var for access to ResourceManager
ResourceManager gResMng;

const sf::Image & ResourceManager::Get_Image(const std::string & filename)
{ 
	//	//	checking is image exist in memory
	for(std::map<std::string, sf::Image>::const_iterator it = images_.begin(); it != images_.end(); it++)
	{
		if(filename == it->first)
			return it->second;
	}

	//	//	adding image to memory if doesnt exist
	sf::Image _image;
/*	if( _image.LoadFromFile(filename) )
	{
		images_[filename] = _image;
		return images_[filename];
	}
*/
	//	//	if not found nothing, use default blank
	images_[filename] = _image;
	return images_[filename];
}

bool ResourceManager::Load_Image(const std::string & filename)
{
	sf::Image _image;
	if( _image.LoadFromFile(filename) )
	{
		images_[filename] = _image;
		return true;
	}
	return false;
}

int ResourceManager::Get_MapSize()
{
	return (int)images_.size();
}

void ResourceManager::Delete_Image(const std::string & filename)
{
	std::map<std::string, sf::Image>::const_iterator it = images_.find(filename);
	if( it != images_.end() )
		images_.erase( it );
}

ResourceManager::ResourceManager() 
{
	
}

#ifdef CPP_0x11
ResourceManager* rm_ptr=nullptr;
#else
ResourceManager* rm_ptr=NULL;
#endif

ResourceManager* ResourceManager::GetInstance()
{
	if(rm_ptr==NULL) rm_ptr=new ResourceManager();
	return rm_ptr;
}