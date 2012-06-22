#include "stdafx.h"

class Ekran2 : public cScreen
{
public:
	Ekran2();
	virtual int Run(sf::RenderWindow &App);

private:
	sf::Sprite tlo;
	bool playing;
};