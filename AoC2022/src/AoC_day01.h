#pragma once
#include "AoC22.h"

class AoC22_01 : public AoC22
{
private:
	std::vector<int> data;

private:
	void read(const char* filename) override
	{
		std::ifstream myfile(filename);

		std::string line;
		if (myfile.is_open())
		{
			while (getline(myfile, line))
			{
				if (line.size() > 0)
				{
					data.push_back(std::stoi(line));
				}
				else
				{
					data.push_back(0);
				}
			}
			myfile.close();
		}
		else std::cout << "Unable to open file";

	}

	void part1() override
	{
		std::vector<int>& item_calories = data;

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

		std::cout << "AoC 2022 - Day 01 - Part 1" << std::endl;
		std::cout << max << std::endl;

	}

	void part2() override
	{
		std::vector<int>& item_calories = data;

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

		std::cout << "AoC 2022 - Day 01 - Part 2" << std::endl;
		std::cout << +top1 + top2 + top3 << std::endl;

	}

};
