#pragma once
#include "AoC22.h"

class AoC22_XX : public AoC22
{
private:
	std::vector<int> data;

public:
	AoC22_XX(const std::string& Filename) : AoC22(Filename)
	{
		this->solve();
	}

private:
	void loadData() override
	{
		data.clear();
		for (std::string line : this->rawData)
		{

		}
	}

	std::string part1() override
	{
		std::cout << "AoC 2022 - Day XX - Part 1";
		return "R1";
	}

	std::string part2() override
	{
		std::cout << "AoC 2022 - Day XX - Part 2";
		return "R2";
	}

};
