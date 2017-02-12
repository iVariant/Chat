#pragma once

class ChatClient
{

private:

	SOCKET client;


	static DWORD WINAPI sendMessageToServer(LPVOID param);

public:
	ChatClient();
	~ChatClient();

	int connectChatServer(char ip[15], char name[32]);
	int disconnectChatServer();
	
};

