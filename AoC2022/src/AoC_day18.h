#pragma once
#include "AoC22.h"

class AoC22_18 : public AoC22
{
private:
	std::vector<Point> data;

public:
	AoC22_18(const std::string& Filename) : AoC22(Filename)
	{
		this->solve();
	}

private:
	void loadData() override
	{
		data.clear();
		for (std::string line : this->rawData)
		{
			Point P;
			std::string str,strA, strB;
			str = line;
			this->split(str, ",", strA, strB);
			P.x = std::stoi(strA);
			str = strB;
			this->split(str, ",", strA, strB);
			P.y = std::stoi(strA);
			P.z = std::stoi(strB);

			data.push_back(P);
		}
	}



	std::string part1() override
	{

		std::vector<Point> data_1 = data;

		int nfaces = 0;
		for (int i = 0; i < data_1.size(); i++)
		{
			for (int j = i + 1; j < data_1.size(); j++)
			{
				Point P = data_1[i];
				Point Q = data_1[j];

				if (abs(P.x - Q.x) + abs(P.y - Q.y) + abs(P.z - Q.z) == 1)
					nfaces += 2;
			}
		}
		
		int result = data_1.size() * 6 - nfaces;

		std::cout << "AoC 2022 - Day 18 - Part 1";
		return std::to_string(result);
	}

	std::string part2() override
	{
		std::cout << "AoC 2022 - Day 18 - Part 2";
		return "R2";
	}

};
