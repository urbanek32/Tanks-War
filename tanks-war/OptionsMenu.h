#include "stdafx.h"

class OptionsMenu : public cScreen
{
public:
	OptionsMenu();
	virtual int Run(sf::RenderWindow& App); // main function to draw on screen


private:
	bool readXmlConfigFile(); // reading xml file for nick, nick_color and tank type
	sf::Event m_Event; // event container

	bool Running; // for main loop while

	class ImageButton *m_button_nick;
	
	sf::String YourNick, YourColor, YourTankType; // labeles for containers
	sf::Shape NickShape, ColorShape, TankTypeShape; // contour containers
	sf::FloatRect nickRect, colorRect, tankTypeRect; // helpers for detecting events
	bool nickClicked, colorClicked, tankTypeClicked; // helpers for detecting events
	sf::Color colorNick, colorColor, colorTankType; // color for shapes to recognize which shape was clicked

	sf::String player_nick, player_color, player_tankType; // helpers for XML
	std::string attr,t,elemName; // helpers for XML
};