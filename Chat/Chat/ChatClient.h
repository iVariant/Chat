#pragma once

class ChatClient
{
private:
	char serverIP[15];

	SOCKET socketLocal;


public:
	ChatClient();
	~ChatClient();

	int connectChatServer(char ip[15], char name[32]);
	int disconnectChatServer();

};

