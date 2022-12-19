#pragma once
#include "AoC22.h"

class AoC22_12 : public AoC22
{
private:
	std::vector<std::vector<int>> data;
	int iS = 0;
	int jS = 0;

	int iE = 0;
	int jE = 0;

public:
	AoC22_12(const std::string& Filename) : AoC22(Filename)
	{
		this->solve();
	}

private:
	void loadData() override
	{
		data.clear();
		for (int i=0; i<this->rawData.size(); i++)
		{
			std::vector<int> row;
			for (int j = 0; j < rawData[i].length(); j++)
			{
				std::string spot = rawData[i].substr(j, 1);
				if (spot == "S")
				{
					iS = i;
					jS = j;
					row.push_back('a'-'a');

				}
				else if (spot == "E")
				{
					iE = i;
					jE = j;
					row.push_back('z' - 'a');
				}
				else
					row.push_back(*spot.c_str() - 'a');
			}
			data.push_back(row);
		}
	}

	std::string part1() override
	{
		for (int i = 0; i < data.size(); i++)
		{
			for (int j = 0; j < data[0].size(); j++)
				std::cout << data[i][j];

			std::cout << std::endl;
		}


		std::cout << "AoC 2022 - Day 12 - Part 1";
		return "R1";
	}

	std::string part2() override
	{
		std::cout << "AoC 2022 - Day 12 - Part 2";
		return "R2";
	}

};
