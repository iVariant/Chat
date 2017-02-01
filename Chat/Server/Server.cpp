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

	





	system("pause");

	delete serv;
    return 0;
}

