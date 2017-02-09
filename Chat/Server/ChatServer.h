#pragma once

class ChatServer
{
private:
	char ip[15];

	SOCKET server;

	static DWORD WINAPI sendMessageToClient(LPVOID param);
	int countClient;

public:

	ChatServer();
	~ChatServer();

	char* getIP();
	int Initialization();
	int close();
	int run();

};

