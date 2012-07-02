#include "stdafx.h"

class LoadContent : public cScreen
{
public:
	LoadContent();
	// return instnace to this object
	static LoadContent* GetInstance();

	// main function to load and collect images
	ImageManager* ImgMnr;

	// main font instance
	sf::Font m_font;

	virtual int Run(tgui::Window &App);
};