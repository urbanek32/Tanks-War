#include "stdafx.h"


class Ekran1 : public cScreen
{
public:
	Ekran1();
	virtual int Run(sf::RenderWindow &App);

private:
	sf::Sprite tlo;
	bool playing;
};