#pragma once
#include "AoC22.h"

class AoC22_25 : public AoC22
{
private:
	std::vector<int64_t> data;

public:
	AoC22_25(const std::string& Filename) : AoC22(Filename)
	{
		this->solve();
	}

private:
	void loadData() override
	{
		data.clear();
		for (std::string line : this->rawData)
		{
			int64_t sum = 0;
			for (int i = 0; i < line.length(); i++)
			{
				int val = 0;
				std::string c = line.substr(i, 1);
				if (c == "=")
					val = -2;
				else if (c == "-")
					val = -1;
				else
					val = std::stoi(c);

				sum += val * pow(5, line.length()-1-i);
			}
			data.push_back(sum);
		}

	}

	std::string part1() override
	{
		int64_t sum = 0;
		for (int i = 0; i < data.size(); i++)
			sum += data[i];


		int64_t num = sum;
		int64_t rest = 0; 

		std::string result;
		bool stop = false; 

		while (!stop)
		{
			rest = num % 5;

			if (rest > 2)
				rest = rest-5;
			if (rest == -2)
				result = "=" + result;
			else if (rest == -1)
				result = "-" + result;
			else
				result = std::to_string(rest) + result;

			num = (num - rest)/5;
			if (num < 1)
				stop = true;
		}

		//int a0 = data[0] % 5;
		//int a1 = (data[0] - a0) / 5;
		//int a2 = a1 % 5;
		//if (a2 > 2)
		//	a2 = a2 - 5;
		//int a3 = (a1 -a2)%5;

		std::cout << "AoC 2022 - Day 25 - Part 1";
		return result;
	}

	std::string part2() override
	{
		std::cout << "AoC 2022 - Day 25 - Part 2";
		return "R2";
	}

};
