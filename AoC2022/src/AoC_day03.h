#pragma once
#include "AoC22.h"

class AoC22_03 : public AoC22
{
private:
	std::vector<std::string> data;

public:
	AoC22_03(const std::string& Filename) : AoC22(Filename)
	{
		this->solve();
	}

private:
	void read() override
	{
		std::ifstream myfile(filename);

		std::string line;
		if (myfile.is_open())
		{
			while (getline(myfile, line))
			{
				data.push_back(line);
			}
			myfile.close();
		}
		else std::cout << "Unable to open file";

		return;
	}

	std::string getItem(const std::string& strA, const std::string& strB)
	{
		std::string items;

		for (int i = 0; i < strA.size(); i++)
		{
			for (int j = 0; j < strB.size(); j++)
			{
				if (strA[i] == strB[j])
					items+=strA[i];
			}
		}

		return items;
	}

	int getVal(const char& item)
	{
		// ASCII
		//std::cout << "97 98 99 ..." << std::endl;
		//std::cout << " a  b  c  d  e  f  g  h  i  j  k  l  m  n  o  p  q  r  s  t  u  v  w  x  y  z" << std::endl;
		//std::cout << "65 66 67 ..." << std::endl;
		//std::cout << " A  B  C  D  E  F  G  H  I  J  K  L  M  N  O  P  Q  R  S  T  U  V  W  X  Y  Z" << std::endl;

		// Prioridad
		//std::cout << "01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26" << std::endl;
		//std::cout << " a  b  c  d  e  f  g  h  i  j  k  l  m  n  o  p  q  r  s  t  u  v  w  x  y  z" << std::endl;
		//std::cout << "27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52" << std::endl;
		//std::cout << " A  B  C  D  E  F  G  H  I  J  K  L  M  N  O  P  Q  R  S  T  U  V  W  X  Y  Z" << std::endl;

		int sum = 0;
		int val = int(item);

		if (val < 97)
			sum = val - 64 + 26;
		else
			sum = val - 96;

		return sum;
	}

	void part1() override
	{
		int sum = 0;
		for (int iS = 0; iS < data.size(); iS++)
		{

			int len = data[iS].size()/2;

			std::string strA = data[iS].substr(0, len);
			std::string strB = data[iS].substr(len, len);

			char item = this->getItem(strA, strB)[0];

			sum += this->getVal(item);
		}

		std::cout << "AoC 2022 - Day 03 - Part 1" << std::endl;
		std::cout << sum << std::endl;

	}

	void part2() override
	{


		int sum = 0;
		for (int iS = 0; iS < data.size(); iS += 3)
		{
			std::string badge01 = this->getItem(data[iS + 0], data[iS + 1]);
			std::string badge12 = this->getItem(data[iS + 1], data[iS + 2]);

			std::string badge = this->getItem(badge01, badge12);

			//std::cout << iS << " " << data[iS + 0] << std::endl;
			//std::cout << iS << " " << data[iS + 1] << std::endl;
			//std::cout << iS << " " << data[iS + 2] << std::endl;
			//std::cout << iS << " " << badge01 << " " << badge12 << std::endl;
			//std::cout << iS << " " << badge << std::endl;

			sum += this->getVal(badge[0]);
		}

		std::cout << "AoC 2022 - Day 03 - Part 2" << std::endl;
		std::cout << sum << std::endl;

	}

};
