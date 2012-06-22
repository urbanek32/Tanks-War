#include "stdafx.h"

#ifdef CPP_0x11
LoadContent* ptr=nullptr;
#else
LoadContent* ptr=NULL;
#endif

LoadContent::LoadContent()
{
	ImgMnr = new ImageManager();

	m_font.LoadFromFile("menu-font.ttf",80);


}


LoadContent* LoadContent::GetInstance()
{
	if(ptr==NULL) ptr=new LoadContent();
	return ptr;
}

int LoadContent::Run(sf::RenderWindow &App)
{

	return 1; // returns Go to MainMenu
}