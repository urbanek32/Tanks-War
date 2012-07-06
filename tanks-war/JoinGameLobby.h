#include "stdafx.h"

class JoinGameLobby : public cScreen
{
public:
	JoinGameLobby();
	virtual int Run(sf::RenderWindow & App);

private:
	sf::Event m_Event;
	bool m_running;

	sf::Sprite m_background;

	void Init();
	bool m_Inited;
};