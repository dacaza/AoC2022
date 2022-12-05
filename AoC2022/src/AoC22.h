#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>

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
		std::string name, ext;
		this->split(filename, ".", name, ext);

		this->readRawData(name + "-test." + ext);
		this->loadData();
		std::cout << " - Test    : " << this->part1() << std::endl;
		std::cout << " - Test    : " << this->part2() << std::endl;

		this->readRawData(filename);
		this->loadData();
		std::cout << " - Solution: " << this->part1() << std::endl;
		std::cout << " - Solution: " << this->part2() << std::endl;
	}

private:
	
	virtual void loadData() = 0;
	virtual std::string part1() = 0;
	virtual std::string part2() = 0;

	void readRawData(const std::string& filename)
	{
		rawData.clear();
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
