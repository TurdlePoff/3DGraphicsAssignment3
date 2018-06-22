//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2015 Media Design School
//
// File Name	: server.cpp
// Description	: server implementation file.
// Author		: Vivian Ngo
// Mail			: vivian.ngo7572@mediadesign.school.nz
//

//Library Includes
#include <WS2tcpip.h>
#include <iostream>
#include <utility>
#include <thread>
#include <chrono>


//Local Includes
#include "utils.h"
#include "network.h"
#include "consoletools.h"
#include "socket.h"


//Local Includes
#include "server.h"

CServer::CServer()
	:m_pcPacketData(0),
	m_pServerSocket(0)
{
	ZeroMemory(&m_ClientAddress, sizeof(m_ClientAddress));
}

CServer::~CServer()
{
	delete m_pConnectedClients;
	m_pConnectedClients = 0;

	delete m_pServerSocket;
	m_pServerSocket = 0;

	delete m_pWorkQueue;
	m_pWorkQueue = 0;

	delete[] m_pcPacketData;
	m_pcPacketData = 0;
}

bool CServer::Initialise()
{
	m_pcPacketData = new char[MAX_MESSAGE_LENGTH];

	//Create a work queue to distribute messages between the main  thread and the receive thread.
	m_pWorkQueue = new CWorkQueue<char*>();

	//Create a socket object
	m_pServerSocket = new CSocket();

	//Get the port number to bind the socket to
	unsigned short _usServerPort = QueryPortNumber(DEFAULT_SERVER_PORT);

	//Initialise the socket to the local loop back address and port number
	if (!m_pServerSocket->Initialise(_usServerPort))
	{
		return false;
	}

	//Qs 2: Create the map to hold details of all connected clients
	m_pConnectedClients = new std::map < std::string, TClientDetails >();

	return true;
}

bool CServer::AddClient(std::string _strClientName)
{
	//Add the code to add a client to the map here...
	for (auto it = m_pConnectedClients->begin(); it != m_pConnectedClients->end(); ++it)
	{
		//Check to see that the client to be added does not already exist in the map, 
		if (it->first == ToString(m_ClientAddress))
		{
			return false;	//Exited server
		}
		//also check for the existence of the username
		else if (it->second.m_strName == _strClientName)
		{
			return false;
		}
	}
	//Add the client to the map.
	TClientDetails _clientToAdd;
	_clientToAdd.m_strName = _strClientName;
	_clientToAdd.m_ClientAddress = this->m_ClientAddress;

	std::string _strAddress = ToString(m_ClientAddress);
	m_pConnectedClients->insert(std::pair < std::string, TClientDetails >(_strAddress, _clientToAdd));
	return true;
}

bool CServer::SendData(char* _pcDataToSend)
{
	int _iBytesToSend = (int)strlen(_pcDataToSend) + 1;

	int iNumBytes = sendto(
		m_pServerSocket->GetSocketHandle(),				// socket to send through.
		_pcDataToSend,									// data to send
		_iBytesToSend,									// number of bytes to send
		0,												// flags
		reinterpret_cast<sockaddr*>(&m_ClientAddress),	// address to be filled with packet target
		sizeof(m_ClientAddress)							// size of the above address struct.
	);
	//iNumBytes;
	if (_iBytesToSend != iNumBytes)
	{
		std::cout << "There was an error in sending data from client to server" << std::endl;
		return false;
	}

	return true;
}

void CServer::ReceiveData(char* _pcBufferToReceiveData) //constantly listen and if pick up add to workqueue

