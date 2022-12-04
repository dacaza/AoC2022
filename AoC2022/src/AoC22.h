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

	void split(const std::string& str, const std::string& delimiter, std::string& strA, std::string& strB)
	{
		size_t pos = str.find(delimiter);
		if (pos != std::string::npos)
		{
			strA = str.substr(0, pos);
			strB = str.substr(pos + 1, str.size() - pos);
		}
		else
		{
			strA = str;
			strB = "";
		}
	}

	void split(const std::string& str, const size_t& pos, std::string& strA, std::string& strB)
	{
		if (pos < str.size())
		{
			strA = str.substr(0, pos);
			strB = str.substr(pos, pos);
		}
		else
		{
			strA = str;
			strB = "";
		}
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

public:
	void toInt(std::vector<int>& data)
	{
		for (std::string line : rawData)
			data.push_back(std::stoi(line));
	}

	void toStr_Str(std::vector<std::pair<std::string,std::string>>& data, const std::string& delimiter)
	{
		for (std::string line : rawData)
		{
			std::string strA, strB;
			this->split(line, delimiter, strA, strB);

			std::pair<std::string, std::string> pair;
			pair = std::make_pair(strA, strB);

			data.push_back(pair);
		}
	}

	void toStr_Int(std::vector<std::pair<std::string, int>>& data, const char& delimiter)
	{
		for (std::string line : rawData)
		{
			std::string strA, strB;
			this->split(line, delimiter, strA, strB);

			std::pair<std::string, int> pair;
			pair = std::make_pair(strA, std::stoi(strB));

			data.push_back(pair);
		}
	}

	void toInt_Int(std::vector<std::pair<int, int>>& data, const char& delimiter)
	{
		for (std::string line : rawData)
		{
			std::string strA, strB;
			this->split(line, delimiter, strA, strB);

			std::pair<int, int> pair;
			pair = std::make_pair(std::stoi(strA), std::stoi(strB));

			data.push_back(pair);
		}
	}

	void toVecOfInts(std::vector<int>& data, const char& delimiter)
	{
		std::string current = rawData[0];
		std::string strA;;
		std::string strB;

		std::size_t pos = current.find(delimiter);
		this->split(current, delimiter, strA, strB);
		data.push_back(std::stoi(strA));
		data.push_back(std::stoi(strB));
		current = strB;
		while(pos != std::string::npos)
		{
			this->split(current, delimiter, strA, strB);
			data.push_back(std::stoi(strB));
			current = strB;
			pos = current.find(delimiter);
		}
	}



};
