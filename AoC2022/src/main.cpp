#include "AoC_day01.h"
#include "AoC_day02.h"
#include "AoC_day03.h"

int main()
{
	std::string path = "C:/Users/dacaz/source/repos/AoC2022/AoC2022/data/";

	AoC22_01 day01;
	day01.solve((path + "data01.txt").c_str());

	AoC22_02 day02;
	day02.solve((path + "data02.txt").c_str());

	AoC22_03 day03;
	day03.solve((path + "data03.txt").c_str());

}