#pragma once
#include "AoC22.h"

class AoC22_04 : public AoC22
{
private:
	std::vector<std::pair<std::pair<int, int>,std::pair<int,int>>> data;
	size_t max = 0;
	bool debug = false;

public:
	AoC22_04(const std::string& Filename) : AoC22(Filename)
	{
		this->solve();
	}

private:
	void loadData() override
	{
		for (std::string line : this->rawData)
		{
			std::string a1, a11, a12;
			std::string a2, a21, a22;
			this->split(line, ",", a1, a2);
			this->split(a1, "-", a11, a12);
			this->split(a2, "-", a21, a22);

			std::pair<int, int> pair1, pair2;
			pair1 = std::make_pair(std::stoi(a11), std::stoi(a12));
			pair2 = std::make_pair(std::stoi(a21), std::stoi(a22));
				
			std::pair<std::pair<int, int>, std::pair<int, int>> assigments;
			assigments = std::make_pair(pair1, pair2);

			data.push_back(assigments);

			if (debug)
				printf("%2d-%2d,%2d-%2d\n", pair1.first, pair1.second, pair2.first, pair2.second);				
		}

		this->calcMax();

	}

	void part1() override
	{
		int count = 0;
		
		for (size_t i = 0; i < data.size(); i++)
		{
			// a-b,c-d
			int& a = data[i].first.first;
			int& b = data[i].first.second;
			int& c = data[i].second.first;
			int& d = data[i].second.second;

			if (a >= c && b <= d || a <= c && b >= d)
				count++;
		}

		std::cout << "AoC 2022 - Day 04 - Part 1: ";
		std::cout << count << std::endl;
	}

	void part2() override
	{
		int count = 0;

		for (size_t i = 0; i < data.size(); i++)
		{
			// a-b,c-d
			int& a = data[i].first.first;
			int& b = data[i].first.second;
			int& c = data[i].second.first;
			int& d = data[i].second.second;

			if (a <= d && b >= c || b >= c && a <= c)
				count++;

			if (debug)
				this->draw(data[i]);
		}

		std::cout << "AoC 2022 - Day 04 - Part 2: ";
		std::cout << count << std::endl;
	}

	void draw(const std::pair<std::pair<int, int>, std::pair<int, int>>& data)
	{
		// a-b,c-d
		int a = data.first.first;
		int b = data.first.second;
		int c = data.second.first;
		int d = data.second.second;

		if (a <= d && b >= c || b >= c && a <= c)
			std::cout << "Y ";
		else
			std::cout << "N ";

		printf("%2d-%2d,%2d-%2d ", a, b, c, d);

		std::vector<int> first;
		std::vector<int> second;

		for (size_t i = 1; i < max + 1; i++)
		{
			if (i >= a && i <= b)
				first.push_back((int)i);

			if (i >= c && i <= d)
				second.push_back((int)i);
		}

		std::vector<int> v(first.size() + second.size());
		std::vector<int>::iterator it;

		std::sort(first.begin(), first.end());
		std::sort(second.begin(), second.end());

		it = std::set_union(first.begin(), first.end(), second.begin(), second.end(), v.begin());
		v.resize(it - v.begin());

		int k = 0;
		for (size_t i = 0; i < max; i++)
		{
			if (k < v.size())
			{
				if (i + 1 < v[k])
					std::cout << ".";
				else
				{
					if (a > c)
					{
						if (b > d)
							// ..aFFFFb
							// cSSSSd..
						{
							if (v[k] < a)
								std::cout << "S";
							else if (v[k] > d)
								std::cout << "F";
							else
								std::cout << "X";

						}
						else if (b < d)
							// ..aFFb..
							// cSSSSSSd
						{
							if (v[k] < a)
								std::cout << "S";
							else if (v[k] > b)
								std::cout << "S";
							else
								std::cout << "X";
						}
						else if (b == d)
							// ..aFFFFb
							// cSSSSSSd
						{
							if (v[k] < a)
								std::cout << "S";
							else
								std::cout << "X";
						}
					}
					else if (a < c)
					{
						if (b > d)
							// aFFFFFFb
							// ..cSSd..
						{
							if (v[k] < c)
								std::cout << "F";
							else if (v[k] > d)
								std::cout << "F";
							else
								std::cout << "X";
						}
						else if (b < d)
							// aFFFFb..
							// ..cSSSSd
						{
							if (v[k] < c)
								std::cout << "F";
							else if (v[k] > b)
								std::cout << "S";
							else
								std::cout << "X";
						}
						else if (b == d)
							// aFFFFb
							// ..cSSd
						{
							if (v[k] < c)
								std::cout << "F";
							else
								std::cout << "X";
						}
					}
					else if (a == c)
					{
						if (b > d)
							// aFFFFb
							// cSSd..
						{
							if (v[k] > d)
								std::cout << "F";
							else
								std::cout << "X";
						}
						else if (b < d)
							// aFFb..
							// cSSSSd
						{
							if (v[k] > b)
								std::cout << "S";
							else
								std::cout << "X";
						}
						else if (b == d)
							// aFFFFb
							// cSSSSd
							std::cout << "X";
					}

					k++;
				}
			}
			else
				std::cout << ".";
		}

		std::cout << std::endl;
	}

	void calcMax()
	{
		for (size_t i = 0; i < data.size(); i++)
		{
			if (data[i].first.first > max)
				max = data[i].first.first;

			if (data[i].first.second > max)
				max = data[i].first.second;

			if (data[i].second.first > max)
				max = data[i].second.first;

			if (data[i].second.second > max)
				max = data[i].second.second;
		}
	}

};
