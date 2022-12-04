#pragma once
#include "AoC22.h"

class AoC22_04 : public AoC22
{
private:
	std::vector<std::pair<std::pair<int, int>,std::pair<int,int>>> data;
	int max = 0;
	bool debug = false;

public:
	AoC22_04(const std::string& Filename) : AoC22(Filename)
	{
		this->solve();
	}

private:
	void read() override
	{
		std::ifstream myfile(filename);

		std::string line;
		if (myfile.is_open())
		{
			while (getline(myfile, line))
			{
				int pos0 = line.find(",");
				std::string assig_1 = line.substr(0, pos0);
				std::string assig_2 = line.substr(pos0+1, line.size()-pos0);

				int pos1 = assig_1.find("-");
				std::pair<int, int> pair1;
				pair1.first = std::stoi(assig_1.substr(0, pos1));
				pair1.second = std::stoi(assig_1.substr(pos1+1, assig_1.size()-pos1));

				int pos2 = assig_2.find("-");
				std::pair<int, int> pair2;
				pair2.first = std::stoi(assig_2.substr(0, pos2));
				pair2.second = std::stoi(assig_2.substr(pos2 + 1, assig_2.size() - pos2));

				std::pair<std::pair<int, int>, std::pair<int, int>> assigments;
				assigments.first = pair1;
				assigments.second = pair2;

				data.push_back(assigments);

				if (pair1.first > max)
					max = pair1.first;

				if (pair1.second > max)
					max = pair1.second;
				
				if (pair2.first > max)
					max = pair2.first;
				
				if (pair2.second > max)
					max = pair2.second;

				if (debug)
					printf("%2d-%2d,%2d-%2d\n", pair1.first, pair1.second, pair2.first, pair2.second);
				
			}

			if (debug)
				std::cout << max << std::endl;

			myfile.close();
		}
		else std::cout << "Unable to open file";

		return;
	}

	void draw(const std::pair<std::pair<int, int>, std::pair<int, int>>& data)
	{
		// a-b,c-d
		int a = data.first.first;
		int b = data.first.second;
		int c = data.second.first;
		int d = data.second.second;

		std::vector<int> first;
		std::vector<int> second;

		for (size_t i = 1; i < max+1; i++)
		{
			if (i >= a && i <= b)
				first.push_back(i);

			if (i >= c && i <= d)
				second.push_back(i);
		}

		std::vector<int> v(first.size()+second.size());
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

	void part1() override
	{
		int count = 0;
		
		for (size_t i = 0; i < data.size(); i++)
		{
			// a-b,c-d
			int a = data[i].first.first;
			int b = data[i].first.second;
			int c = data[i].second.first;
			int d = data[i].second.second;

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
			int a = data[i].first.first;
			int b = data[i].first.second;
			int c = data[i].second.first;
			int d = data[i].second.second;

			if (a <= d && b >= c || b >= c && a <= c)
			{
				count++;
				if (debug) 
					std::cout << "Y ";
			}
			else
			{
				if (debug)
					std::cout << "N ";
			}

			if (debug)
			{
				printf("%2d-%2d,%2d-%2d ", a,b,c,d);
				this->draw(data[i]);
			}
		}

		std::cout << "AoC 2022 - Day 04 - Part 2: ";
		std::cout << count << std::endl;
	}

};
