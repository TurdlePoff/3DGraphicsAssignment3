//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2015 Media Design School
//
// File Name	: main.cpp
// Description	: main declaration file.
// Author		: Vivian Ngo
// Mail			: vivian.ngo7572@mediadesign.school.nz
//

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

// make sure the winsock lib is included...
#pragma comment(lib,"ws2_32.lib")

int main()
{
	CControl::ChangeWindowSize(700, 900);

	char* _pcPacketData = 0; //A local buffer to receive packet data info
	_pcPacketData = new char[MAX_MESSAGE_LENGTH];
	strcpy_s(_pcPacketData, strlen("") + 1, "");

	char _cIPAddress[MAX_ADDRESS_LENGTH]; // An array to hold the IP Address as a string
										  //ZeroMemory(&_cIPAddress, strlen(_cIPAddress));

	unsigned char _ucChoice;
	EEntityType _eNetworkEntityType;
	CInputLineBuffer _InputBuffer(MAX_MESSAGE_LENGTH);
	std::thread _ClientReceiveThread, _ServerReceiveThread;

	//Get the instance of the network
	CNetwork& _rNetwork = CNetwork::GetInstance();
	_rNetwork.StartUp();

	//A pointer to hold a client instance
	CClient* _pClient = nullptr;
	//A pointer to hold a server instance
	CServer* _pServer = nullptr;

	//Initialize clock
	auto startTime = std::chrono::system_clock::now();
	auto endTime = std::chrono::system_clock::now();
	// query, is this to be a client or a server?
	_ucChoice = QueryOption("Do you want to run a client or server (C/S)? ", "CS");
	switch (_ucChoice)
	{
		case 'C':
		{
			_eNetworkEntityType = CLIENT;
			break;
		}
		case 'S':
		{
			_eNetworkEntityType = SERVER;
			break;
		}
		default:
		{
			std::cout << "This is not a valid option." << std::endl;
			return 0;
			break;
		}
	}

	if (!_rNetwork.GetInstance().Initialise(_eNetworkEntityType))
	{
		std::cout << "Unable to initialise the Network........Press any key to continue......";
		_getch();
		return 0;
	}

	//Run receive on a separate thread so that it does not block the main client thread.
	if (_eNetworkEntityType == CLIENT) //if network entity is a client
	{

		_pClient = static_cast<CClient*>(_rNetwork.GetInstance().GetNetworkEntity());
		_ClientReceiveThread = std::thread(&CClient::ReceiveData, _pClient, std::ref(_pcPacketData));
	}

	//Run receive of server also on a separate thread 
	else if (_eNetworkEntityType == SERVER) //if network entity is a server
	{

		_pServer = static_cast<CServer*>(_rNetwork.GetInstance().GetNetworkEntity());
		_ServerReceiveThread = std::thread(&CServer::ReceiveData, _pServer, std::ref(_pcPacketData));
		startTime = std::chrono::system_clock::now();

	}

	while (_rNetwork.IsOnline())
	{
		if (_eNetworkEntityType == CLIENT) //if network entity is a client
		{
			_pClient = static_cast<CClient*>(_rNetwork.GetInstance().GetNetworkEntity());

			//Prepare for reading input from the user
			_InputBuffer.PrintToScreenTop();

			//Get input from the user
			if (_InputBuffer.Update())
			{
				// we completed a message, lets send it:
				int _iMessageSize = static_cast<int>(strlen(_InputBuffer.GetString()));

				std::string msg = _InputBuffer.GetString();
				TPacket _packet;

				//Checks if message is a command
				if (msg != "")
				{
					if (msg.at(0) == '!')
					{
						//If there is just a single ! exclamation mark
						if (strlen(_InputBuffer.GetString()) == 1)
						{
							//Send it as data
							_packet.Serialize(DATA, const_cast<char*>(_InputBuffer.GetString())); //Hardcoded username; change to name as taken in via user input.
							_rNetwork.GetInstance().GetNetworkEntity()->SendData(_packet.PacketData);
						}
						else
						{
							std::string commandReply = "!";
							switch (msg.at(1))
							{
							case '?':
							{
								std::cout << "List of commands: "
									<< std::endl << "   !? - Display list of Commands"
									<< std::endl << "   !q - Quit server"
									<< std::endl << "   !c - Display list of active clients" << std::endl;
								break;
							}
							case 'q':
							{
								_packet.Serialize(QUIT, "---Exiting Server---"); //Hardcoded username; change to name as taken in via user input.
								_rNetwork.GetInstance().GetNetworkEntity()->SendData(_packet.PacketData);
								_rNetwork.ShutDown();
								exit(0);
								break;
							}
							case 'c':
							{
								_packet.Serialize(CLIST, "Requesting Client List"); //Hardcoded username; change to name as taken in via user input.
								_rNetwork.GetInstance().GetNetworkEntity()->SendData(_packet.PacketData);
								break;
							}
							default:
								//Send whatever else that was inputted as data
								_packet.Serialize(DATA, const_cast<char*>(_InputBuffer.GetString())); //Hardcoded username; change to name as taken in via user input.
								_rNetwork.GetInstance().GetNetworkEntity()->SendData(_packet.PacketData);
								break;
							}
						}

					}
					else
					{
						//Put the message into a packet structure
						_packet.Serialize(DATA, const_cast<char*>(_InputBuffer.GetString())); //Hardcoded username; change to name as taken in via user input.
						_rNetwork.GetInstance().GetNetworkEntity()->SendData(_packet.PacketData);
						//Clear the Input Buffer
						//Print To Screen Top
						_InputBuffer.PrintToScreenTop();
					}
				}
				_InputBuffer.ClearString();

			}
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
		else //if you are running a server instance
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

				//ADD
				endTime = std::chrono::system_clock::now();
				std::chrono::milliseconds timeSince = std::chrono::duration_cast<std::chrono::milliseconds> (endTime - startTime);
				std::chrono::seconds thrty(5); //Test with 5 seconds first

				if (timeSince >= thrty)
				{
					_pServer->SendKeepAlive();

					startTime = std::chrono::system_clock::now();
					endTime = std::chrono::system_clock::now();

				}
			}
		}
	} //End of while network is Online

	_ClientReceiveThread.join();
	_ServerReceiveThread.join();

	//Shut Down the Network
	_rNetwork.ShutDown();
	_rNetwork.DestroyInstance();

	delete[] _pcPacketData;
	return 0;
}