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
protected:
	std::string filename;

public:
	AoC22(const std::string& Filename)
		: filename(Filename)
	{
	}

	void solve()
	{
		this->read();
		this->part1();
		this->part2();
	}

private:
	virtual void read() = 0;
	virtual void part1() = 0;
	virtual void part2() = 0;

};
