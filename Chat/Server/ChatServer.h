#pragma once
class ChatServer
{
private:
	char ip[32];

	SOCKET s;
	WORD wVersionRequested;
	WSADATA wsaData;

	struct sockaddr_in local;

public:
	ChatServer();
	~ChatServer();

	char* getIP();
	int Initialization();
	int close();
};

