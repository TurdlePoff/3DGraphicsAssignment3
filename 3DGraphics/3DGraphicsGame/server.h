//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2015 Media Design School
//
// File Name	: server.h
// Description	: server declaration file.
// Author		: Vivian Ngo
// Mail			: vivian.ngo7572@mediadesign.school.nz
//

#ifndef __SERVER_H__
#define __SERVER_H__

// Library Includes
#include <Windows.h>
#include <map>
#include <time.h>

// Local Includes
#include "networkentity.h"
#include "WorkQueue.h"

// Types

// Constants

//Forward Declaration
class CSocket;

//Structure to hold the details of all connected clients
struct TClientDetails
{
	sockaddr_in m_ClientAddress;
	//bool m_bIsActive;
	std::string m_strName;
	//time_t m_timeOfLastMessage;
	bool isOnline;
};

class CServer : public INetworkEntity
{
public:
	// Default Constructors/Destructors
	CServer();
	~CServer();

	bool waitingForClientAlive;

	// Virtual Methods from the Network Entity Interface.
	virtual bool Initialise(); //Implicit in the intialization is the creation and binding of the socket
	virtual bool SendData(char* _pcDataToSend);
	virtual void ReceiveData(char* _pcBufferToReceiveData);
	virtual void ProcessData(char* _pcDataReceived);
	virtual void GetRemoteIPAddress(char* _pcSendersIP);
	virtual unsigned short GetRemotePort();
	void SendKeepAlive();

	CWorkQueue<char*>* GetWorkQueue();
	//Qs 2: Function to add clients to the map.
private:
	bool AddClient(std::string _strClientName);



private:
	//A Buffer to contain all packet data for the server
	char* m_pcPacketData;
	//A server has a socket object to create the UDP socket at its end.
	CSocket* m_pServerSocket;
	// Make a member variable to extract the IP and port number of the sender from whom we are receiving
	//Since it is a UDP socket capable of receiving from multiple clients; these details will change depending on who has sent the packet we are currently processing.
	sockaddr_in m_ClientAddress; 

	//Qs 2 : Make a map to hold the details of all the client who have connected. 
	//The structure maps client addresses to client details
	std::map<std::string, TClientDetails>* m_pConnectedClients;

	//A workQueue to distribute messages between the main thread and Receive thread.
	CWorkQueue<char*>* m_pWorkQueue;

	std::chrono::system_clock::time_point startTime = std::chrono::system_clock::now();
	std::chrono::system_clock::time_point endTime = std::chrono::system_clock::now();

	std::vector<bool> clientsOnline;
};

#endif