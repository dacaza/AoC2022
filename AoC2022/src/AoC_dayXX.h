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
	void read() override
	{

	}

	void part1() override
	{

		std::cout << "AoC 2022 - Day XX - Part 1: ";
		std::string result = "R1";
		std::cout << result << std::endl;
	}

	void part2() override
	{
		std::cout << "AoC 2022 - Day XX - Part 2: ";
		std::string result = "R2";
		std::cout << result << std::endl;
	}

};
