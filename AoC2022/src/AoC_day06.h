#pragma once
#include "AoC22.h"

class AoC22_06 : public AoC22
{
private:
	std::string data;

public:
	AoC22_06(const std::string& Filename) : AoC22(Filename)
	{
		this->solve();
	}

private:
	void loadData() override
	{
		data.clear();
		for (std::string line : this->rawData)
			data = line;
	}

	std::string part1() override
	{
		const int marker_len = 4;
		int k = this->getMarker(marker_len);

		std::string marker = data.substr(k - marker_len, marker_len);
		
		std::cout << "AoC 2022 - Day 06 - Part 1";
		return marker + " " + std::to_string(k);
	}

	std::string part2() override
	{
		const int marker_len = 14;
		int k = this->getMarker(marker_len);

		std::string marker = data.substr(k - marker_len, marker_len);

		std::cout << "AoC 2022 - Day 06 - Part 2";
		return marker + " " + std::to_string(k);
	}

	int getMarker(const int& marker_len)
	{
		std::string marker;

		int k = 0;
		while (k < data.length())
		{
			marker = data.substr(k, marker_len);

			bool stop = false;
			int i = 0;
			while (i < marker_len && !stop)
			{
				int j = i + 1;
				while (j < marker_len && !stop)
				{
					if (marker[i] == marker[j])
						stop = true;
					j++;
				}
				i++;
			}
			if (!stop)
				break;
			k++;
		}

		return k + marker_len;
	}

};


