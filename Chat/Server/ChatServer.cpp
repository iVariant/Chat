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
	WORD wVersionRequested = MAKEWORD(2, 2);
	WSADATA wsaData;
	struct sockaddr_in local;

	//Initialization WinSock API
	if (WSAStartup(wVersionRequested, &wsaData)) 
	{ 
		std::cout << "Server> Error Initialization!\n";
		return 0; 
	}

	if (INVALID_SOCKET == (server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)))
	{
		std::cout << "Server> Binding error!";
		closesocket(server);
		WSACleanup();
		return 0;
	}

	local.sin_family = AF_INET;
	local.sin_port = htons(1280);
	local.sin_addr.s_addr = htonl(INADDR_ANY); //physical ip address

	if (bind(server, (struct sockaddr*)&local, sizeof(local)) == -1) //ip + port
	{
		std::cout << "Server> Binding error!";
		closesocket(server);
		WSACleanup();
		return 0;
	}

	if (listen(server, 100) == -1)
	{
		std::cout << "Server> Error listening!";
		closesocket(server);
		WSACleanup();
		return 0;
	}

	std::cout << "Server> Start! \n";
	return 1;
}

int ChatServer::close()
{
	std::cout << "Server> Close!";
	closesocket(server);
	WSACleanup();
	return 1;
}


static SOCKET clientConnections[100];

int ChatServer::run()
{
	SOCKET connect;

	countClient = 0;
	memset(clientConnections, 0, sizeof clientConnections); // clear array


	std::cout << "Server> Run \n";

	while (true)
	{
		if (connect = accept(server, NULL, NULL))
		{
			
			clientConnections[countClient] = connect;
			send(clientConnections[countClient], "Connecting...\n", strlen("Connecting...\n"), NULL);
			countClient++;
			std::cout << "Server> Client " << countClient << " connected \n";
			HANDLE thread = CreateThread(NULL, 0, sendMessageToClient, (LPVOID)countClient, 0, NULL);
		}
		Sleep(99);
	}


	return 1;
}


DWORD ChatServer::sendMessageToClient(LPVOID param)
{
	char buffer[1024];
	while(true)
	{
		memset(buffer, '\0', sizeof(buffer));
		if (recv(clientConnections[(int)param-1], buffer, 1024, NULL)) // here
		{
			std::cout << buffer << std::endl;
			for (int i = 0; i <= (int)param; i++)
			{
				send(clientConnections[i], buffer, strlen(buffer), NULL);
			}
		}
	}
	return 0;
}

ChatServer::ChatServer()
{
}

ChatServer::~ChatServer()
{
	close();
}


