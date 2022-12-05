#pragma once
#include "AoC22.h"

class AoC22_05 : public AoC22
{
private:
	std::vector<std::vector<int>> data;
	std::vector<std::stack<std::string>> stacks;

public:
	AoC22_05(const std::string& Filename) : AoC22(Filename)
	{
		this->solve();
	}

private:
	void loadData() override
	{
		std::vector<std::stack<std::string>> temp_stacks;

		// Load Stacks
		// [W]     [L]     [T] [H] [V] [F] [H]
		// 012301230123012301230123012301230123
		int k = 0;
		int nS = (rawData[k].size() + 1) / 4;
		temp_stacks.resize(nS);
		std::string ss = rawData[k].substr(1, 1);
		while (ss != "1")
		{
			for (int iS = 0; iS < nS; iS++)
				if (rawData[k].substr(4 * iS + 1, 1) != " ")
					temp_stacks[iS].push(rawData[k].substr(4*iS+1, 1));
			k++;
			ss = rawData[k].substr(1, 1);
		}

		// Invertir el orden de las pilas
		stacks.resize(nS);
		for (int i = 0; i < temp_stacks.size(); i++)
		{
			while (temp_stacks[i].size()>0)
			{
				stacks[i].push(temp_stacks[i].top());
				temp_stacks[i].pop();
			}
		}

		// Load instructions
		k += 2; // pasa el espacio en blanco del archivo
		std::vector<int> instructions(3);
		std::string strA, strB;
		while (k < rawData.size())
		{
			// move 1 from 2 to 1
			this->split(rawData[k], " ", strA, strB);
			this->split(strB, " ", strA, strB);
			instructions[0] = std::stoi(strA);	// mov

			this->split(strB, " ", strA, strB);
			this->split(strB, " ", strA, strB);
			instructions[1] = std::stoi(strA);	// stack_i

			this->split(strB, " ", strA, strB);
			instructions[2] = std::stoi(strB);	// stack_f

			data.push_back(instructions);

			k++;
		}
	}

	void part1() override
	{
		std::vector<std::stack<std::string>> stacks_1 = stacks;

		int mov, stack_i, stack_f;
		for (int i = 0; i < data.size(); i++)
		{
			mov	    = data[i][0];
			stack_i = data[i][1] - 1;
			stack_f = data[i][2] - 1;

			// move 3 from 2 to 1
			// one at a time
			std::string crate;
			for (int i = 0; i < mov; i++)
			{
				crate = stacks_1[stack_i].top();
				stacks_1[stack_i].pop();
				stacks_1[stack_f].push(crate);
			}
		}

		std::string result;
		for (int i = 0; i < stacks_1.size(); i++)
			result += stacks_1[i].top();

		std::cout << "AoC 2022 - Day 05 - Part 1: " << result << std::endl;
	}

	void part2() override
	{
		std::vector<std::stack<std::string>> stacks_2 = stacks;

		int mov, stack_i, stack_f;
		for (int i = 0; i < data.size(); i++)
		{
			mov = data[i][0];
			stack_i = data[i][1] - 1;
			stack_f = data[i][2] - 1;

			// move 3 from 2 to 1
			// at the same time
			std::stack<std::string> temp;
			for (int i = 0; i < mov; i++)
			{
				temp.push(stacks_2[stack_i].top());
				stacks_2[stack_i].pop();
			}

			std::string crate;
			while (temp.size()>0)
			{
				crate = temp.top();
				temp.pop();
				stacks_2[stack_f].push(crate);
			}
		}

		std::string result;
		for (int i = 0; i < stacks_2.size(); i++)
			result += stacks_2[i].top();

		std::cout << "AoC 2022 - Day 05 - Part 2: " << result << std::endl;
	}
};
