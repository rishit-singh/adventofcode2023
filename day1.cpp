#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <string>
#include <string_view>

constexpr bool IsNum(char c) 
{
	return (c >= 48 && c < 58);
}

constexpr int ExtractNumber(const std::string& str)
{
	if (!(str.size()))
		return 0;

	int num = 0; 	

	for (char c : str)
		if (IsNum(c))
		{
			std::cout << "IsNum: " << c << '\n'; 

			num = (c - 48) * 10;

			break;
		}
	
	for (int x = str.size() - 1; x >= 0; x--)
	{
		if (IsNum(str[x]))
		{
			std::cout << "IsNum: " << str[x] << '\n'; 
			num += str[x] - 48;
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

	std::cout << GetSum(dataset) << std::endl; // GetSum(dataset) << '\n';  

	return 0;
}
