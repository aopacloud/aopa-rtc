#include "HttpClient.h"
#include <winsock2.h>
#include <iostream>


bool getAddress(const std::string& url, std::string& host, int& port, std::string& path) {
	char ip[128] = { 0 };
	int port16 = 0;
	char channel[128] = { 0 };
	if (url.size() >= 128) {
		return false;
	}
	if (false) {}
	else if (sscanf(url.c_str(), "http://%[^:/]:%d/%s", ip, &port16, channel) == 3) {
		
	}
	else if (sscanf(url.c_str(), "http://%[^:/]/%s", ip, channel) == 2) {
		port16 = 80;
	}
	else if (sscanf(url.c_str(), "http://%[^:/]:%d", ip, &port16) == 2) {
		channel[0] = '\0';
	}
	else if (sscanf(url.c_str(), "http://%[^:/]", ip) == 1) {
		port16 = 80;
		channel[0] = '\0';
	}
	else {
		return false;
	}
	host = ip;
	port = port16;
	path = "/" + (std::string)channel;
	return true;
}
std::string HttpClient::post(const std::string& url, const std::string& param) {
	std::string ret;
	WSADATA wsaData;
	//WSAStartup(MAKEWORD(2, 2), &wsaData);
	std::string host;
	std::string path;
	int port;
	if (!getAddress(url, host, port, path))
		return ret;

	//地址与端口参数
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = inet_addr(host.c_str());
	//初始化socket
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == SOCKET_ERROR) {
		return ret;
	}
	//连接服务器
	int connectStatus = connect(sock, (const struct sockaddr*)&sin, sizeof(sin));
	if (connectStatus == INVALID_SOCKET) {
		return ret;
	}
	//初始化发送的数据
	std::string data = "";
	data += "POST " + path + " HTTP/1.1\r\n";
	//HEADER信息
	data += "Host: " + host + "\r\n";
	data += "Connection: keep-alive\r\n";
	data += "Content-Length: " + std::to_string(param.length());
	data += "\r\n";
	data += "Cache-Control: max-age=0\r\n";
	data += "Upgrade-Insecure-Requests: 1\r\n";
//	data += "User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/69.0.3497.100 Safari/537.36\r\n";
	data += "Content-Type:  application/x-www-form-urlencoded\r\n";
//	data += "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8\r\n";
//	data += "Accept-Encoding: gzip, deflate, br\r\n";
//	data += "Accept-Language: zh-CN,zh;q=0.9\r\n";
	//内容信息
	data += "\r\n";
	data += param;

	//将string转为c字符串，不然请求会失败
	int len = data.length() + 1;
	char* content = new char[len];
	memset(content, 0, len);
	strcpy(content, data.c_str());

	//发送请求
	int index = 0;
	while (index < len){
		int sendStatus = ::send(sock, content + index, len - index, 0);
		if (sendStatus == -1) {
			delete[] content;
			return ret;
		}
		index += sendStatus;
	}
	

	//获取返回的信息
	char recvStr[4096] = { 0 };
	memset(recvStr, 0, 4096);
	int recvStatus = 0;
	recvStatus = ::recv(sock, recvStr, 4096, 0);
	if (recvStatus == -1) {
		delete[] content;
		return ret;
	}
	ret = recvStr;
	closesocket(sock);
	//WSACleanup();
	return ret;
}