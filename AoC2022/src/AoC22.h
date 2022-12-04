#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

class AoC22
{
protected:
	std::string filename;
	std::vector<std::string> rawData;

public:
	AoC22(const std::string& Filename)
		: filename(Filename)
	{
	}

	void split(const std::string& str, const char& delimiter, std::string& strA, std::string& strB)
	{
		size_t pos = str.find(delimiter);
		strA = str.substr(0, pos);
		strB = str.substr(pos + 1, str.size() - pos);
	}

	void split(const std::string& str, const size_t& pos, std::string& strA, std::string& strB)
	{
		strA = str.substr(0, pos);
		strB = str.substr(pos, pos);
	}

protected:
	void solve()
	{
		this->readRawData();
		this->loadData();
		this->part1();
		this->part2();
	}

private:
	
	virtual void loadData() = 0;
	virtual void part1() = 0;
	virtual void part2() = 0;

	void readRawData()
	{
		std::ifstream myfile(filename.c_str());

		std::string line;
		if (myfile.is_open())
		{
			while (getline(myfile, line))
				rawData.push_back(line);

			myfile.close();
		}
		else std::cout << "Unable to open file\n";
	}

};
