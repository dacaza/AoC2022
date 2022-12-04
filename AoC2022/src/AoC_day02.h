#pragma once

#include "AoC22.h"

class AoC22_02 : public AoC22
{
private:
	std::vector<std::pair<std::string, std::string>> data;

	int ROCK = 1;
	int PAPER = 2;
	int SCISSORS = 3;

	int LOSS = 0;
	int DRAW = 3;
	int WIN = 6;

public:
	AoC22_02(const std::string& Filename) : AoC22(Filename) 
	{ 
		this->solve(); 
	}

private:
	void loadData() override
	{
		this->toStr_Str(data, " ");
	}

	void part1() override
	{
		// A = X = Rock
		// B = Y = Paper
		// C = Z = Scissors

		int score = 0;

		for (int i = 0; i < data.size(); i++)
		{
			std::string& Op = data[i].first;
			std::string& Me = data[i].second;

			if (Me == "X") // Rock
			{
				if (Op == "A") // Rock
					score += DRAW;
				if (Op == "B") // Paper
					score += LOSS;
				if (Op == "C") // Scissors
					score += WIN;

				score += ROCK;
			}

			if (Me == "Y") // Paper
			{
				if (Op == "A") // Rock
					score += WIN;
				if (Op == "B") // Paper
					score += DRAW;
				if (Op == "C") // Scissors
					score += LOSS;

				score += PAPER;
			}

			if (Me == "Z") // Scissors
			{
				if (Op == "A") // Rock
					score += LOSS;
				if (Op == "B") // Paper
					score += WIN;
				if (Op == "C") // Scissors
					score += DRAW;

				score += SCISSORS;
			}
		}

		std::cout << "AoC 2022 - Day 02 - Part 1: ";
		std::cout << score << std::endl;
	}

	void part2() override
	{
		// A Rock
		// B Paper
		// C Scissors

		// X = LOSS
		// Y = DRAW
		// Z = WIN

		int score = 0;

		for (int i = 0; i < data.size(); i++)
		{
			std::string& Op = data[i].first;
			std::string& Me = data[i].second;

			if (Me == "X") // LOSS
			{
				if (Op == "A") // Rock
					score += SCISSORS;
				if (Op == "B") // Paper
					score += ROCK;
				if (Op == "C") // Scissors
					score += PAPER;

				score += LOSS;
			}

			if (Me == "Y") // DRAW
			{
				if (Op == "A") // Rock
					score += ROCK;
				if (Op == "B") // Paper
					score += PAPER;
				if (Op == "C") // Scissors
					score += SCISSORS;

				score += DRAW;
			}

			if (Me == "Z") // WIN
			{
				if (Op == "A") // Rock
					score += PAPER;
				if (Op == "B") // Paper
					score += SCISSORS;
				if (Op == "C") // Scissors
					score += ROCK;

				score += WIN;
			}
		}

		std::cout << "AoC 2022 - Day 02 - Part 2: ";
		std::cout << score << std::endl;
	}

};