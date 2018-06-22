#pragma once


#include "network.h"
#include "client.h"
#include "server.h"
#include <iostream>

class NetworkingManager
{
public:
	~NetworkingManager();
	static NetworkingManager* GetInstance();
	static void DestroyInstance();
	static void Initialise();

	static void StartupClient();
	static void StartupServer();
	static void ProcessNetwork();
	static void StartUpNetwork();
	/*static void BroadCastServers();
	static void ConnectToServer(int i);*/

	static std::vector<sockaddr_in> GetServerList() { return m_vecServerAddresses; }
	static void AddToServerList(sockaddr_in _add) { m_vecServerAddresses.push_back(_add); }

private:
	static NetworkingManager* s_pNetworkInstance;
	NetworkingManager() {};

	static char* _pcPacketData; //A local buffer to receive packet data info
	static CNetwork& _rNetwork;
	static EEntityType _eNetworkEntityType;
	static char _cIPAddress[MAX_ADDRESS_LENGTH]; // An array to hold the IP Address as a string
										  //ZeroMemory(&_cIPAddress, strlen(_cIPAddress));
	static CClient* _pClient;	//A pointer to hold a client instance
	static CServer* _pServer;	//A pointer to hold a server instance

	static std::vector<sockaddr_in> m_vecServerAddresses;

	static sockaddr_in m_ServerSocketAddress;
	static char _cServerIPAddress[128];

	static float cEndTime;
	static float cStartTime;
	static bool _bServerChosen;

};

