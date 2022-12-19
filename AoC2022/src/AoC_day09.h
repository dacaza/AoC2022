#pragma once
#include "AoC22.h"



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
		Point H = { 0, 0 };
		Point T = { 0, 0 };

		std::unordered_set<std::string> cells;
		this->insertPoint(T, cells);

		for (int i = 0; i < data.size(); i++)
		{
			std::string command = data[i].first;
			int val = data[i].second;

			for (int v = 0; v < val; v++)
			{
				this->moveHead(command, H);
				this->moveBody(H, T);
				this->insertPoint(T, cells);
			}
		}

		std::cout << "AoC 2022 - Day 09 - Part 1";
		return std::to_string(cells.size());
	}

	std::string part2() override
	{
		Point H = { 0, 0 };
		std::vector<Point> body(9, { 0, 0 });

		std::unordered_set<std::string> cells;
		this->insertPoint(body.back(), cells);

		for (int i = 0; i < data.size(); i++)
		{
			std::string command = data[i].first;
			int val = data[i].second;

			for (int v = 0; v < val; v++)
			{
				this->moveHead(command, H);
				this->moveBody(H, body[0]);
				for (int k = 1; k < body.size(); k++)
					this->moveBody(body[k-1], body[k]);
				this->insertPoint(body.back(), cells);

				//std::cout << command << " " << v << std::endl;
				//this->draw(H, Knots);
			}

			//std::cout << command << " " << val << std::endl;
			//this->draw(H, body);
		}

		std::cout << "AoC 2022 - Day 09 - Part 2";
		return std::to_string(cells.size());
	}

	void moveHead(const std::string& command, Point& H)
	{
		if (command == "R") 
			H.x += 1;

		if (command == "L")
			H.x -= 1;

		if (command == "U")
			H.y += 1;

		if (command == "D")
			H.y -= 1;
	}

	void moveBody(const Point& H, Point& T)
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

	void draw(const Point& H, const std::vector<Point>& body)
	{
		int N = 100;
		std::vector<std::vector<std::string>> grid;
		grid.resize(N);
		for (int i = 0; i < N; i++)
			grid[i].resize(N, ".");

		int x = H.x + N / 2;
		int y = H.y + N / 2;

		grid[x][y] = "H";
		for (size_t i = body.size() - 1; i >= 0; i--)
		{
			int u = body[i].x + N / 2;
			int v = body[i].y + N / 2;
			grid[u][v] = std::to_string(i + 1);
		}

		for (int i = N - 1; i >= 0; i--)
		{
			for (int j = 0; j < N; j++)
				std::cout << grid[j][i];

			std::cout << std::endl;
		}
	}

	void insertPoint(const Point& P, std::unordered_set<std::string>& set)
	{
		set.insert(std::to_string(P.x) + "," + std::to_string(P.y));
	}

};
