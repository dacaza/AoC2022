#pragma once
#include "AoC22.h"

class AoC22_15 : public AoC22
{
private:
	std::vector<int> data;
	std::vector<Point> sensors, beacons;
	std::vector<int> dist;
	int part = 0;

public:
	AoC22_15(const std::string& Filename) : AoC22(Filename)
	{
		this->solve();
	}

private:
	void loadData() override
	{
		part++;
		data.clear();
		sensors.clear();
		beacons.clear();
		dist.clear();

		for (std::string line : this->rawData)
		{
			std::string str, strA, strB;
			str = line;
			this->split(str, "=", strA, strB);
			str = strB;
			this->split(str, ",", strA, strB);
			int xs = std::stoi(strA);
			str = strB;
			this->split(str, "=", strA, strB);
			str = strB;
			this->split(str, ":", strA, strB);
			int ys = std::stoi(strA);
			sensors.push_back({ xs,ys });

			str = strB;
			this->split(str, "=", strA, strB);
			str = strB;
			this->split(str, ",", strA, strB);
			int xb = std::stoi(strA);
			str = strB;
			this->split(str, "=", strA, strB);
			int yb = std::stoi(strB);
			beacons.push_back({ xb,yb });

			dist.push_back(this->getManhatanDistance(sensors.back(), beacons.back()));
		}
	}

	std::string part1() override
	{
		int Y = 0;
		if (part == 1)
		{
			Y = 10;
			//this->draw();
		}
		if (part == 2)
			Y = 2000000;

		std::unordered_set<int> grid;
		this->exploreRow(Y, grid);

		std::cout << "AoC 2022 - Day 15 - Part 1";
		return std::to_string(grid.size());
	}

	std::string part2() override
	{
		unsigned long long int result = 0; 

		int xmin = 0, xmax = 0;
		int ymin = 0, ymax = 0;

		if (part == 1)
		{
			xmin = 0;
			xmax = 20;

			ymin = 0;
			ymax = 20;
		
			int x0 = 0;
			int y0 = 0; 
			for (int y = ymin; y <= ymax; y++)
			{
				std::unordered_set<int> grid;
				this->exploreRow(y, xmin, xmax, grid, x0, y0);
			}
			result = 4000000 * x0 + y0;
		}
	
		
		if (part == 2)
		{

			//for (int iS = 0; iS < sensors.size(); iS++)
			//{
			//	float scl = 20.;
			//	sensors[iS].x = (int)(sensors[iS].x / 4000000. * scl);
			//	sensors[iS].y = (int)(sensors[iS].y / 4000000. * scl);
			//													 
			//	beacons[iS].x = (int)(beacons[iS].x / 4000000. * scl);
			//	beacons[iS].y = (int)(beacons[iS].y / 4000000. * scl);

			//	dist[iS] = this->getManhatanDistance(sensors[iS], beacons[iS]);
			//}

			//this->draw();
			//this->drawSensors();
			//this->drawBeacons();

			int ii = 0;
			int jj = 0;

			for (int iS = 0; iS < sensors.size(); iS++)
			{
				Point Si = sensors[iS];
				int di = dist[iS];

				int y_pu_i = Si.y + di - Si.x;
				int y_nu_i = Si.y + di + Si.x;

				for (int jS = 0; jS < sensors.size(); jS++)
				{
					Point Sj = sensors[jS];
					int dj = dist[jS];

					int y_pd_j = Sj.y - dj - Sj.x;
					int y_nd_j = Sj.y - dj + Sj.x;

					if (abs(y_pu_i - y_pd_j) == 2)
					{
						//printf("Si=%2d, Sj=%2d: %7d\n", iS, jS, y_pd_j - y_pu_i);
						//printf("Si=%2d, x=%2d, y=%2d, d=%2d\n", iS, sensors[iS].x, sensors[iS].y, dist[iS]);
						//printf("Sj=%2d, x=%2d, y=%2d, d=%2d\n", jS, sensors[jS].x, sensors[jS].y, dist[jS]);
						ii = iS;
					}

					if (abs(y_nu_i - y_nd_j) == 2)
					{
						//printf("i=%2d, j=%2d: %7d\n", iS, jS, y_nd_j - y_nu_i);
						//printf("Si=%2d, x=%2d, y=%2d, d=%2d\n", iS, sensors[iS].x, sensors[iS].y, dist[iS]);
						//printf("Sj=%2d, x=%2d, y=%2d, d=%2d\n", jS, sensors[jS].x, sensors[jS].y, dist[jS]);
						jj = iS;
					}
				}

			}

			Point Sui = sensors[ii];
			Point Suj = sensors[jj];

			//printf("Si: x=%2d, y=%2d, d=%7d\n", Sui.x, Sui.y, dist[ii]);
			//printf("Sj: x=%2d, y=%2d, d=%7d\n", Suj.x, Suj.y, dist[jj]);

			unsigned long long int y0 =  (Sui.y + Suj.y + dist[ii] + dist[jj] + 2 - Sui.x + Suj.x) / 2;
			unsigned long long int x0 = -(Sui.y - Suj.y + dist[ii] - dist[jj]     - Sui.x - Suj.x) / 2;

			//printf("x=%2d, y=%2d\n", x0, y0);


			result = 4000000 * x0 + y0;
		}

		std::cout << "AoC 2022 - Day 15 - Part 2";
		return std::to_string(result);
	}

