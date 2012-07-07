#include "stdafx.h"

class OptionsMenu : public cScreen
{
public:
	OptionsMenu();

	// main function to draw on screen
	virtual int Run(sf::RenderWindow & App); 

	// return static pointer to this class
	static OptionsMenu* GetInstance();

private:
	bool readDataFromXmlConfigFile(); // reading xml file for nick, nick_color and tank type
	bool saveDataToXmlConfigFile(); // save nick, nick_color and tank_type to xml config file
	sf::Event m_Event; // event container

	bool Running; // for main loop while
	
	
	sf::String player_nick, player_color, player_tankType; // helpers for XML
	std::string attr,t,elemName; // helpers for XML

	class TextBox *m_playerNickBox;

	// method using once at first enter to Run method
	void Init();

	// @up
	bool m_Inited;

};