{
	int iSizeOfAdd = sizeof(m_ClientAddress);
	int _iNumOfBytesReceived;
	int _iPacketSize;

	//Make a thread local buffer to receive data into
	char _buffer[MAX_MESSAGE_LENGTH];

	while (true)
	{

		// pull off the packet(s) using recvfrom()
		_iNumOfBytesReceived = recvfrom(			// pulls a packet from a single source...
			m_pServerSocket->GetSocketHandle(),						// client-end socket being used to read from
			_buffer,							// incoming packet to be filled
			MAX_MESSAGE_LENGTH,					   // length of incoming packet to be filled
			0,										// flags
			reinterpret_cast<sockaddr*>(&m_ClientAddress),	// address to be filled with packet source
			&iSizeOfAdd								// size of the above address struct.
		);
		if (_iNumOfBytesReceived < 0)
		{
			int _iError = WSAGetLastError();
			ErrorRoutines::PrintWSAErrorInfo(_iError);

			if (_iError == WSAECONNRESET)
			{
				std::string cUsername = "";

				for (auto it = m_pConnectedClients->begin(); it != m_pConnectedClients->end(); ++it)
				{
					if (ToString(it->second.m_ClientAddress) == ToString(this->m_ClientAddress))
					{
						cUsername = it->second.m_strName;
						m_pConnectedClients->erase(it);
						break;
					}
				}
			}
			//return false;
		}
		else
		{
			_iPacketSize = static_cast<int>(strlen(_buffer)) + 1;
			strcpy_s(_pcBufferToReceiveData, _iPacketSize, _buffer);
			char _IPAddress[100];
			inet_ntop(AF_INET, &m_ClientAddress.sin_addr, _IPAddress, sizeof(_IPAddress));

			std::string cUsername = "";

			for (auto it = m_pConnectedClients->begin(); it != m_pConnectedClients->end(); ++it)
			{
				if (ToString(it->second.m_ClientAddress) == ToString(this->m_ClientAddress))
					cUsername = it->second.m_strName;
			}

			//std::cout << "Server Received \"" << _pcBufferToReceiveData << "\" from " <<
			//	_IPAddress << ":" << ntohs(m_ClientAddress.sin_port) << std::endl;

			std::string userMessage = _pcBufferToReceiveData;
			std::string msgType = _pcBufferToReceiveData;
			msgType = msgType.substr(0, 1);
			userMessage = userMessage.substr(2);

			if (stoi(msgType) != KEEPALIVE)
			{
				if (cUsername == "")
				{
					std::cout << "[" << ToString(this->m_ClientAddress) << "]: \"" << userMessage << "\"" << std::endl;
				}
				else
				{
					std::cout << "	[" << cUsername << "]: \"" << userMessage << "\"" << std::endl;
				}
			}

			//Push this packet data into the WorkQ
			m_pWorkQueue->push(_pcBufferToReceiveData);
		}
		//std::this_thread::yield();

	} //End of while (true)
}

void CServer::GetRemoteIPAddress(char *_pcSendersIP)
{
	char _temp[MAX_ADDRESS_LENGTH];
	int _iAddressLength;
	inet_ntop(AF_INET, &(m_ClientAddress.sin_addr), _temp, sizeof(_temp));
	_iAddressLength = static_cast<int>(strlen(_temp)) + 1;
	strcpy_s(_pcSendersIP, _iAddressLength, _temp);
}

unsigned short CServer::GetRemotePort()
{
	return ntohs(m_ClientAddress.sin_port);
}

/**

* Sends keep alive messages to client when called in main every 5 seconds

**/
void CServer::SendKeepAlive()
{
	for (auto it = m_pConnectedClients->begin(); it != m_pConnectedClients->end(); ++it)
	{
		m_ClientAddress = it->second.m_ClientAddress;

		TPacket _packetToSend;
		_packetToSend.Serialize(KEEPALIVE, "HI");
		SendData(_packetToSend.PacketData);

	}
}

