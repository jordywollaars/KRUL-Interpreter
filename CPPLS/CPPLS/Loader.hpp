#ifndef LOADER_HPP
#define LOADER_HPP

#include "curl/curl.h"
#include <string>
#include <vector>
#include <sstream>

class Loader {
private:
	CURL* req;
	std::vector<std::string> CreateStackFromString(std::string content);
public:
	Loader();
	std::vector<std::string> LoadInstructionsFromURL(std::string url);

};

#endif //LOADER_HPP