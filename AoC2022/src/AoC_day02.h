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
	void read() override
	{
		std::ifstream myfile(filename.c_str());

		std::string line;
		if (myfile.is_open())
		{
			while (getline(myfile, line))
			{

				std::size_t pos = line.find(" ");

				std::string command = line.substr(0, pos);
				std::string value = line.substr(pos + 1, line.size());

				std::pair<std::string, std::string> commandPair;
				commandPair.first = command;
				commandPair.second = value;

				data.push_back(commandPair);

			}
			myfile.close();
		}
		else std::cout << "Unable to open file";
	}

	void part1() override
	{

		// A = X = Rock
		// B = Y = Paper
		// C = Z = Scissors

		int score = 0;

		for (int i = 0; i < data.size(); i++)
		{
			if (data[i].second == "X") // Rock
			{
				if (data[i].first == "A") // Rock
					score += DRAW;
				if (data[i].first == "B") // Paper
					score += LOSS;
				if (data[i].first == "C") // Scissors
					score += WIN;
				score += ROCK;
			}

			if (data[i].second == "Y") // Paper
			{
				if (data[i].first == "A") // Rock
					score += WIN;
				if (data[i].first == "B") // Paper
					score += DRAW;
				if (data[i].first == "C") // Scissors
					score += LOSS;
				score += PAPER;
			}

			if (data[i].second == "Z") // Scissors
			{
				if (data[i].first == "A") // Rock
					score += LOSS;
				if (data[i].first == "B") // Paper
					score += WIN;
				if (data[i].first == "C") // Scissors
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
			if (data[i].second == "X") // LOSS
			{
				if (data[i].first == "A") // Rock
					score += SCISSORS;
				if (data[i].first == "B") // Paper
					score += ROCK;
				if (data[i].first == "C") // Scissors
					score += PAPER;
				score += LOSS;
			}

			if (data[i].second == "Y") // DRAW
			{
				if (data[i].first == "A") // Rock
					score += ROCK;
				if (data[i].first == "B") // Paper
					score += PAPER;
				if (data[i].first == "C") // Scissors
					score += SCISSORS;
				score += DRAW;
			}

			if (data[i].second == "Z") // WIN
			{
				if (data[i].first == "A") // Rock
					score += PAPER;
				if (data[i].first == "B") // Paper
					score += SCISSORS;
				if (data[i].first == "C") // Scissors
					score += ROCK;
				score += WIN;
			}
		}

		std::cout << "AoC 2022 - Day 02 - Part 2: ";
		std::cout << score << std::endl;

	}

};