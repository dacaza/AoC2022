#pragma once
#include "AoC22.h"

class AoC22_23 : public AoC22
{
private:
	std::unordered_map<std::string,int> data; // <str_position,proposed_dir>

	Point Pmin;
	Point Pmax;

	const int NO_MOVE = -1;
	const int NORTH   = 0;
	const int SOUTH   = 1;
	const int WEST    = 2;
	const int EAST    = 3;

public:
	AoC22_23(const std::string& Filename) : AoC22(Filename)
	{
		this->solve();
	}

private:
	void loadData() override
	{
		data.clear();

		for (int j = 0; j < this->rawData.size(); j++)
		{
			for (int i = 0; i < rawData[j].length(); i++)
			{
				if (rawData[j].substr(i, 1) == "#")
				{

					data.insert(std::make_pair(std::to_string(i) + "," + std::to_string(j), NORTH));

					if (data.size() == 1)
					{
						Pmin.x = i;
						Pmax.x = i;

						Pmin.y = j;
						Pmax.y = j;
					}
					else
						this->chekLimits(Point({ i,j }));
				}
			}
		}
	}

	std::string part1() override
	{
		std::unordered_map<std::string, int> ground = data;
		std::unordered_map<std::string, int> next_ground;
		//this->draw(ground);

		int nR = 10; // Number of rounds
		for (int r = 0; r < nR; r++)
		{
			int init_dir = r % 4;
			std::unordered_map<std::string, int> nextElf; // <str_position,count>

			// First half - considering where to move ----------------------------------
			for (auto it = ground.begin(); it != ground.end(); ++it)
			{
				std::string current_elf_pos = it->first;
				Point Pe = this->getXY(current_elf_pos); 	//Get Elf position

				// If no other Elves are in one of the 8 positions adjacent to themself,
				// the Elf does not do anything during this round
				if (all_adjacents_free(Pe, ground))
				{
					//std::cout << current_elf_pos << ": all adjacents free" << std::endl;
					it->second = NO_MOVE;
					nextElf.insert(std::make_pair(current_elf_pos, 1)); // Insert in current pos with count 1
				}
				else
				// If the Elf looks in each of four directions in the following order (N,S,W,E)
				// and proposes moving one step in the first valid direction
				{
					int proposed_dir = init_dir;
					int id = 0;
					while (id < 4)
					{
						if (this->dirFree(proposed_dir, Pe, ground))
						{
							std::string next = this->getNextPosition(proposed_dir, Pe);
							std::unordered_map<std::string, int>::const_iterator got = nextElf.find(next);

							if (got == nextElf.end())
								nextElf.insert(std::make_pair(next, 1)); // if free, insert new position
							else
								nextElf.at(next)++;	// if not free, increment counter

							//std::cout << current_elf_pos << ": move to " << next << ", counter: " << nextElf.at(next) << std::endl;

							it->second = proposed_dir; // update proposed Elf dir
							
							break;
						}
						
						proposed_dir = (proposed_dir + 1) % 4;
						id++;
					}

					if (id == 4) // No possible movement
					{
						//std::cout << current_elf_pos << ": no moves available" << std::endl;
						it->second = NO_MOVE;
						nextElf.insert(std::make_pair(current_elf_pos, 1));
					}
				}
			}

			// Second half - actually moving -------------------------------------------
			for (auto it = ground.begin(); it != ground.end(); ++it)
			{
				//Get Elf position
				std::string current = it->first;
				Point Pe = this->getXY(current);
				int proposed_dir = it->second;

				if (proposed_dir == NO_MOVE)
					next_ground.insert(std::make_pair(current, NORTH));
				else
				{
					std::string next = this->getNextPosition(proposed_dir, Pe);
					Point Pnext = this->getXY(next);
					std::unordered_map<std::string, int>::const_iterator got = nextElf.find(next);

					if (got != nextElf.end())
					{
						int counter = got->second;
						if (counter < 2)
							next_ground.insert(std::make_pair(next, NORTH));
						else
							next_ground.insert(std::make_pair(current, NORTH));
					}
				}
			}

			ground = next_ground;
			//std::cout << "Round: " << r+1 << std::endl;
			//this->draw(ground);
			next_ground.clear();
		}
		int empty = this->count(ground);
		std::cout << "AoC 2022 - Day 23 - Part 1";
		return std::to_string(empty);
	}

