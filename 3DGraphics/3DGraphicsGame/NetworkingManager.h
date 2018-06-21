#pragma once
//Library Includes
#include <Windows.h>
#include <cassert>
//#include <vld.h>
#include <thread>

//Local Includes
#include "consoletools.h"
#include "network.h"
#include "client.h"
#include "server.h"
#include "InputLineBuffer.h"
#include <functional>
#include "control.h"



class NetworkingManager
{
public:
	static void Initialise();
	~NetworkingManager();
	static NetworkingManager* GetInstance();
	static void DestroyInstance();
	static void StartupClient();
	static void StartupServer();
	static void ProcessNetwork();

private:
	static NetworkingManager* s_pNetworkInstance;
	NetworkingManager() {};

	static std::thread _ClientReceiveThread, _ServerReceiveThread;

	static char* _pcPacketData; //A local buffer to receive packet data info
	static CNetwork& _rNetwork;
	static EEntityType _eNetworkEntityType;
	static char _cIPAddress[MAX_ADDRESS_LENGTH]; // An array to hold the IP Address as a string
										  //ZeroMemory(&_cIPAddress, strlen(_cIPAddress));
	static CClient* _pClient;	//A pointer to hold a client instance
	static CServer* _pServer;	//A pointer to hold a server instance
	//AAAA
};

