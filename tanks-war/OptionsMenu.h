#include "stdafx.h"

class OptionsMenu : public cScreen
{
public:
	OptionsMenu();
	virtual int Run(sf::RenderWindow& App);


private:
	bool readXmlConfigFile();
	sf::Event m_Event;

	sf::Sprite _background;
	bool Running;
};