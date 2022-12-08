#pragma once
#include "AoC22.h"

class AoC22_08 : public AoC22
{
private:
	std::vector<std::vector<int>> data;
	std::vector<std::vector<bool>> mVisible;
	std::vector<std::vector<bool>> mVisible_top;
	std::vector<std::vector<bool>> mVisible_bottom;
	std::vector<std::vector<bool>> mVisible_left;
	std::vector<std::vector<bool>> mVisible_right;	
	std::vector<std::vector<int>> mScenic_score;

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

		for (int i = 0; i < mVisible.size(); i++)
			mVisible[i].clear();
		mVisible.clear();

		for (int i = 0; i < mVisible_top.size(); i++)
			mVisible_top[i].clear();
		mVisible_top.clear();

		for (int i = 0; i < mVisible_bottom.size(); i++)
			mVisible_bottom[i].clear();
		mVisible_bottom.clear();

		for (int i = 0; i < mVisible_left.size(); i++)
			mVisible_left[i].clear();
		mVisible_left.clear();

		for (int i = 0; i < mVisible_right.size(); i++)
			mVisible_right[i].clear();
		mVisible_right.clear();

		for (int i = 0; i < mScenic_score.size(); i++)
			mScenic_score[i].clear();
		mScenic_score.clear();

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
		{
			std::vector<bool> rVisible;
			std::vector<bool> rVisible_top;
			std::vector<bool> rVisible_bottom;
			std::vector<bool> rVisible_left;
			std::vector<bool> rVisible_right;

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
				for (int jj = j + 1; jj < cols; jj++)
					if (data[i][jj] >= max)
						visible_right = false;


				rVisible_top.push_back(visible_top);
				rVisible_bottom.push_back(visible_bottom);
				rVisible_left.push_back(visible_left);
				rVisible_right.push_back(visible_right);
				rVisible.push_back(visible_top && visible_bottom && visible_left && visible_right);

				if (visible_top || visible_bottom || visible_left || visible_right)
						sum++;

			}
			mVisible_top.push_back(rVisible_top);
			mVisible_bottom.push_back(rVisible_bottom);
			mVisible_left.push_back(rVisible_left);
			mVisible_right.push_back(rVisible_right);
			mVisible.push_back(rVisible);
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
			std::vector<int> rScenic_score;
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
				rScenic_score.push_back(scores.back());
				//printf("i:%d, j:%d - %2d %2d %2d %2d score:%2d\n", i, j, score_top, score_left, score_right, score_bottom, score_top * score_bottom * score_left * score_right);
			}
			mScenic_score.push_back(rScenic_score);
			//std::cout << std::endl;
		}

		//this->draw();

		std::sort(scores.begin(), scores.end());

		std::cout << "AoC 2022 - Day 08 - Part 2";
		return std::to_string(scores.back());
	}

	void draw()
	{

		std::fstream output_file;
		std::string path = "C:/Users/dacaz/source/repos/AoC2022/AoC2022/data/output/";

		output_file.open(path + "output08_data.txt", std::fstream::out);
		std::cout << "data" << std::endl;
		this->printMatrix(data, output_file);
		output_file.close();

		output_file.open(path + "output08_UP.txt", std::fstream::out);
		std::cout << "Up visibility" << std::endl;
		this->printMatrix(mVisible_top, output_file);
		output_file.close();

		output_file.open(path + "output08_DOWN.txt", std::fstream::out);
		std::cout << "Down visibility" << std::endl;
		this->printMatrix(mVisible_bottom, output_file);
		output_file.close();

		output_file.open(path + "output08_LEFT.txt", std::fstream::out);
		std::cout << "Left visibility" << std::endl;
		this->printMatrix(mVisible_left, output_file);
		output_file.close();

		output_file.open(path + "output08_RIGHT.txt", std::fstream::out);
		std::cout << "Right visibility" << std::endl;
		this->printMatrix(mVisible_right, output_file);
		output_file.close();

		output_file.open(path + "output08_FULL.txt", std::fstream::out);
		std::cout << "All directions visibility" << std::endl;
		this->printMatrix(mVisible, output_file);
		output_file.close();

		output_file.open(path + "output08_SCORE.txt", std::fstream::out);
		std::cout << "Scenic Score" << std::endl;
		this->printMatrix(mScenic_score, output_file);
		output_file.close();
	}

	template <typename T>
	void printMatrix(const 	std::vector<std::vector<T>>& matrix, std::fstream& file)
	{
		int rows = matrix.size();
		int cols = matrix[0].size();
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				file << matrix[i][j] << ",";
			}
			file << std::endl;
		}
	}


};
