#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <string>
#include <string_view>
#include <unordered_map>

constexpr bool IsNum(char c) 
{
	return (c >= 48 && c < 58);
}

static std::unordered_map<std::string_view, int> NumberStringsMap = {
	{ "one", 1 },
	{ "two", 2 },
	{ "three", 3 },
	{ "four", 4 },
	{ "five", 5 },
	{ "six", 6 },
	{ "seven", 7 },
	{ "eight", 8 },
	{ "nine", 9 },
}; 

constexpr int ExtractNumber(const std::string& str)
{
	if (!(str.size()))
		return 0;

	int num = 0; 	


	for (auto it = str.begin(); it != str.end(); it++)
	{
		char c = *it;
		
		bool second = false;

		// std::cout << c;
	
		auto itTemp = NumberStringsMap.end();
		
		for (auto i = str.begin(); i != it; i++)
			if ((second = (itTemp = NumberStringsMap.find(std::string_view(i, it))) != NumberStringsMap.end()))
			{
				num = (*itTemp).second * 10;	

				break;
			}

		if (second) 
			break;

		if (IsNum(c))
		{
//			std::cout << "IsNum: " << c << '\n'; 

			num = (c - 48) * 10;

			break;
		}
	}

	for (auto it = str.end(); it != (str.begin() - 1); it--)
	{
		char c = *it;

		auto itTemp = NumberStringsMap.end();
	
		bool second = false;

//		std::cout << std::string_view(it, str.end()) << '\n'; //<< (NumberStringsMap.find(std::string_view(it, str.end())) != NumberStringsMap.end()) << '\n';

		for (auto i = str.end(); i != it; i--)
			if ((second = (itTemp = NumberStringsMap.find(std::string_view(it, i))) != NumberStringsMap.end()))
			{
				
				num += (*itTemp).second;

				std::cout << "second: " << second << "; num:" << num << "str: " <<  std::string_view(it, i) << '\n';

				break;
			}

		if (second) 
			break;

		if (IsNum(c))
		{
			std::cout << "IsNum: " << c << '\n'; 

			num += (c - 48);

			break;
		}

	}

	return num;
}

std::vector<std::string> LoadDataset(const std::string_view path)
{
	std::vector<std::string> dataset;

	std::ifstream is = std::ifstream(path.data()); 

	std::string temp;

	while (!is.eof()) 
	{	
		is >> temp;

		dataset.push_back(temp);

		temp.clear();
	}
	
	return dataset;
}


const int GetSum(const std::vector<std::string>& dataset)
{
	int sum = 0;

	for (std::string data : dataset)
		sum += (ExtractNumber(data));

	return sum;
}	

int main(int argc, char** argv)
{		
	std::vector<std::string> dataset = LoadDataset(argv[1]);	

	std::cout << GetSum(dataset) << std::endl;  
	
	return 0;
}
