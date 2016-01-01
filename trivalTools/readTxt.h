#ifndef READTXT_H
#define READTXT_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>

std::vector<std::string> 
readStringInTxt(const std::string &path)
{
	std::vector<std::string> retStr;
	std::ifstream input(path);
	std::string tmpStr;
	while(input >> tmpStr)
		retStr.push_back(tmpStr);
	input.close();
	return retStr;	
}

std::vector<std::string> 
readStringInTerminal()
{
	std::vector<std::string> retStr;
	std::string oneLine;
	std::string tmpString;
	while(std::cin >> oneLine)
	{
		std::istringstream strStream(oneLine);
		while(strStream >> tmpString)
			retStr.push_back(tmpString);		
	}
	
	return retStr;
}

#endif

