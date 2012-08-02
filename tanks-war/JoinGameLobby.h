#include "stdafx.h"

#ifndef JOINLOBBY_H
#define JOINLOBBY_H
class JoinGameLobby : public cScreen
{
public:
	JoinGameLobby();
	virtual int Run(sf::RenderWindow & App);

	std::string GetServerIP();

	static JoinGameLobby* GetInstance();

private:
	sf::Event m_Event;
	bool m_running;

	sf::Sprite m_Background;

	class TextBox *m_serverIPBox;

	sf::String m_serverIP, m_serverPing;

	void Init();
	bool m_Inited;

	sf::Clock m_pingclock;
};
#endif