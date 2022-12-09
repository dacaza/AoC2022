#pragma once
#include "AoC22.h"

struct Point
{
	int x = 0;
	int y = 0;
};

class AoC22_09 : public AoC22
{
private:
	std::vector<std::pair<std::string,int>> data;

public:
	AoC22_09(const std::string& Filename) : AoC22(Filename)
	{
		this->solve();
	}

private:
	void loadData() override
	{
		data.clear();
		for (std::string line : this->rawData)
		{
			std::string command;
			std::string  value;
			this->split(line, " ", command, value);

			data.push_back(std::make_pair(command, std::stoi(value)));
		}
	}

	std::string part1() override
	{
		Point H, T;

		std::unordered_map<std::string, int> cells;

		// Initial position
		this->insertCell(T, cells);

		for (int i = 0; i < data.size(); i++)
		{
			std::string command = data[i].first;
			int val = data[i].second;

			for (int v = 0; v < val; v++)
			{
				// Move Head
				this->moveHead(command, H);

				// Move Tail
				this->moveKnot(H, T);

				this->insertCell(T, cells);
			}
		}

		std::cout << "AoC 2022 - Day 09 - Part 1";
		return std::to_string(cells.size());
	}

	std::string part2() override
	{
		Point H;
		std::vector<Point> Knots(9);

		std::unordered_map<std::string, int> cells;

		// Initial position
		this->insertCell(Knots.back(), cells);

		for (int i = 0; i < data.size(); i++)
		{
			std::string command = data[i].first;
			int val = data[i].second;

			for (int v = 0; v < val; v++)
			{
				// Move Head
				this->moveHead(command, H);

				// Move Tail
				this->moveKnot(H, Knots[0]);
				for (int k = 1; k < Knots.size(); k++)
				{
					this->moveKnot(Knots[k-1], Knots[k]);
				}

				this->insertCell(Knots.back(), cells);

				//std::cout << command << " " << v << std::endl;
				//this->draw(H, Knots);

			}

			//std::cout << command << " " << val << std::endl;
			//this->draw(H, Knots);

		}

		std::cout << "AoC 2022 - Day 09 - Part 2";
		return std::to_string(cells.size());
	}

	void draw(const Point& H, const std::vector<Point>& Knots)
	{
		int N = 100;
		std::vector<std::vector<std::string>> grid;
		grid.resize(N);
		for (int i = 0; i < N; i++)
			grid[i].resize(N,".");


		int x = H.x + N / 2;
		int y = H.y + N / 2;

		grid[x][y] = "H";
		for (int i = Knots.size()-1 ; i >=0 ; i--)
		{
			int u = Knots[i].x + N / 2;
			int v = Knots[i].y + N / 2;
			grid[u][v] = std::to_string(i + 1);
		}

		for (int i = N-1; i>=0;i--)
		{
			for (int j = 0; j<N ; j++)
			{
				std::cout << grid[j][i]; 
			}
			std::cout << std::endl;
		}



	}

	void moveHead(const std::string& command, Point& H)
	{
		if (command == "R") H.x += 1;
		if (command == "L") H.x -= 1;
		if (command == "U") H.y += 1;
		if (command == "D") H.y -= 1;
	}

	void moveKnot(const Point& H, Point& T)
	{
		if (T.x - H.x == 2)
		{
			if (T.y - H.y == 2)
			{
				T.x -= 1;
				T.y -= 1;
			}
			else if (T.y - H.y == -2)
			{
				T.x -= 1;
				T.y += 1;
			}
			else
			{
				T.x -= 1;
				T.y -= T.y - H.y;
			}
		}

		if (T.x - H.x == -2)
		{
			if (T.y - H.y == 2)
			{
				T.x += 1;
				T.y -= 1;
			}
			else if (T.y - H.y == -2)
			{
				T.x += 1;
				T.y += 1;
			}
			else
			{
				T.x += 1;
				T.y -= T.y - H.y;
			}
		}

		if (T.y - H.y == 2)
		{
			if (T.x - H.x == 2)
			{
				T.x -= 1;
				T.y -= 1;
			}
			else if (T.x - H.x == -2)
			{
				T.x += 1;
				T.y -= 1;
			}
			else
			{
				T.y -= 1;
				T.x -= T.x - H.x;
			}
		}

		if (T.y - H.y == -2)
		{
			if (T.x - H.x == 2)
			{
				T.x -= 1; 
				T.y += 1;
			}
			else if (T.x - H.x == -2)
			{
				T.x += 1;
				T.y += 1;
			}
			else
			{
				T.y += 1;
				T.x -= T.x - H.x;
			}
		}
	}

	void insertCell(const Point& P, std::unordered_map<std::string, int>& map)
	{
		std::string posP = std::to_string(P.x) + "," + std::to_string(P.y);
		map.insert(std::pair<std::string, int>(posP, 1));
	}

};
