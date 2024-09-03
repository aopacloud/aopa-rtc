#pragma once
#include <string>
class HttpClient
{
public:
	static std::string post(const std::string& url, const std::string& param);
};

