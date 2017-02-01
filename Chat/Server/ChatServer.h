#pragma once
class ChatServer
{
private:
	char ip[32];


public:
	ChatServer();
	~ChatServer();

	char* getIP();
};

