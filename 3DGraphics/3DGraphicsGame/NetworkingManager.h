#pragma once


#include "network.h"
#include "client.h"
#include "server.h"

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

private:
	static NetworkingManager* s_pNetworkInstance;
	NetworkingManager() {};

	static std::thread _ClientReceiveThread;
	static std::thread _ServerReceiveThread;

	static char* _pcPacketData; //A local buffer to receive packet data info
	static CNetwork& _rNetwork;
	static EEntityType _eNetworkEntityType;
	static char _cIPAddress[MAX_ADDRESS_LENGTH]; // An array to hold the IP Address as a string
										  //ZeroMemory(&_cIPAddress, strlen(_cIPAddress));
	static CClient* _pClient;	//A pointer to hold a client instance
	static CServer* _pServer;	//A pointer to hold a server instance
	//AAAA
};