	std::string part2() override
	{
		std::unordered_map<std::string, int> ground = data;
		std::unordered_map<std::string, int> next_ground;

		bool stop = false;
		int r = 0;
		while (!stop)
		{
			int init_dir = r % 4;
			std::unordered_map<std::string, int> nextElf; // <str_position,count>

			// First half - considering where to move ----------------------------------
			int no_moved_elfs = 0;
			for (auto it = ground.begin(); it != ground.end(); ++it)
			{
				std::string current_elf_pos = it->first;
				Point Pe = this->getXY(current_elf_pos); 	//Get Elf position

				// If no other Elves are in one of the 8 positions adjacent to themself,
				// the Elf does not do anything during this round
				if (all_adjacents_free(Pe, ground))
				{
					it->second = NO_MOVE;
					nextElf.insert(std::make_pair(current_elf_pos, 1)); // Insert in current pos with count 1
					no_moved_elfs++;
				}
				else
					// If the Elf looks in each of four directions in the following order (N,S,W,E)
					// and proposes moving one step in the first valid direction
				{
					int proposed_dir = init_dir;
					int id = 0;
					while (id < 4)
					{
						if (this->dirFree(proposed_dir, Pe, ground))
						{
							std::string next = this->getNextPosition(proposed_dir, Pe);
							std::unordered_map<std::string, int>::const_iterator got = nextElf.find(next);

							if (got == nextElf.end())
								nextElf.insert(std::make_pair(next, 1)); // if free, insert new position
							else
								nextElf.at(next)++;	// if not free, increment counter

							it->second = proposed_dir; // update proposed Elf dir

							break;
						}

						proposed_dir = (proposed_dir + 1) % 4;
						id++;
					}

					if (id == 4) // No possible movement
					{
						it->second = NO_MOVE;
						nextElf.insert(std::make_pair(current_elf_pos, 1));
					}
				}

				if (no_moved_elfs == ground.size())
					stop = true;
			}

			// Second half - actually moving -------------------------------------------
			for (auto it = ground.begin(); it != ground.end(); ++it)
			{
				//Get Elf position
				std::string current = it->first;
				Point Pe = this->getXY(current);
				int proposed_dir = it->second;

				if (proposed_dir == NO_MOVE)
					next_ground.insert(std::make_pair(current, NORTH));
				else
				{
					std::string next = this->getNextPosition(proposed_dir, Pe);
					Point Pnext = this->getXY(next);
					std::unordered_map<std::string, int>::const_iterator got = nextElf.find(next);

					if (got != nextElf.end())
					{
						int counter = got->second;
						if (counter < 2)
							next_ground.insert(std::make_pair(next, NORTH));
						else
							next_ground.insert(std::make_pair(current, NORTH));
					}
				}
			}

			ground = next_ground;
			next_ground.clear();
			r++;
		}

		//this->draw(ground);

		std::cout << "AoC 2022 - Day 23 - Part 2";
		return std::to_string(r);
	}

