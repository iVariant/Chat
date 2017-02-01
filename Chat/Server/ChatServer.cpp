#include "stdafx.h"
#include "ChatServer.h"


char* ChatServer::getIP()
{
	const int WSVer = 0x101;
	WSAData wsaData;
	hostent *h;
	char Buf[128];


	if (WSAStartup(WSVer, &wsaData) == 0)
	{
		if (gethostname(&Buf[0], 128) == 0)
		{
			h = gethostbyname(&Buf[0]);
		}
		WSACleanup();
	}

	if (h == NULL) 
	{
		std::cout << "ip address is not defined!";
		return NULL; 
	}
	else
	{
		strcpy_s(ip, inet_ntoa(*(reinterpret_cast<in_addr *>(*(h->h_addr_list)))));	
		std::cout << "Your ip address: " << ip << std::endl;
		return ip;
	}
}

ChatServer::ChatServer()
{
}


ChatServer::~ChatServer()
{
}


