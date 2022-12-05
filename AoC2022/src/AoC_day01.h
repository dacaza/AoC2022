#pragma once
#include "AoC22.h"

class AoC22_01 : public AoC22
{
private:
	std::vector<int> data;
	std::vector<int> calories;

public:
	AoC22_01(const std::string& Filename) : AoC22(Filename)
	{
		this->solve();
	}

private:
	void loadData() override
	{
		data.clear();
		for (std::string line : rawData)
			if (line.size() > 0)
				data.push_back(std::stoi(line));
			else
				data.push_back(0);

		calories = this->addCalories();
		std::sort(calories.begin(), calories.end());
	}

	std::string part1() override
	{
		int max = calories.back();

		std::cout << "AoC 2022 - Day 01 - Part 1";
		return std::to_string(max);

	}

	std::string part2() override
	{
		size_t n = calories.size();
		int top1 = calories[n - 1];
		int top2 = calories[n - 2];
		int top3 = calories[n - 3];

		std::cout << "AoC 2022 - Day 01 - Part 2";
		return std::to_string(top1 + top2 + top3);
	}

	std::vector<int> addCalories()
	{
		std::vector<int> calories;

		calories.push_back(data[0]);
		for (int i = 1; i < data.size(); i++)
		{
			if (data[i] != 0)
				calories.back() += data[i];
			else
				calories.push_back(0);
		}

		return calories;
	}

};
