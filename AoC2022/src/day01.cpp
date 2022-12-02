#include "problems.h"
#include <algorithm>

void day01()
{
	const char* filename = "C:/Users/dacaz/source/repos/AoC2022/AoC2022/data/data01.txt";

	std::vector<int> data;
	ReadFile01(filename, data);

	day01_part1(data);
	day01_part2(data);
}

void day01_part1(const std::vector<int>& item_calories)
{

	std::vector<int> calories;
	calories.push_back(item_calories[0]);

	for (int i = 1; i < item_calories.size(); i++)
	{
		if (item_calories[i] != 0)
			calories.back() += item_calories[i];
		else
			calories.push_back(0);
	}

	int max = calories[0];
	for (int i = 1; i < calories.size(); i++)
		if (calories[i] > max)
			max = calories[i];



	std::cout << max << std::endl;
	std::cout << "AoC 2022 - Day 01 - Part 1" << std::endl;
}

void day01_part2(const std::vector<int>& item_calories)
{

	std::vector<int> calories;
	calories.push_back(item_calories[0]);

	for (int i = 1; i < item_calories.size(); i++)
	{
		if (item_calories[i] != 0)
			calories.back() += item_calories[i];
		else
			calories.push_back(0);
	}

	std::sort(calories.begin(), calories.end());

	int top1 = calories[calories.size() - 1];
	int top2 = calories[calories.size() - 2];
	int top3 = calories[calories.size() - 3];


	std::cout << +top1 + top2 + top3 << std::endl;
	std::cout << "AoC 2022 - Day 01 - Part 2" << std::endl;
}