	void exploreRow(const int& Y, std::unordered_set<int>& grid)
	{
		for (int iS = 0; iS < sensors.size(); iS++)
		{
			int dm = getManhatanDistance(sensors[iS], beacons[iS]);
			int Ys = sensors[iS].y;
			int dy = abs(Ys - Y);
			int dx = dm - dy;

			if (dy <= dm)
			{
				for (int x = 0; x <= dx; x++)
				{
					int xr = sensors[iS].x + x;
					int xl = sensors[iS].x - x;

					bool xr_empty = true;
					bool xl_empty = true;

					for (int j = 0; j < beacons.size(); j++)
					{
						if ((beacons[j].x == xr && beacons[j].y == Y) || (sensors[j].x == xr && sensors[j].y == Y))
							xr_empty = false;

						if ((beacons[j].x == xl && beacons[j].y == Y) || (sensors[j].x == xl && sensors[j].y == Y))
							xl_empty = false;
					}

					if (xr_empty)
						grid.insert(xr);
					if (xl_empty)
						grid.insert(xl);
				}
			}
		}
	}

	void exploreRow(const int& Y, const int& xmin, const int& xmax, std::unordered_set<int>& grid, int& x0, int& y0)
	{
		for (int iS = 0; iS < sensors.size(); iS++)
		{
			Point S = sensors[iS];
			Point B = beacons[iS];

			int dm = getManhatanDistance(S, B);
			int dy = abs(S.y - Y);
			int dx = dm - dy;

			if (dy <= dm)
			{
				for (int x = 0; x <= dx; x++)
				{
					int xr = S.x + x;
					if (xr >= xmin && xr <= xmax)
							grid.insert(xr);

					int xl =S.x - x;
					if (xl >= xmin && xl <= xmax)
							grid.insert(xl);
				}
			}
		}

		for (int x = xmin; x <= xmax; x++)
		{
			std::unordered_set<int>::const_iterator got = grid.find(x);
			if (got == grid.end())
			{
				//printf("x=%4d, y=%4d\n", x, Y);
				x0 = x;
				y0 = Y;
			}
		}

	}

	bool xIsEmpty(int& x, const int& Y)
	{
		bool empty = true;

		for (int j = 0; j < beacons.size(); j++)
			if ((beacons[j].x == x && beacons[j].y == Y) || (sensors[j].x == x && sensors[j].y == Y))
				empty = false;

		return empty;
	}

