// tanks-war - server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"



int main(int argc, _TCHAR* argv[])
{
	sf::SocketUDP _SocketUDP;

	ServerManager *serverMng = new ServerManager(_SocketUDP, 6666);

	serverMng->Run(_SocketUDP);


	delete serverMng;
	_SocketUDP.Close();

	return 0;
}

