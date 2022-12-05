#pragma once
#include "AoC22.h"

class AoC22_06 : public AoC22
{
private:
	std::vector<int> data;

public:
	AoC22_06(const std::string& Filename) : AoC22(Filename)
	{
		this->solve();
	}

private:
	void loadData() override
	{
		for (std::string line : this->rawData)
		{

		}
	}

	void part1() override
	{
		std::cout << "AoC 2022 - Day 06 - Part 1: " << "R1" << std::endl;
	}

	void part2() override
	{
		std::cout << "AoC 2022 - Day 06 - Part 2: " << "R2" << std::endl;
	}

};