	int getManhatanDistance(const Point& P, const Point& Q)
	{
		return abs(P.x - Q.x) + abs(P.y - Q.y);
	}

	void draw()
	{
		int xSmin = 0, xSmax = 0, ySmin = 0, ySmax = 0;
		int xBmin = 0, xBmax = 0, yBmin = 0, yBmax = 0;
		getMinMax(sensors, xSmin, xSmax, ySmin, ySmax);
		getMinMax(beacons, xBmin, xBmax, yBmin, yBmax);

		int xmin = std::min({ xSmin,xBmin });
		int xmax = std::max({ xSmax,xBmax });

		int ymin = std::min({ ySmin,yBmin });
		int ymax = std::max({ ySmax,yBmax });

		for (int j = ymin; j <= ymax; j++)
		{
			printf("%4d ", j);
			for (int i = xmin; i <= xmax; i++)
			{
				Point P = { i,j };
				if (find(P, sensors))
					std::cout << "S";
				else if (find(P, beacons))
					std::cout << "B";
				else
					std::cout << ".";
			}
			std::cout << std::endl;
		}
	}

	void drawSensors()
	{
		int xSmin = 0, xSmax = 0, ySmin = 0, ySmax = 0;
		int xBmin = 0, xBmax = 0, yBmin = 0, yBmax = 0;
		getMinMax(sensors, xSmin, xSmax, ySmin, ySmax);
		getMinMax(beacons, xBmin, xBmax, yBmin, yBmax);

		int xmin = std::min({ xSmin,xBmin });
		int xmax = std::max({ xSmax,xBmax });

		int ymin = std::min({ ySmin,yBmin });
		int ymax = std::max({ ySmax,yBmax });

		for (int j = ymin; j <= ymax; j++)
		{
			printf("%4d ", j);
			for (int i = xmin; i <= xmax; i++)
			{
				Point P = { i,j };
				if (find(P, sensors))
					std::cout << "S";
				else
					std::cout << ".";
			}
			std::cout << std::endl;
		}
	}

	void drawBeacons()
	{
		int xSmin = 0, xSmax = 0, ySmin = 0, ySmax = 0;
		int xBmin = 0, xBmax = 0, yBmin = 0, yBmax = 0;
		getMinMax(sensors, xSmin, xSmax, ySmin, ySmax);
		getMinMax(beacons, xBmin, xBmax, yBmin, yBmax);

		int xmin = std::min({ xSmin,xBmin });
		int xmax = std::max({ xSmax,xBmax });

		int ymin = std::min({ ySmin,yBmin });
		int ymax = std::max({ ySmax,yBmax });

		for (int j = ymin; j <= ymax; j++)
		{
			printf("%4d ", j);
			for (int i = xmin; i <= xmax; i++)
			{
				Point P = { i,j };
				if (find(P, beacons))
					std::cout << "B";
				else
					std::cout << ".";
			}
			std::cout << std::endl;
		}
	}

	void getMinMax(const std::vector<Point>& vec, int& xmin, int& xmax, int& ymin, int& ymax)
	{
		xmin = vec[0].x;
		xmax = vec[0].x;

		ymin = vec[0].y;
		ymax = vec[0].y;

		int i = 1;
		while (i < vec.size())
		{
			if (vec[i].x < xmin)
				xmin = vec[i].x;
			
			if (vec[i].x > xmax)
				xmax = vec[i].x;

			if (vec[i].y < ymin)
				ymin = vec[i].y;

			if (vec[i].y > ymax)
				ymax = vec[i].y;
			i++;
		}
	}

	bool find(const Point& P, const std::vector<Point> vec)
	{
		int k = 0;
		bool PointFound = false;
		while (!PointFound && k < vec.size())
		{
			if (vec[k].x == P.x && vec[k].y == P.y)
			{
				PointFound = true;
				break;
			}
			k++;
		}
		return PointFound;

	}



};
