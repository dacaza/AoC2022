#include "problems.h"


int ROCK = 1;
int PAPER = 2;
int SCISSORS = 3;

int LOSS = 0;
int DRAW = 3;
int WIN = 6;


void day02()
{
	const char* filename = "C:/Users/dacaz/source/repos/AoC2022/AoC2022/data/data02.txt";

	std::vector<std::pair<std::string,std::string>> data;
	ReadFile(filename, data);

	day02_part1(data);
	day02_part2(data);
}

void day02_part1(const std::vector<std::pair<std::string, std::string>>& data)
{
	// A = X = Rock
	// B = Y = Paper
	// C = Z = Scissors
	
	int sum = 0;

	for (int i = 0; i < data.size(); i++)
	{
		if (data[i].second == "X") // Rock
		{
			if (data[i].first == "A") // Rock
				sum += DRAW;
			if (data[i].first == "B") // Paper
				sum += LOSS;
			if (data[i].first == "C") // Scissors
				sum += WIN;
			sum += ROCK;
		}

		if (data[i].second == "Y") // Paper
		{
			if (data[i].first == "A") // Rock
				sum += WIN;
			if (data[i].first == "B") // Paper
				sum += DRAW;
			if (data[i].first == "C") // Scissors
				sum += LOSS;
			sum += PAPER;
		}

		if (data[i].second == "Z") // Scissors
		{
			if (data[i].first == "A") // Rock
				sum += LOSS;
			if (data[i].first == "B") // Paper
				sum += WIN;
			if (data[i].first == "C") // Scissors
				sum += DRAW;
			sum += SCISSORS;
		}
	}

	std::cout << sum << std::endl;
	std::cout << "AoC 2022 - Day 02 - Part 1" << std::endl;
}

void day02_part2(const std::vector<std::pair<std::string, std::string>>& data)
{
	// A Rock
	// B Paper
	// C Scissors

	// X = LOSS
	// Y = DRAW
	// Z = WIN

	int sum = 0;

	for (int i = 0; i < data.size(); i++)
	{
		if (data[i].second == "X") // LOSS
		{
			if (data[i].first == "A") // Rock
				sum += SCISSORS;
			if (data[i].first == "B") // Paper
				sum += ROCK;
			if (data[i].first == "C") // Scissors
				sum += PAPER;
			sum += LOSS;
		}

		if (data[i].second == "Y") // DRAW
		{
			if (data[i].first == "A") // Rock
				sum += ROCK;
			if (data[i].first == "B") // Paper
				sum += PAPER;
			if (data[i].first == "C") // Scissors
				sum += SCISSORS;
			sum += DRAW;
		}

		if (data[i].second == "Z") // WIN
		{
			if (data[i].first == "A") // Rock
				sum += PAPER;
			if (data[i].first == "B") // Paper
				sum += SCISSORS;
			if (data[i].first == "C") // Scissors
				sum += ROCK;
			sum += WIN;
		}


	}

	std::cout << sum << std::endl;

	std::string result;
	std::cout << result << std::endl;
	std::cout << "AoC 2022 - Day 02 - Part 2" << std::endl;
}