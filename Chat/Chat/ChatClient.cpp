#include "stdafx.h"
#include "ChatClient.h"


ChatClient::ChatClient()
{
}

ChatClient::~ChatClient()
{
	disconnectChatServer();
}

static char ClientName[32];

int ChatClient::connectChatServer(char ip[15], char name[32])
{
	WORD wVersionRequested = MAKEWORD(2, 2);
	WSADATA wsaData;

	WSAStartup(wVersionRequested, &wsaData);

	struct sockaddr_in peer;
	peer.sin_family = AF_INET;
	peer.sin_port = htons(1280);


	peer.sin_addr.s_addr = inet_addr(ip);


	if (INVALID_SOCKET == (client = socket(AF_INET, SOCK_STREAM, 0)))
	{
		printf("Client> Error! INVALID_SOCKET!\n");
		return 0;
	}


	if (SOCKET_ERROR == (connect(client, (sockaddr *)&peer, sizeof(peer))))
	{
		printf("Client> Error! SOCKET_ERROR!\n");
		return 0;
	}


	wchar_t strTitleIp[50] = L"Connected ";
	wchar_t wcsServerIP[32] = L"\0";

	MultiByteToWideChar(0, 0, ip, 32, wcsServerIP, 32);
	wcscat_s(strTitleIp, wcsServerIP);

	SetConsoleTitle(strTitleIp);


	char bufferSend[1024];

	ClientName[0] = '\0'; strcat_s(ClientName, name);
	
	SOCKET connect;
	int recvFromServer;

	while (true)
	{
		memset(bufferSend, '\0', sizeof bufferSend);
		HANDLE thread = CreateThread(NULL, 0, sendMessageToServer, (LPVOID)client, 0, NULL);

		if (connect = accept(client, NULL, NULL))
		{
			static int countErrorRecv = 0;

			recvFromServer = recv(client, bufferSend, sizeof(bufferSend), 0);

			if (recvFromServer > 0)
			{
				printf("\r%80c\r", ' '); std::cout << bufferSend << std::endl;
			}
			else if (recvFromServer == 0)
			{
				printf("\r%80c\r", ' '); std::cout << "Client> Connection closed!\n";
				break;
			}
			else if (recvFromServer < 0 && countErrorRecv < 5)
			{				
				countErrorRecv++;
				printf("\r%80c\r", ' '); printf("Client> recv failed %d\n", WSAGetLastError());	
			}
			else
			{
				printf("\r%80c\r", ' '); std::cout << "Client> Failed connection to server!";				
				countErrorRecv = 0;
				break;
			}
	
		}

		Sleep(99);
	}

	return 1;
}

DWORD ChatClient::sendMessageToServer(LPVOID param)
{
	char bufferSendToServer[1024] = {'\0'};
	char bufferText[1024] = { '\0' };

	std::cout << "say> ";
	std::cin.getline(bufferText,1024);
	
	strcat_s(bufferSendToServer, ClientName); strcat_s(bufferSendToServer, ": "); strcat_s(bufferSendToServer, bufferText);

	send((SOCKET)param, bufferSendToServer, sizeof(bufferSendToServer), 0);

	return 0;
}

int ChatClient::disconnectChatServer()
{
	closesocket(client);
	WSACleanup();
	printf("\r%80c\r", ' '); std::cout << "Client> disconnect from chat server!\n";	
	return 1;
}


