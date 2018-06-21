//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name	: "NetworkingManager.cpp"
// Description	: NetworkingManager.cpp
// Author		: Vivian Ngo & Melanie Jacobson
// Mail			: vivian.ngo7572@mediadesign.school.nz
//

#include "NetworkingManager.h"

NetworkingManager* NetworkingManager::s_pNetworkInstance = 0;

char* _pcPacketData = 0;
CClient* _pClient = nullptr;
CServer* _pServer = nullptr;
CNetwork& _rNetwork = CNetwork::GetInstance();

NetworkingManager::~NetworkingManager()
{
	_ClientReceiveThread.join();
	_ServerReceiveThread.join();

	//Shut Down the Network
	_rNetwork.ShutDown();
	_rNetwork.DestroyInstance();

	delete[] _pcPacketData;
}

/***********************
* GetInstance: Gets Networking Manager Instance
* @author: Vivian Ngo & Melanie Jacobson
* @date: 20 / 06 / 18
* return s_pNetworkInstance - instance of network manager
***********************/
NetworkingManager * NetworkingManager::GetInstance()
{
	if (s_pNetworkInstance == 0)
	{
		s_pNetworkInstance = new NetworkingManager();
	}
	return s_pNetworkInstance;
}

/***********************
* DestroyInstance: Destroys network manager Instance
* @author: Vivian Ngo & Melanie Jacobson
* @date: 20 / 06 / 18
***********************/
void NetworkingManager::DestroyInstance()
{
	if (s_pNetworkInstance != 0) // If there is an instance of this class
	{
		//Delete the instance
		delete s_pNetworkInstance;
		s_pNetworkInstance = nullptr;
	}
}

/***********************
* Initialise: Initialise network manager Instance
* @author: Vivian Ngo & Melanie Jacobson
* @date: 20 / 06 / 18
***********************/
void NetworkingManager::Initialise()
{
	_pcPacketData = new char[MAX_MESSAGE_LENGTH];
	strcpy_s(_pcPacketData, strlen("") + 1, "");
	_rNetwork.StartUp();
}

/***********************
* StartupClient: Starts up client instance
* @author: Vivian Ngo & Melanie Jacobson
* @date: 20 / 06 / 18
***********************/
void NetworkingManager::StartupClient()
{
	_pClient = static_cast<CClient*>(_rNetwork.GetInstance().GetNetworkEntity());
	_ClientReceiveThread = std::thread(&CClient::ReceiveData, _pClient, std::ref(_pcPacketData));
	_eNetworkEntityType = CLIENT;
}

/***********************
* StartupClient: Starts up server instance
* @author: Vivian Ngo & Melanie Jacobson
* @date: 20 / 06 / 18
***********************/
void NetworkingManager::StartupServer()
{
	_pServer = static_cast<CServer*>(_rNetwork.GetInstance().GetNetworkEntity());
	_ServerReceiveThread = std::thread(&CServer::ReceiveData, _pServer, std::ref(_pcPacketData));
	_eNetworkEntityType = SERVER;
}

/***********************
* ProcessNetwork: Processes the network
* @author: Vivian Ngo & Melanie Jacobson
* @date: 20 / 06 / 18
***********************/
void NetworkingManager::ProcessNetwork()
{
	while(_rNetwork.IsOnline())
	{
		if (_eNetworkEntityType == CLIENT) //if network entity is a client
		{
			if (_pClient != nullptr)
			{
				//If the message queue is empty 
				if (_pClient->GetWorkQueue()->empty())
				{
					//Don't do anything
				}
				else
				{
					//Retrieve off a message from the queue and process it
					std::string temp;
					_pClient->GetWorkQueue()->pop(temp);
					_pClient->ProcessData(const_cast<char*>(temp.c_str()));
				}
			}
		}
		else
		{
			if (_pServer != nullptr)
			{
				if (!_pServer->GetWorkQueue()->empty())
				{
					_rNetwork.GetInstance().GetNetworkEntity()->GetRemoteIPAddress(_cIPAddress);

					//Retrieve off a message from the queue and process it
					_pServer->GetWorkQueue()->pop(_pcPacketData);
					_pServer->ProcessData(_pcPacketData);
				}
			}
		}
	}
}
