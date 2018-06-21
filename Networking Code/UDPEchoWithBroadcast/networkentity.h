//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2015 Media Design School
//
// File Name	: client.h
// Description	: client declaration file.
// Author		: Vivian Ngo
// Mail			: vivian.ngo7572@mediadesign.school.nz
//

#ifndef __NETWORKENTITY_H__
#define __NETWORKENTITY_H__

#include <string>
#include <sstream>
#include "stdafx.h"

enum EMessageType : unsigned char
{
	HANDSHAKE,
	DATA,
	KEEPALIVE,
	QUIT,
	CLIST,
	BROADCAST,
	STARTKA,
	VECTOR4,
	VECTOR3
};

struct TPacket 
{
	unsigned short MessageType;
	char MessageContent[50];
	char PacketData[60];
	unsigned short PacketSize;

	//void set_packet(short _x, short _y, WORD _object_type, short _object_index, WORD _param)
	
	//Basically create a packet
	void Serialize(EMessageType _MessageType, char* _message)
	{
		MessageType = _MessageType;	//Set messagetype
		strcpy_s(MessageContent, strlen(_message) + 1, _message); //Copy over the message to check

		std::ostringstream oss;
		oss << MessageType;
		oss << " ";
		oss << MessageContent;
		
		std::string _strToSend = oss.str();			//String to send is message type and content combined
		const char* _pcToSend = _strToSend.c_str();	//Convert string to Packet to send

		strcpy_s(PacketData, strlen(_pcToSend) + 1, _pcToSend);	//Copy over packet into packet data

		PacketSize = static_cast<unsigned short>(_strToSend.size());	//Packet size is determined by string size
	}

	//vector version
	void Serialize(EMessageType _MessageType, glm::vec3 _message)
	{
		// Serialise a vector

		//....add code here...

	}
	
	//Decode a packet
	TPacket Deserialize(char* _PacketData)
	{
		std::string _strTemp(_PacketData);
		std::istringstream iss(_strTemp);
		
		iss >> this->MessageType;
		
		//iss >> this->MessageContent;
		std::string _tempMessageBuffer;
		getline(iss, _tempMessageBuffer);
		_tempMessageBuffer = _tempMessageBuffer.substr(1);
		strcpy_s(MessageContent, _tempMessageBuffer.length() + 2, _tempMessageBuffer.c_str());
		
		return *this;
	}

};

class INetworkEntity
{
public:
	virtual bool Initialise() = 0; //Implicit in the intialization is the creation and binding of the socket
	virtual bool SendData(char* _pcDataToSend) = 0;
	virtual void ReceiveData(char* _pcBufferToReceiveData) = 0;
	virtual void GetRemoteIPAddress(char *_pcSendersIP) = 0;
	virtual unsigned short GetRemotePort() = 0;
	virtual ~INetworkEntity() {};

protected:
	//Additional state variable to indicate whether a network entity is online or not
	bool m_bOnline;
};
#endif 