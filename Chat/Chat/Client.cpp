// Chat.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ChatClient.h"


int main()
{
	SetConsoleTitle(L"MyChat");

	ChatClient *client = new ChatClient();

	char ip[15];
	char name[32];

	do
	{
		std::cout << "Enter server ip address: ";
		std::cin >> ip;

		std::cout << "Enter your name: ";
		std::cin >> name;
	
	} while (!client->connectChatServer(ip,name));

	delete client;

	system("pause");

    return 0;
}