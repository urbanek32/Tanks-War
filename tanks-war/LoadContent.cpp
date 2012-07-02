#include "stdafx.h"

#ifdef CPP_0x11
LoadContent* ptr=nullptr;
#else
LoadContent* ptr=NULL;
#endif

LoadContent::LoadContent()
{
	ImgMnr = new ImageManager();

	m_font.loadFromFile("CONTENT\\menu-font2.ttf");


}


LoadContent* LoadContent::GetInstance()
{
	if(ptr==NULL) ptr=new LoadContent();
	return ptr;
}

int LoadContent::Run(tgui::Window &App)
{

	return 1; // returns Go to MainMenu
}