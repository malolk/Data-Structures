#include <iostream>
#include "../trivalTools/readTxt.h"
#include "HashSep.h"
#include <vector>
#include <string>

int main()
{
	auto hTble = HashSepTable(15);
	std::vector<std::string> input = readStringInTerminal();
	
	for(const auto &str : input)	
		hTble.insert(str);
	
	std::cout << hTble.find("sdak")->key << std::endl;	
	printHashTable(hTble);
	hTble.delNode("sdak");
	printHashTable(hTble);

	return 0;
}