void CServer::ProcessData(char* _pcDataReceived)
{
	TPacket _packetRecvd, _packetToSend;
	_packetRecvd = _packetRecvd.Deserialize(_pcDataReceived);
	std::string userName = "SERVER>";
	std::string message = _packetRecvd.MessageContent;
	std::string clientList = "<ACTIVE CLIENTS>: ";

	//Search for username
	for (auto it = m_pConnectedClients->begin(); it != m_pConnectedClients->end(); ++it)
	{
		if (ToString(it->second.m_ClientAddress) == ToString(m_ClientAddress))
		{
			userName = it->second.m_strName;
		}
	}

	switch (_packetRecvd.MessageType)
	{
	case HANDSHAKE:
	{
		//Print message saying a handshake was made
		char _IPAddress[100];
		inet_ntop(AF_INET, &m_ClientAddress.sin_addr, _IPAddress, sizeof(_IPAddress));

		std::cout << "Server received a handshake message from: " << _IPAddress << std::endl;

		//Attempt to add a client to the server
		if (AddClient(_packetRecvd.MessageContent))
		{
			//Find the username
			for (auto it = m_pConnectedClients->begin(); it != m_pConnectedClients->end(); ++it)
			{
				if (ToString(it->second.m_ClientAddress) == ToString(m_ClientAddress))
				{
					//Set it to a variable
					userName = it->second.m_strName;
				}
			}

			//Send a welcome message
			_packetToSend.Serialize(DATA, (char*)("Welcome to the server " + userName).c_str());
			SendData(_packetToSend.PacketData);

			//Display all active clients for the user that just joined
			std::string clientList = "<ACTIVE CLIENTS>: ";

			//Combine all client names into one string
			for (auto it = m_pConnectedClients->begin(); it != m_pConnectedClients->end(); ++it)
			{
				clientList += it->second.m_strName;
				clientList += ", ";
			}
			std::cout << clientList << std::endl;	//Print the list to server console

													//Send the client list string to the client
			_packetToSend.Serialize(DATA, (char*)clientList.c_str());
			SendData(_packetToSend.PacketData);

			//Tell the rest of the clients on server that a new client has joined
			message += " has joined the server.";

			for (auto it = m_pConnectedClients->begin(); it != m_pConnectedClients->end(); ++it)
			{
				if (it->first == ToString(m_ClientAddress))
					continue;	//Skip the current user in for loop

				m_ClientAddress = it->second.m_ClientAddress;

				_packetToSend.Serialize(DATA, (char*)message.c_str());
				SendData(_packetToSend.PacketData);
			}
		}
		else
		{
			//Tell client that they were not added to the server
			_packetToSend.Serialize(HANDSHAKE, "Failed to add client.");
			SendData(_packetToSend.PacketData);
		}
		break;
	}
	case DATA:
	{
		//Print out message received with a username
		message = "[" + userName + "]: " + message;

		//Iterate through client list and send to all clients
		for (auto it = m_pConnectedClients->begin(); it != m_pConnectedClients->end(); ++it)
		{
			m_ClientAddress = it->second.m_ClientAddress;

			_packetToSend.Serialize(DATA, (char*)message.c_str());
			SendData(_packetToSend.PacketData);
		}

		break;
	}
	case BROADCAST:
	{
		std::cout << "Received a broadcast packet" << std::endl;
		//Just send out a packet to the back to the client again which will have the server's IP and port in it's sender fields
		_packetToSend.Serialize(BROADCAST, "I'm here!");
		SendData(_packetToSend.PacketData);
		break;
	}
	case QUIT:
	{
		m_pConnectedClients->erase(ToString(m_ClientAddress));
		//Tell the rest of the clients on server that a new client has joined
		message = "User: <" + userName + "> has left the server";

		for (auto it = m_pConnectedClients->begin(); it != m_pConnectedClients->end(); ++it)
		{
			if (it->first == ToString(m_ClientAddress))
				continue;	//Skip item in for loop

			m_ClientAddress = it->second.m_ClientAddress;

			clientList += it->second.m_strName;
			clientList += ", ";
		}

		//m_ClientAddress = m_pConnectedClients->begin()->second.m_ClientAddress;

		//Send message and client list
		_packetToSend.Serialize(DATA, (char*)message.c_str());
		SendData(_packetToSend.PacketData);

		_packetToSend.Serialize(DATA, (char*)clientList.c_str());
		SendData(_packetToSend.PacketData);
		break;
	}
	case CLIST:
	{
		//Send client list to user
		for (auto it = m_pConnectedClients->begin(); it != m_pConnectedClients->end(); ++it)
		{
			clientList += it->second.m_strName;
			clientList += ", ";
		}
		_packetToSend.Serialize(DATA, (char*)clientList.c_str());
		SendData(_packetToSend.PacketData);
		break;
	}
	case KEEPALIVE:
	{
		for (auto it = m_pConnectedClients->begin(); it != m_pConnectedClients->end(); ++it)
		{
			if (ToString(it->first) == ToString(m_ClientAddress))
				userName = it->second.m_strName;
		}

		std::cout << "	[" << userName << "]: \"" << "[IS ALIVE]" << "\"" << std::endl;
		break;
	}
	default:
		break;
	}

}

CWorkQueue<char*>* CServer::GetWorkQueue()
{
	return m_pWorkQueue;
}
