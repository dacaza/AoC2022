

#pragma once
#include "AoC22.h"

class AoC21_21 : public AoC22
{
private:
	std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> data;

	int dice_faces = 100;
	int track_len = 10;
	int target = 1000;
	int p1_ini = 4;
	int p2_ini = 8;

public:
	AoC21_21(const std::string& Filename) : AoC22(Filename)
	{
		this->solve();
	}

private:
	void loadData() override
	{

	}

	void part1() override
	{
		int p1 = p1_ini;
		int p2 = p2_ini;

		int score1 = 0;
		int score2 = 0;

		int d = 0;
		int dice_count = 0;
		while (true)
		{
			d = (d + 1) % dice_faces;
			this->play(d, p1);

			d = (d + 1) % dice_faces;
			this->play(d, p1);

			d = (d + 1) % dice_faces;
			this->play(d, p1);

			score1 += p1;
			dice_count += 3;
			if (score1 >= target)
				break;

			d = (d + 1) % dice_faces;
			this->play(d, p2);

			d = (d + 1) % dice_faces;
			this->play(d, p2);

			d = (d + 1) % dice_faces;
			this->play(d, p2);

			score2 += p2;
			dice_count += 3;
			if (score2 >= target)
				break;
		}

		std::cout << "AoC 2021 - Day 21 - Part 1: " << std::min({ score1,score2 }) * dice_count << std::endl;
	}

	void play(const int& d, int& p)
	{
		int v;
		v = p - 1;
		v += d;
		v = v % track_len;
		p = v + 1;
	}

	void part2() override
	{
		// No se hace con recursividad, sino con programación dinámica. Revisarlo entero

		int p1 = p1_ini;
		int p2 = p2_ini;

		unsigned long long int score1 = 0;
		unsigned long long int score2 = 0;

		unsigned long long int n_vic1 = 0;
		unsigned long long int n_vic2 = 0;

		this->dirac_play(p1, p2, score1, score2, n_vic1, n_vic2);

		std::cout << "AoC 2021 - Day 21 - Part 2: " << std::max({ n_vic1,n_vic2 }) << std::endl;
	}

	void dirac_play(int& p1, int& p2, unsigned long long int& score1, unsigned long long int& score2, unsigned long long int& n_vic1, unsigned long long int& n_vic2)
	{
		for (size_t i = 0; i < 3; i++)
			for (size_t j = 0; j < 3; j++)
				for (size_t k = 0; k < 3; k++)
				{
					play(i + 1, p1);
					play(j + 1, p1);
					play(k + 1, p1);
					score1 += p1;

					if (score1 >= target)
					{
						n_vic1++;
						return;
					}
					else
					{
						play(i + 1, p2);
						play(j + 1, p2);
						play(k + 1, p2);
						score2 += p2;

						if (score2 >= target)
						{
							n_vic2++;
							return;
						}
						else
							dirac_play(p1, p2, score1, score2, n_vic1, n_vic2);
					}
				}
	}

};
