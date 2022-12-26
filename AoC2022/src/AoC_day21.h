#pragma once
#include "AoC22.h"

enum class Oper {sum, res, mul, div, none};

struct Node
{
	std::string name;
	Oper oper;
	int val = 0;

	std::vector<Node*> children;
	//Node* parent;
};

class AoC22_21 : public AoC22
{
private:
	std::vector<Node*> data;

public:
	AoC22_21(const std::string& Filename) : AoC22(Filename)
	{
		this->solve();
	}

private:
	void loadData() override
	{

		//root: pppw + sjmn
		//dbpl : 5

		Node* current=nullptr;

		data.clear();
		for (std::string line : this->rawData)
		{
			std::string str, strA, strB;
			std::string oper;

			str = line;
			this->split(str, ":", strA, strB);

			int i = 0;
			while (i < data.size())
			{
				if (strA == data[i]->name)
				{
					current = data[i];
					break;
				}
				i++;
			}
			if (i >= data.size())
			{
				data.push_back(new Node);
				data.back()->name = strA;
				current = data.back();
			}

			if (strB.length() > 4)
			{
				strA = strB.substr(1, 4);

				int i = 0;
				while (i < data.size())
				{
					if (strA == data[i]->name)
					{
						current->children.push_back(data.back());
						break;
					}
					i++;
				}
				if (i >= data.size())
				{
					data.push_back(new Node);
					data.back()->name = strA;
					current->children.push_back(data.back());
				}

				oper = strB.substr(6, 1);
				if (oper == "+")
					current->oper = Oper::sum;
				else if (oper == "-")
					current->oper = Oper::res;
				else if (oper == "*")
					current->oper = Oper::mul;
				else if (oper == "/")
					current->oper = Oper::div;

				strA = strB.substr(8, 4);
				i = 0;
				while (i < data.size())
				{
					if (strA == data[i]->name)
					{
						current->children.push_back(data.back());
						break;
					}
					i++;
				}
				if (i >= data.size())
				{
					data.push_back(new Node);
					data.back()->name = strA;
					current->children.push_back(data.back());
				}
			}
			else
			{
				current->oper = Oper::none;
				strA = strB.substr(1, str.length() - 1);
				current->val = std::stoi(strA);				
			}
		}
	}

	std::string part1() override
	{
		std::cout << "AoC 2022 - Day 21 - Part 1";
		return "R1";
	}

	std::string part2() override
	{
		std::cout << "AoC 2022 - Day 21 - Part 2";
		return "R2";
	}

};
