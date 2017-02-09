// Server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ChatServer.h"

int main()
{
	wchar_t wcsConsoleTitle[64] = L"Server ";
	wchar_t wcsServerIP[32] = L"\0";

	ChatServer *serv = new ChatServer();
	
	MultiByteToWideChar(0, 0, serv->getIP(), 32, wcsServerIP, 32);
	wcscat_s(wcsConsoleTitle, wcsServerIP);
	SetConsoleTitle(wcsConsoleTitle);


	int countInitialization = 0;
	do
	{
		countInitialization++;
		if (countInitialization > 5)
		{
			std::cout << "Server> exit \n";
			system("pause");
			delete serv;
			return 0;
		}
		std::cout << "Server> Try Initialization... \n";
	} while (!serv->Initialization());
	
	
	serv->run();


	std::cout << "Server> Close... \n";
	if (serv->close())
	{
		std::cout << "Server> OK \n";
	}

	system("pause");

	delete serv;
    return 0;
}

