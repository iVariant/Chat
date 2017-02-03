#pragma once
class ChatServer
{
private:
	char ip[32];

	SOCKET socketLocal;

	WORD wVersionRequested;
	WSADATA wsaData;

	struct sockaddr_in local;


public:
	ChatServer();
	~ChatServer();

	char* getIP();
	int Initialization();
	int close();
	int run();
};

