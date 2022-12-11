#pragma once
#include "AoC22.h"

enum class Operations { sum, mul_val, mul_item };

struct Monkey
{
	std::queue<uint64_t> items;
	Operations op = Operations::sum; 
	int value = 0;
	int div = 1;
	size_t toMonkeyT = 0;
	size_t toMonkeyF = 0;
};

class AoC22_11 : public AoC22
{
private:
	std::vector<Monkey> monkeys;
	uint64_t totaldiv = 1;

public:
	AoC22_11(const std::string& Filename) : AoC22(Filename)
	{
		this->solve();
	}

private:
	void loadData() override
	{
		monkeys.clear();

		int m = 0;
		int ll = 0;
		while (ll < rawData.size())
		{
			Monkey monkey;

			ll++; 
			std::string line = rawData[ll];
			std::string strA, strB;
			this->split(line, ":", strA, strB);

			line = strB;
			std::size_t found = line.find(',');
			while (found != std::string::npos)
			{
				this->split(line, ",", strA, strB);
				monkey.items.push(std::stoi(strA));

				line = strB;
				found = line.find(',');
			}
			monkey.items.push(std::stoi(strB));

			ll++;
			line = rawData[ll];
			found = line.find('*');
			if (found != std::string::npos)
			{
				this->split(line, "*", strA, strB);
				if (strB == " old")
				{
					monkey.op = Operations::mul_item;
					monkey.value = 0;
				}
				else
				{
					monkey.op = Operations::mul_val;
					monkey.value = std::stoi(strB);
				}

			}
			else
			{
				this->split(line, "+", strA, strB);
				monkey.op = Operations::sum;
				monkey.value = std::stoi(strB);
			}

			ll++;
			line = rawData[ll];
			this->split(line, "y", strA, strB);
			monkey.div = std::stoi(strB);

			ll++;
			line = rawData[ll];
			this->split(line, "y", strA, strB);
			monkey.toMonkeyT = std::stoi(strB);

			ll++;
			line = rawData[ll];
			this->split(line, "y", strA, strB);
			monkey.toMonkeyF = std::stoi(strB);

			ll += 2;

			monkeys.push_back(monkey);
		}
	}

	std::string part1() override
	{
		int N = 20;

		totaldiv = 1;
		for (size_t iM = 0; iM < monkeys.size(); iM++)
			totaldiv *= monkeys[iM].div;

		std::vector<uint64_t> inspections(monkeys.size(), 0);

		for (size_t r = 0; r < N; r++)
			for (size_t iM = 0; iM < monkeys.size(); iM++)
				while (!monkeys[iM].items.empty())
				{
					this->play(monkeys[iM], 1);
					inspections[iM]++;
				}

		std::sort(inspections.begin(), inspections.end());
		uint64_t result = inspections[inspections.size() - 1] * inspections[inspections.size() - 2];

		std::cout << "AoC 2022 - Day 11 - Part 1";
		return std::to_string(result);
	}

	std::string part2() override
	{
		int N = 10000;

		this->loadData();
		totaldiv = 1;
		for (size_t iM = 0; iM < monkeys.size(); iM++)
			totaldiv *= monkeys[iM].div;

		std::vector<uint64_t> inspections(monkeys.size(), 0);

		for (size_t r = 0; r < N; r++)
		{
			for (size_t iM = 0; iM < monkeys.size(); iM++)
				while (!monkeys[iM].items.empty())
				{
					this->play(monkeys[iM], 2);
					inspections[iM]++;
				}
		}

		std::sort(inspections.begin(), inspections.end());
		uint64_t result = inspections[inspections.size() - 1] * inspections[inspections.size() - 2];

		std::cout << "AoC 2022 - Day 11 - Part 2";
		return std::to_string(result);
	}

	void play(Monkey& monkey, uint64_t part )
	{
		// Get item from queue
		uint64_t item = monkey.items.front();
		monkey.items.pop();

		// Perform Operation
		switch (monkey.op)
		{
		case Operations::sum:
			item += monkey.value;
			break;
		case Operations::mul_val:
			item *= monkey.value;
			break;
		case Operations::mul_item:
			item *= item;
			break;
		}

		// Recalculate item value 
		if (part == 1)
			item = (uint64_t)floor(item / 3.);
		else if (part == 2)
			item = item % totaldiv;
		
		// Calculate modulo
		if (item % monkey.div == 0)
			monkeys[monkey.toMonkeyT].items.push(item);
		else
			monkeys[monkey.toMonkeyF].items.push(item);
	}

};
