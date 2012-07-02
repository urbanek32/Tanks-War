#include "stdafx.h"

class OptionsMenu : public cScreen
{
public:
	OptionsMenu();
	virtual int Run(tgui::Window & App); // main function to draw on screen
	sf::String GetPlayerNick();
	sf::String GetPlayerColor();
	static OptionsMenu* GetInstance();

private:
	bool readDataFromXmlConfigFile(tgui::Window & App); // reading xml file for nick, nick_color and tank type
	bool saveDataToXmlConfigFile(); // save nick, nick_color and tank_type to xml config file
	void init_Gui(tgui::Window & app); // create TGUI for options
	sf::Event m_Event; // event container

	bool Running; // for main loop while
	
	
	sf::Text m_YourNickLabel, m_YourColorLabel, m_YourTankTypeLabel; // labeles for containers
	sf::String player_nick, player_color, player_tankType; // helpers for XML
	std::string attr,t,elemName; // helpers for XML

};