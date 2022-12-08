#pragma once
#include "AoC22.h"

class AoC22_08 : public AoC22
{
private:
	std::vector<std::vector<int>> data;

public:
	AoC22_08(const std::string& Filename) : AoC22(Filename)
	{
		this->solve();
	}

private:
	void loadData() override
	{
		for (int i = 0; i < data.size(); i++)
			data[i].clear();
		data.clear();

		data.resize(rawData.size());
		for (int i = 0; i < this->rawData.size(); i++)
		{
			for (int j = 0; j < this->rawData[i].length(); j++)
			{
				data[i].push_back(std::stoi(rawData[i].substr(j,1)));
			}
		}
	}

	std::string part1() override
	{
		int sum = 0;

		int rows = data.size();
		int cols = data[0].size();

		int max = 0; 

		//  30373
		//	25512
		//	65332
		//	33549
		//	35390

		for (int i = 1; i < rows-1; i++)
			for (int j = 1; j < cols-1; j++)
			{
				bool visible_top = true;
				bool visible_bottom = true;
				bool visible_left = true;
				bool visible_right = true;

				// top
				max = data[i][j];
				for (int ii = 0; ii < i; ii++)
					if (data[ii][j] >= max)
						visible_top = false;

				// bottom
				max = data[i][j];
				for (int ii = i + 1; ii < rows; ii++)
					if (data[ii][j] >= max)
						visible_bottom = false;

				// left
				max = data[i][j];
				for (int jj = 0; jj < j; jj++)
					if (data[i][jj] >= max)
						visible_left = false;

				// right
				max = data[i][j];
				for (int jj = j+1; jj < cols; jj++)
					if (data[i][jj] >= max)
						visible_right = false;

				if (visible_top || visible_bottom || visible_left || visible_right)
					sum++;
			}

		// Sum edges
		sum += 2 * cols + 2 * (rows - 2);


		std::cout << "AoC 2022 - Day 08 - Part 1";
		return std::to_string(sum);
	}

	std::string part2() override
	{
		std::vector<int> scores;

		int rows = data.size();
		int cols = data[0].size();

		int max = 0;

		//  30373
		//	25512
		//	65332
		//	33549
		//	35390

		for (int i = 1; i < rows - 1; i++)
		{
			for (int j = 1; j < cols - 1; j++)
			{
				int score_top = 0;
				int score_bottom = 0;
				int score_left = 0;
				int score_right = 0;

				// top
				max = data[i][j];
				for (int ii = i - 1; ii >= 0; ii--)
					if (data[ii][j] >= max)
					{
						score_top++;
						break;
					}
					else
						score_top++;

				// bottom
				max = data[i][j];
				for (int ii = i + 1; ii < rows; ii++)
					if (data[ii][j] >= max)
					{
						score_bottom++;
						break;
					}
					else
						score_bottom++;

				// left
				max = data[i][j];
				for (int jj = j - 1; jj >= 0; jj--)
					if (data[i][jj] >= max)
					{
						score_left++;
						break;
					}
					else
						score_left++;
				// right
				max = data[i][j];
				for (int jj = j + 1; jj < cols; jj++)
					if (data[i][jj] >= max)
					{
						score_right++;
						break;
					}
					else
						score_right++;

				scores.push_back(score_top * score_bottom * score_left * score_right);
				printf("i:%d, j:%d - %2d %2d %2d %2d score:%2d\n", i, j, score_top, score_left, score_right, score_bottom, score_top * score_bottom * score_left * score_right);
			}
			std::cout << std::endl;
		}

		std::sort(scores.begin(), scores.end());

		std::cout << "AoC 2022 - Day 08 - Part 2";
		return std::to_string(scores.back());
	}

};
