#pragma once
#include "AoC22.h"


class AoC22_14 : public AoC22
{
private:
	std::unordered_map<std::string,int> data;

	int Xmin = 0;
	int Xmax = 0;
	int Ymin = 0;
	int Ymax = 0;

	Point S = { 500,0 };

	int ROCK = 1;
	int SOURCE = 2; 
	int SAND = 3;


public:
	AoC22_14(const std::string& Filename) : AoC22(Filename)
	{
		this->solve();
	}

private:
	void loadData() override
	{
		data.clear();
				
		Xmin = S.x;
		Xmax = S.x;
		
		Ymin = S.y;
		Ymax = S.y;

		for (std::string line : this->rawData)
		{

			std::string str, strA, strB;
			this->split(line, " -> ", strA, strB);

			std::vector<std::string> walls;
			walls.push_back(strA);
			data.insert(std::make_pair(strA, ROCK));

			this->chekLimits(this->getWallVals(walls.back()));

			str = strB;
			while(str.length() > 0)
			{
				this->split(str, " ", strA, strB);
				str = strB;
				this->split(str, " ", strA, strB);
				walls.push_back(strA);
				str = strB;

				this->chekLimits(this->getWallVals(walls.back()));
			}

			Point P = this->getWallVals(walls[0]);
			for (int i = 1; i < walls.size(); i++)
			{
				Point Q = this->getWallVals(walls[i]);

				int ii = Q.x - P.x;
				int jj = Q.y - P.y;

				if (ii > 0)
					for (int k = P.x; k <= Q.x; k++)
						data.insert(std::make_pair(std::to_string(k) + "," + std::to_string(P.y), ROCK));

				if (ii < 0)
					for (int k = Q.x; k <= P.x; k++)
						data.insert(std::make_pair(std::to_string(k) + "," + std::to_string(P.y), ROCK));

				if (jj > 0)
					for (int k = P.y; k <= Q.y; k++)
						data.insert(std::make_pair(std::to_string(P.x) + "," + std::to_string(k), ROCK));

				if (jj < 0)
					for (int k = Q.y; k <= P.y; k++)
						data.insert(std::make_pair(std::to_string(P.x) + "," + std::to_string(k), ROCK));

				P = Q;
			}
		}
	}

	Point getWallVals(const std::string& wall)
	{
		std::string strA, strB;
		this->split(wall, ",", strA, strB);

		Point P;
		P.x = std::stoi(strA);
		P.y = std::stoi(strB);

		return P;
	}

	void chekLimits(const Point& P)
	{
		if (P.x < Xmin)
			Xmin = P.x;
		if (P.x > Xmax)
			Xmax = P.x;

		if (P.y < Ymin)
			Ymin = P.y;
		if (P.y > Ymax)
			Ymax = P.y;
	}

	void draw()
	{
		for (int j = Ymin; j <= Ymax; j++)
		{
			for (int i = Xmin; i <= Xmax; i++)
			{
				int val; 
				if (this->isFree({ i,j },val))
					std::cout << ".";
				else if (val == ROCK)
					std::cout << "#";
				else if (val == SAND)
					std::cout << "o";
				else if (val == SOURCE)
					std::cout << "+";
			}
			std::cout << std::endl;
		}
	}

	bool isFree(const Point& P, int& val)
	{
		std::string str = std::to_string(P.x) + "," + std::to_string(P.y);
		bool free = false;

		std::unordered_map<std::string,int>::const_iterator got = data.find(str);
		if (got == data.end())
			free = true;
		else
		{
			free = false;
			val = got->second;
		}

		return free;
	}

	std::string part1() override
	{
		Point next({ S.x,S.y});

		while (next.x >= Xmin && next.x <= Xmax)
		{
			next.x = S.x;
			next.y = S.y + 1;

			while (next.x >= Xmin && next.x <= Xmax)
			{
				int val = 0;
				if (this->isFree(next, val))
					next.y += 1;

				else if (this->isFree({ next.x - 1, next.y }, val))
					next.x -= 1;

				else if (this->isFree({ next.x + 1,next.y }, val))
					next.x += 1;
				else
				{
					data.insert(std::make_pair(std::to_string(next.x) + "," + std::to_string(next.y-1), SAND));
					//this->draw();
					break;
				}
			}
		}
		//this->draw();

		int res = 0;
		for (int j = Ymin; j <= Ymax; j++)
		{
			for (int i = Xmin; i <= Xmax; i++)
			{
				int val = 0;
				this->isFree({ i,j }, val);
				if (val == SAND)
					res++;
			}
		}

		std::cout << "AoC 2022 - Day 14 - Part 1";
		return std::to_string(res);
	}

	std::string part2() override
	{
		this->loadData();

		Point next({ S.x,S.y-1 });

		// Add floor
		Ymax += 2;
		for (int i = Xmin; i <= Xmax; i++)
			data.insert(std::make_pair(std::to_string(i) + "," + std::to_string(Ymax), ROCK));

		while (!(next.x == S.x && next.y == S.y+1))
		{
			next.x = S.x;
			next.y = S.y;

			while (next.y <= Ymax)
			{
				int val = 0;
				if (this->isFree(next, val))
				{
					if (next.y != Ymax)
						next.y += 1;
					else
					{
						data.insert(std::make_pair(std::to_string(next.x) + "," + std::to_string(Ymax), ROCK));
						this->chekLimits(next);
						break;
					}
				}
				else if (this->isFree({ next.x - 1, next.y }, val))
					next.x -= 1;

				else if (this->isFree({ next.x + 1,next.y }, val))
					next.x += 1;
				else
				{
					data.insert(std::make_pair(std::to_string(next.x) + "," + std::to_string(next.y - 1), SAND));
					//this->draw();
					break;
				}
			}
		}
		//this->draw();

		int res = 0;
		for (int j = Ymin; j <= Ymax; j++)
		{
			for (int i = Xmin; i <= Xmax; i++)
			{
				int val = 0;
				this->isFree({ i,j }, val);
				if (val == SAND)
					res++;
			}
		}

		std::cout << "AoC 2022 - Day 14 - Part 2";
		return std::to_string(res);
	}

};
