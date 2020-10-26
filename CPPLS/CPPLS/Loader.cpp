#include "Loader.h"
#include <iostream>

Loader::Loader()
{
}

size_t WriteCallback(char* contents, size_t size, size_t nmemb, void* userp)
{
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

std::vector<std::string> Loader::LoadInstructionsFromURL(std::string url)
{
	this->req = curl_easy_init();
	CURLcode res;
	std::string readBuffer;

	if (req)
	{
		curl_easy_setopt(req, CURLOPT_URL, url.c_str());
		curl_easy_setopt(req, CURLOPT_FOLLOWLOCATION, 1L);
		curl_easy_setopt(req, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(req, CURLOPT_WRITEDATA, &readBuffer);
		res = curl_easy_perform(req);

		if (res != CURLE_OK)
		{
			fprintf(stderr, "curl_easy_operation() failed : %s\n", curl_easy_strerror(res));
		}
	}

	curl_easy_cleanup(req);

	std::cout << readBuffer << std::endl;
	
	return this->CreateStackFromString(readBuffer);
}

std::vector<std::string> Loader::CreateStackFromString(std::string content)
{
	std::vector<std::string> instructions;

	std::stringstream ss(content);
	std::string line;
	std::vector<std::string> temp;

	while (std::getline(ss, line))
	{
		instructions.push_back(line);
	}

	while (!temp.empty())
	{
		instructions.push_back(temp.back());
		temp.pop_back();
	}

	return instructions;
}
