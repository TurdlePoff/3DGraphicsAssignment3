
 //Bachelor of Software Engineering
 //Media Design School
 //Auckland
 //New Zealand

 //(c) 2018 Media Design School

 //File Name	: "NetworkingManager.cpp"
 //Description	: NetworkingManager.cpp
 //Author		: Vivian Ngo & Melanie Jacobson
 //Mail			: vivian.ngo7572@mediadesign.school.nz


#include "NetworkingManager.h"

NetworkingManager* NetworkingManager::s_pNetworkInstance = 0;

char* NetworkingManager::_pcPacketData = 0;
CClient* NetworkingManager::_pClient = nullptr;
CServer* NetworkingManager::_pServer = nullptr;
CNetwork& NetworkingManager::_rNetwork = CNetwork::GetInstance();
EEntityType NetworkingManager::_eNetworkEntityType = DEFAULT;
char NetworkingManager::_cIPAddress[MAX_ADDRESS_LENGTH] = {};
std::thread _ClientReceiveThread;
std::thread _ServerReceiveThread;
std::vector<sockaddr_in> NetworkingManager::m_vecServerAddresses;

NetworkingManager::~NetworkingManager()
{
	/*_ClientReceiveThread.join();
	_ServerReceiveThread.join();
*/
	//Shut Down the Network
	_rNetwork.ShutDown();
	_rNetwork.DestroyInstance();

	//delete[] _pcPacketData;
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
	/*_ClientReceiveThread.join();
	_ServerReceiveThread.join();*/

	//Shut Down the Network
	_rNetwork.ShutDown();
	_rNetwork.DestroyInstance();

	delete[] _pcPacketData;
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
	//_ClientReceiveThread = std::thread(&CClient::ReceiveData, _pClient, std::ref(_pcPacketData));
	_eNetworkEntityType = CLIENT;
	//_rNetwork.GetInstance().Initialise(_eNetworkEntityType);
}

/***********************
* StartupClient: Starts up server instance
* @author: Vivian Ngo & Melanie Jacobson
* @date: 20 / 06 / 18
***********************/
void NetworkingManager::StartupServer()
{
	_pServer = static_cast<CServer*>(_rNetwork.GetInstance().GetNetworkEntity());
	//_ServerReceiveThread = std::thread(&CServer::ReceiveData, _pServer, std::ref(_pcPacketData));
	_eNetworkEntityType = SERVER;
	//_rNetwork.GetInstance().Initialise(_eNetworkEntityType);
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
			_pClient = static_cast<CClient*>(_rNetwork.GetInstance().GetNetworkEntity());
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

void NetworkingManager::StartUpNetwork()
{
	_rNetwork.GetInstance().Initialise(_eNetworkEntityType);
}
