#pragma once
#include "AoC22.h"

class AoC22_10 : public AoC22
{
private:
	std::vector<std::pair<std::string,int>> data;

	int X = 0;

	int W = 40;
	int H = 6;

public:
	AoC22_10(const std::string& Filename) : AoC22(Filename)
	{
		this->solve();
	}

private:
	void loadData() override
	{
		data.clear();
		for (std::string line : this->rawData)
		{
			std::string strA, strB;
			this->split(line, " ", strA, strB);

			if (strB != "")
				data.push_back(std::make_pair(strA, std::stoi(strB)));
			else
				data.push_back(std::make_pair(strA, 0));

		}
	}

	std::string part1() override
	{
		int sum = 0;

		std::vector<int> stops = { 20, 60, 100, 140, 180, 220 };
		int iStop = 0;

		X = 1;
		int cycle = 1;
		//std::cout << cycle << " : " << X << std::endl;

		for (int i=0; i < data.size(); i++)
		{
			int delta_cycles = 0;
			int val = 0;

			if (data[i].first[0] == 'a')
			{
				delta_cycles = 2;
				val = data[i].second;
			}
			else
			{
				delta_cycles = 1;
				val = 0;
			}

			for (int k=0; k< delta_cycles; k++)
			{
				if (k == delta_cycles - 1)
					X += val;
				cycle++;
				if (iStop < stops.size() && cycle == stops[iStop])
				{
					//std::cout << cycle << " : " << X << std::endl;
					sum += cycle * X;
					iStop++;
				}
			}
		}

		std::cout << "AoC 2022 - Day 10 - Part 1";
		return std::to_string(sum);
	}

	std::string part2() override
	{
		std::vector<bool> CRT(100*W * H);

		X = 1;
		int cycle = 1;

		if (cycle%W == X || cycle%W == X + 1 || cycle%W == X + 2)
			CRT[cycle - 1] = true;
		//std::cout << cycle << " : " << X << " - " << CRT[cycle - 1] << std::endl;

		for (int i = 0; i < data.size(); i++)
		{
			int delta_cycles = 0;
			int val = 0;

			if (data[i].first[0] == 'a')
			{
				delta_cycles = 2;
				val = data[i].second;
			}
			else
			{
				delta_cycles = 1;
				val = 0;
			}

			for (int k = 0; k < delta_cycles; k++)
			{
				if (k == delta_cycles - 1)
					X += val;
				cycle++;

				if (cycle%W == X || cycle%W == X + 1 || cycle%W == X + 2)
					CRT[cycle - 1] = true;
				//std::cout << cycle << " : " << X << " - " << CRT[cycle - 1] << std::endl;
			}
		}

		this->draw(CRT);

		std::cout << "AoC 2022 - Day 10 - Part 2";
		return "R2";
	}

	void draw(const std::vector<bool>& CRT)
	{
		for (int i = 0; i < H; i++)
		{
			for (int j = 0; j < W; j++)
				if (CRT[j + W * i] == true)
					std::cout << "#";
				else
					std::cout << ".";
			std::cout << std::endl;

		}
	}

};
