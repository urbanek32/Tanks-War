#include "stdafx.h"

ServerManager::ServerManager()
{

}

ServerManager::ServerManager(sf::SocketUDP & SocketUDP, unsigned short ServerPort)
{
	SocketUDP.Bind(ServerPort);

	m_Running = true;

	std::cout<<"Server is running on port: "<<SocketUDP.GetPort()<<std::endl;
}

void ServerManager::Run(sf::SocketUDP & SocketUDP)
{
	while(m_Running)
	{
		SocketUDP.Receive(m_PacketRec, m_IPRec, m_PortRec);

		(m_PacketRec >> m_PacketType);

		switch(m_PacketType)
		{
		case sf::Uint8(1):	// PING packet, resend it
			{
				ResendPing(SocketUDP, m_PacketRec, m_IPRec, m_PortRec);
				std::cout<<" PING sent\n";
				break;
			}
		case sf::Uint8(2) :	// New Player Packet
			{
				std::cout<<"New player: " << m_IPRec << " : " << m_PortRec << std::endl;
				AddNewPlayer(m_PacketRec, m_IPRec, m_PortRec);
				SendAcceptedNewPlayer(SocketUDP, m_IPRec, m_PortRec);
				SendToAllNewPlayerJoin(SocketUDP, m_IPRec, m_PortRec);
				break;
			}
		case sf::Uint8(3) :	// Player list packet, resend it
			{
				SendPlayerList(SocketUDP, m_IPRec, m_PortRec);
				std::cout<<" Player List Sent: " << GetPlayerList() << std::endl;
				break;
			}
		case sf::Uint8(4) :	// New data arrived, send it to all
			{
				ManageArrivedData(SocketUDP, m_PacketRec, m_IPRec, m_PortRec);
				std::cout<<"\tData update"<<std::endl;
				break;
			}

		}// end switch



	} // end while
}

void ServerManager::ResendPing(sf::SocketUDP & SocketUDP, sf::Packet & Packet, sf::IPAddress & IPToSend, unsigned short PortToSend)
{
	SocketUDP.Send(Packet, IPToSend, PortToSend);
}


void ServerManager::SendPlayerList(sf::SocketUDP & SocketUDP, sf::IPAddress & IPToSend, unsigned short PortToSend)
{
	sf::Packet *_packet = new sf::Packet();

	*_packet << sf::Uint8(3) << GetPlayerList();

	SocketUDP.Send(*_packet, IPToSend, PortToSend);

	delete _packet;
}

int ServerManager::GetPlayerList()
{
	return m_Players.size();
}

void ServerManager::ManageArrivedData(sf::SocketUDP & SocketUDP, sf::Packet & Packet, sf::IPAddress & IPRec, unsigned short PortRec)
{
	for(std::deque<class RemotePlayer*>::const_iterator it = m_Players.begin(); it != m_Players.end(); ++it)
	{
		if( (*it)->GetIP() == IPRec && (*it)->GetPort() == PortRec)
		{
			Packet >> m_PlayerNick >> m_PosX >> m_PosY >> m_Rotation >> m_CannonRotation;

			(*it)->SetNick(m_PlayerNick);
			(*it)->SetPosition(m_PosX, m_PosY);
			(*it)->SetRotation(m_Rotation);
			(*it)->SetCannonRotation(m_CannonRotation);
		}
		else
		{
			Packet.Clear();
			Packet << sf::Uint8(4) << IPRec.ToString() << PortRec << m_PosX << m_PosY << m_Rotation << m_CannonRotation;
			std::cout << sf::Uint8(4) << IPRec.ToString() << PortRec << m_PosX << m_PosY << m_Rotation << m_CannonRotation << std::endl;
			SocketUDP.Send(Packet, (*it)->GetIP(), (*it)->GetPort() );
		}
	}
}

void ServerManager::CheckPing()
{


}

void ServerManager::AddNewPlayer(sf::Packet & Packet, sf::IPAddress & IP, unsigned short Port)
{
	Packet >> m_PlayerNick >> m_PlayerTankType >> m_PlayerCannonType;
	m_Players.push_back(new RemotePlayer(IP, Port, m_PlayerNick, m_PlayerTankType, m_PlayerCannonType));
//std::cout << m_PlayerNick << m_PlayerTankType << m_PlayerCannonType << std::endl;
}

void ServerManager::SendAcceptedNewPlayer(sf::SocketUDP & SocketUDP, sf::IPAddress & IPToSend, unsigned short PortToSend)
{
	sf::Packet *_packet = new sf::Packet();

	*_packet << sf::Uint8(2);
	SocketUDP.Send(*_packet, IPToSend, PortToSend);

	delete _packet;
}

void ServerManager::SendToAllNewPlayerJoin(sf::SocketUDP & SocketUDP, sf::IPAddress & IPRec, unsigned short PortRec)
{
	sf::Packet *_packet = new sf::Packet();
	
std::cout<<"STANPJ: " << sf::Uint8(2) << IPRec.ToString() << PortRec << m_Players.back()->GetPlayerNick() << m_Players.back()->GetTankType() << m_Players.back()->GetCannonType() << std::endl;

	*_packet << sf::Uint8(2) << IPRec.ToString() << PortRec << m_Players.back()->GetPlayerNick() << m_Players.back()->GetTankType() << m_Players.back()->GetCannonType();
	

	for(std::deque<class RemotePlayer*>::const_iterator it = m_Players.begin(); it != m_Players.end(); ++it)
	{
		if( (*it)->GetIP() != IPRec || (*it)->GetPort() != PortRec )
		{
			SocketUDP.Send(*_packet, (*it)->GetIP(), (*it)->GetPort() );
		}
	}

	delete _packet;
}