#include "stdafx.h"

class JoinGameLobby : public cScreen
{
public:
	JoinGameLobby();
	virtual int Run(sf::RenderWindow & App);

private:
	sf::Event m_Event;
	bool Running;

	sf::Sprite background;
};