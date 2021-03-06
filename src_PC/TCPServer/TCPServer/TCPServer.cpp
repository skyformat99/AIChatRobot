// TCPServer.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <winsock.h>
#include <iostream>
#pragma comment(lib,"ws2_32.lib")
#define BUF_SIZE 6

using namespace std;

int main()
{
	SOCKET sServer;        //服务器套接字
	SOCKET sClient;        //客户端套接字
	SOCKADDR_IN addrServ;;        //服务器地址
	int retVal;
	char buf[BUF_SIZE];


	WORD myVersionRequest;
	WSADATA wsaData;
	myVersionRequest = MAKEWORD(1, 1);
	int err;
	err = WSAStartup(myVersionRequest, &wsaData);
	if (!err)
	{
		printf("已打开套接字\n");
	}
	else
	{
		//进一步绑定套接字
		printf("嵌套字未打开!");
		return 1;
	}


	//创建套接字
	sServer = socket(AF_INET, SOCK_STREAM, 0);

	//服务器套接字地址 
	addrServ.sin_family = AF_INET;
	addrServ.sin_port = htons(8989);
	addrServ.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	//绑定套接字
	retVal = bind(sServer, (SOCKADDR*)&addrServ, sizeof(SOCKADDR));

	//开始监听 
	retVal = listen(sServer, 1);

	//接受客户端请求
	sockaddr_in addrClient;
	int addrClientlen = sizeof(SOCKADDR);
	sClient = accept(sServer, (SOCKADDR*)&addrClient, &addrClientlen);
	printf("收到客户端请求");

	//接收客户端数据
	ZeroMemory(buf, BUF_SIZE);
	retVal = recv(sClient, buf, 7, 0);
	cout << buf << endl;

	//退出
	closesocket(sServer);    //关闭套接字
	closesocket(sClient);    //关闭套接字
	WSACleanup();            //释放套接字资源;

	system("pause");
    return 0;
}

