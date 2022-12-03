#pragma once
#include "AoC22.h"

class AoC22_04 : public AoC22
{
private:
	std::vector<std::string> data;

public:
	AoC22_04(const std::string& Filename) : AoC22(Filename)
	{
		this->solve();
	}

private:
	void read() override
	{
		std::ifstream myfile(filename);

		std::string line;
		if (myfile.is_open())
		{
			while (getline(myfile, line))
			{
				data.push_back(line);
			}
			myfile.close();
		}
		else std::cout << "Unable to open file";

		return;
	}

	void part1() override
	{

		std::cout << "AoC 2022 - Day 04 - Part 1: ";
		std::string result = "R1";
		std::cout << result << std::endl;
	}

	void part2() override
	{
		std::cout << "AoC 2022 - Day 04 - Part 2: ";
		std::string result = "R2";
		std::cout << result << std::endl;
	}

};
