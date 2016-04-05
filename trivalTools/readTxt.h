#ifndef READTXT_H
#define READTXT_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

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

void splitString(const std::string &str, std::vector<std::string> &vecOfStr, char c = ' ')
{
	char chrIn;
	std::istringstream strStream(str);
	std::string strBuffer = "";
	while((chrIn = strStream.get()))
	{
		if(chrIn == c || chrIn == '\n' || chrIn == EOF)
		{
			if(!strBuffer.empty())
			{
				vecOfStr.push_back(strBuffer);
				strBuffer.clear();
			}
			if(chrIn == EOF)
				break;
		}	
		else
			strBuffer.insert(strBuffer.end(), chrIn);	
	}
}


void splitStr2Int(const std::string &str, std::vector<int> &vecInt, char c = ' ')
{
	std::vector<std::string> vecStr;
	splitString(str, vecStr, c);
	for(const auto &str : vecStr)
		vecInt.push_back(std::stoi(str));	
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

