#include "readTxt.h"
#include <string>
#include <vector>

int main()
{
	std::string strIn = "123 21 32";
	std::vector<int> vecInt;
	splitStr2Int(strIn, vecInt, ' ');	
	for(const auto &elem : vecInt)
		std::cout << elem << " ";
	std::cout << std::endl;

	return 0;
}