	void draw(const std::unordered_map<std::string, int>& grid)
	{

		for (auto it = grid.begin(); it != grid.end(); it++)
		{
			std::string strX, strY;
			this->split(it->first, ",", strX, strY);

			int x = std::stoi(strX);
			int y = std::stoi(strY);

			this->chekLimits(Point({ x,y }));
		}

		for (int j = Pmin.y; j <= Pmax.y; j++)
		{
			for (int i = Pmin.x; i <= Pmax.x; i++)
			{
				std::string str = std::to_string(i) + "," + std::to_string(j);

				std::unordered_map<std::string, int>::const_iterator got = grid.find(str);
				if (got == grid.end())
					std::cout << ".";
				else
					std::cout << "#";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	int count(const std::unordered_map<std::string, int>& grid)
	{

		for (auto it = grid.begin(); it != grid.end(); it++)
		{
			std::string strX, strY;
			this->split(it->first, ",", strX, strY);

			int x = std::stoi(strX);
			int y = std::stoi(strY);

			this->chekLimits(Point({ x,y }));
		}

		int empty = 0;
		for (int j = Pmin.y; j <= Pmax.y; j++)
		{
			for (int i = Pmin.x; i <= Pmax.x; i++)
			{
				std::string str = std::to_string(i) + "," + std::to_string(j);

				std::unordered_map<std::string, int>::const_iterator got = grid.find(str);
				if (got == grid.end())
					empty++;
			}
		}

		return empty;
	}

	void chekLimits(const std::string& str)
	{
		std::string strX, strY;
		this->split(str, ",", strX, strY);
		Point P = { std::stoi(strX) , std::stoi(strY) };

		this->chekLimits(P);
	}

	void chekLimits(const Point& P)
	{
		if (P.x < Pmin.x)
			Pmin.x = P.x;
		if (P.x > Pmax.x)
			Pmax.x = P.x;

		if (P.y < Pmin.y)
			Pmin.y = P.y;
		if (P.y > Pmax.y)
			Pmax.y = P.y;
	}

	Point getXY(const std::string str)
	{
		std::string strX, strY;
		this->split(str, ",", strX, strY);
		
		return { std::stoi(strX), std::stoi(strY) };
	}

	std::string getNextPosition(const int& dir, const Point& P)
	{
		int nextX = 0;
		int nextY = 0;

		if (dir == NORTH)
		{
			nextX = P.x;  
			nextY = P.y - 1;
		}

		if (dir == SOUTH)
		{
			nextX = P.x;
			nextY = P.y + 1;
		}

		if (dir == WEST)
		{
			nextX = P.x - 1;
			nextY = P.y;
		}

		if (dir == EAST)
		{
			nextX = P.x + 1;
			nextY = P.y;
		}

		return std::to_string(nextX) + "," + std::to_string(nextY);
	}

	bool dirFree(const int& dir, const Point& P, const std::unordered_map<std::string, int>& grid)
	{
		bool result = false;

		if (dir == NORTH)
		{
			std::string NW = std::to_string(P.x - 1) + "," + std::to_string(P.y - 1);
			std::string N  = std::to_string(P.x    ) + "," + std::to_string(P.y - 1);
			std::string NE = std::to_string(P.x + 1) + "," + std::to_string(P.y - 1);

			std::unordered_map<std::string, int>::const_iterator gotNW = grid.find(NW);
			std::unordered_map<std::string, int>::const_iterator gotN  = grid.find(N );
			std::unordered_map<std::string, int>::const_iterator gotNE = grid.find(NE);

			result = (gotNW == grid.end() && gotN == grid.end() && gotNE == grid.end());
		}

		if (dir == SOUTH)
		{
			std::string SW = std::to_string(P.x - 1) + "," + std::to_string(P.y + 1);
			std::string S  = std::to_string(P.x    ) + "," + std::to_string(P.y + 1);
			std::string SE = std::to_string(P.x + 1) + "," + std::to_string(P.y + 1);

			std::unordered_map<std::string, int>::const_iterator gotSW = grid.find(SW);
			std::unordered_map<std::string, int>::const_iterator gotS  = grid.find(S );
			std::unordered_map<std::string, int>::const_iterator gotSE = grid.find(SE);

			result = (gotSW == grid.end() && gotS == grid.end() && gotSE == grid.end());
		}

		if (dir == WEST)
		{
			std::string NW = std::to_string(P.x - 1) + "," + std::to_string(P.y - 1);
			std::string W  = std::to_string(P.x - 1) + "," + std::to_string(P.y    );
			std::string SW = std::to_string(P.x - 1) + "," + std::to_string(P.y + 1);

			std::unordered_map<std::string, int>::const_iterator gotNW = grid.find(NW);
			std::unordered_map<std::string, int>::const_iterator gotW  = grid.find(W );
			std::unordered_map<std::string, int>::const_iterator gotSW = grid.find(SW);

			result = (gotNW == grid.end() && gotW == grid.end() && gotSW == grid.end());
		}

		if (dir == EAST)
		{
			std::string NE = std::to_string(P.x + 1) + "," + std::to_string(P.y - 1);
			std::string E  = std::to_string(P.x + 1) + "," + std::to_string(P.y    );
			std::string SE = std::to_string(P.x + 1) + "," + std::to_string(P.y + 1);

			std::unordered_map<std::string, int>::const_iterator gotNE = grid.find(NE);
			std::unordered_map<std::string, int>::const_iterator gotE  = grid.find(E );
			std::unordered_map<std::string, int>::const_iterator gotSE = grid.find(SE);

			result = (gotNE == grid.end() && gotE == grid.end() && gotSE == grid.end());
		}

		return result;
	}

	bool all_adjacents_free(const Point& P, const std::unordered_map<std::string, int>& grid)
	{
		bool is_free = true;
		for (int i = -1; i <= 1; i++)
		{
			int X = P.x + i;
			for (int j = -1; j <= 1; j++)
			{
				int Y = P.y + j;
				if (!(i == 0 && j == 0))
				{
					std::string str = std::to_string(X) + "," + std::to_string(Y);
					std::unordered_map<std::string, int>::const_iterator got = grid.find(str);
					if (got == grid.end())
						is_free = is_free && true;
					else
						return false;
				}
			}
		}
		return is_free;
	}


};
