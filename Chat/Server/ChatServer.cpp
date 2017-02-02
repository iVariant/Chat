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

int ChatServer::Initialization()
{
	// Max version WinSock
	wVersionRequested = MAKEWORD(2, 2);

	//Initialization WinSock API
	if (WSAStartup(wVersionRequested, &wsaData)) 
	{ 
		std::cout << "Error Initialization!\n";
		return 0; 
	}

	s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	local.sin_family = AF_INET;
	local.sin_port = htons(1280);
	local.sin_addr.s_addr = htonl(INADDR_ANY); //physical ip address

	if (bind(s, (struct sockaddr*)&local, sizeof(local)) == -1) //ip + port
	{
		std::cout << "Server: Binding error!";
		closesocket(s);
		WSACleanup();
		return 0;
	}

	if (listen(s, 100) == -1)
	{
		std::cout << "Server: Error listening!";
		closesocket(s);
		WSACleanup();
		return 0;
	}

	return 1;
}

int ChatServer::close()
{
	closesocket(s);
	WSACleanup();
	return 1;
}

ChatServer::ChatServer()
{
}

ChatServer::~ChatServer()
{
}


