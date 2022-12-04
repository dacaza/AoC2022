#pragma once
#include "AoC22.h"

class AoC22_05 : public AoC22
{
private:
	std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> data;

public:
	AoC22_05(const std::string& Filename) : AoC22(Filename)
	{
		this->solve();
	}

private:
	void loadData() override
	{

	}

	void part1() override
	{

		std::cout << "AoC 2022 - Day 05 - Part 1: " << "R1" << std::endl;
	}

	void part2() override
	{
		std::cout << "AoC 2022 - Day 05 - Part 2: " << "R2" << std::endl;
	}

};
