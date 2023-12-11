#include <string_view>
#include <string>
#include <vector>
#include <unordered_map> 
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ostream>

struct GameSet
{
	size_t Red;

	size_t Green;

	size_t Blue;

	GameSet(size_t = 0, size_t = 0, size_t = 0);
		
	friend std::ostream& operator << (std::ostream&, const GameSet&);
};

std::ostream& operator << (std::ostream& stream, const GameSet& value)
{
	stream << "[ Red: " << value.Red << ", Green: " << value.Green << ", Blue: " << value.Blue << "];";

	return stream;
}

GameSet::GameSet(size_t red, size_t green, size_t blue) : Red(red), Green(green), Blue(blue) {}

GameSet SumSets(std::vector<GameSet>& game)
{
	GameSet sum = GameSet();

	for (GameSet set : game)
	{
		sum.Red += set.Red;
		sum.Green += set.Green;
		sum.Blue += set.Blue;
	}

	return sum;
}

bool IsPossible(std::vector<GameSet> game, GameSet max)
{
	GameSet sum = SumSets(game); 

	return (sum.Red <= max.Red &&
			sum.Blue <= max.Blue &&
			sum.Green <= max.Green);
}

std::vector<std::string_view> Split(std::string_view str, char c)
{	
	std::vector<std::string_view> split = std::vector<std::string_view>();
		
	auto start = str.begin();

	for (auto it = str.begin(); it != str.end(); it++)
		if (*it == c)
		{
			split.push_back(std::string_view(start, it));
			
			start = it + 1;
		}
		else if (it == str.end() - 1)
		{
			split.push_back(std::string_view(start, it + 1));
		}
	
	return split;
}

std::string_view Trim(std::string_view str)
{
	auto start = str.begin(), end = str.end();
		
	for (; (*start == ' ') && start != str.end(); start++);
	
	for (; (*end == ' ') && end != start; end--);
				
	return std::string_view(start, end);
}

std::vector<GameSet> GetGameSetsFromString(std::string_view str)
{
	std::vector<GameSet> gameSets = std::vector<GameSet>();

	for (auto str : Split(Trim(str.substr(str.find(":") + 1, str.size() - 1)), ';'))
	{
		GameSet set;

		for (auto color : Split(Trim(str), ','))
		{
			auto temp = Split(Trim(color), ' ');

			size_t num = atoi(temp[0].data());
			
			std::string_view colorStr = temp[1];
			
			if (colorStr == "red")
				set.Red += num;
			else if (colorStr == "green")
				set.Green += num;
			else if (colorStr == "blue")
				set.Blue += num;
		}
	
		gameSets.push_back(set);

		set = GameSet();
	}


	return gameSets;	
}

std::vector<std::string> LoadDataset(const std::string_view path)
{
	std::ifstream stream = std::ifstream(path.data());	

	std::vector<std::string> strs = std::vector<std::string>();
	
	std::string temp;

	while (std::getline(stream, temp))	
		strs.push_back(temp);

		
	return strs; 
}


int main(int argc, char** argv)
{
	std::string_view str = argv[1];

	size_t sum = 0;

	GameSet max = GameSet(12, 13, 14);

	std::vector<std::string> dataset = LoadDataset(str);
	
	for (size_t x = 0 ; x < dataset.size(); x++)
	{
		auto sets = GetGameSetsFromString(dataset[x]);

		if (IsPossible(sets, max))
			sum += (x + 1);
	}

	std::cout << "sum: " << sum << '\n';

	return 0;
}
