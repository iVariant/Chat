#include "stdafx.h"
#include "ChatClient.h"


ChatClient::ChatClient()
{
}


ChatClient::~ChatClient()
{
}


int ChatClient::connectChatServer(char ip[15], char name[32])
{
	WORD wVersionRequested = MAKEWORD(2, 2);
	WSADATA wsaData;

	WSAStartup(wVersionRequested, &wsaData);

	struct sockaddr_in peer;
	peer.sin_family = AF_INET;
	peer.sin_port = htons(1280);


	peer.sin_addr.s_addr = inet_addr(ip);


	if (INVALID_SOCKET == (socketLocal = socket(AF_INET, SOCK_STREAM, 0)))
	{
		printf("Client> Error! INVALID_SOCKET!\n");
		return 0;
	}


	if (SOCKET_ERROR == (connect(socketLocal, (sockaddr *)&peer, sizeof(peer))))
	{
		printf("Client> Error! SOCKET_ERROR!\n");
		return 0;
	}


	wchar_t strTitleIp[50] = L"Connected ";
	wchar_t wcsServerIP[32] = L"\0";

	MultiByteToWideChar(0, 0, ip, 32, wcsServerIP, 32);
	wcscat_s(strTitleIp, wcsServerIP);

	SetConsoleTitle(strTitleIp);



	char bufferText[1024];
	char bufferSend[1024];

	
	bufferSend[0] = '\0'; strcat_s(bufferSend, name); strcat_s(bufferSend, " connected!");
	send(socketLocal, bufferSend, sizeof(bufferSend), 0);

	while (true)
	{
	
		std::cout << "say> ";
		std::cin >> bufferText;

		bufferSend[0] = '\0';
		strcat_s(bufferSend, name); strcat_s(bufferSend, ": "); strcat_s(bufferSend, bufferText);
		
	
		send(socketLocal, bufferSend, sizeof(bufferSend), 0);

		if (recv(socketLocal, bufferSend, sizeof(bufferSend), 0) < 0)
		{
			printf("Server>Disconect!");
			break;
		}
		else
		{
			printf("%s \n", bufferSend);
		}

		Sleep(99);
	}


	disconnectChatServer();


	return 1;
}


int ChatClient::disconnectChatServer()
{
	closesocket(socketLocal);
	WSACleanup();
	std::cout << "Client> Close socket!\n";
	return 1;
}


