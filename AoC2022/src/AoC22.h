#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <set>
#include <utility>
#include <algorithm>


class AoC22
{
private:

public:
	AoC22(){}

	void solve(const char* filename)
	{
		this->read(filename);
		this->part1();
		this->part2();
	}

private:
	virtual void read(const char* filename) = 0;
	virtual void part1() = 0;
	virtual void part2() = 0;

};
