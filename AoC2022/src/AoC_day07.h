#pragma once
#include "AoC22.h"


enum class filetype {file, dir};

struct Node
{
	std::string name;
	int size;
	filetype fileType;

	std::vector<Node*> children;
	Node* parent; 
};


class AoC22_07 : public AoC22
{
private:
	std::vector<std::string> data;
	std::vector<Node*> nodes;

public:
	AoC22_07(const std::string& Filename) : AoC22(Filename)
	{
		this->solve();
	}

private:
	void loadData() override
	{
		data.clear();
		nodes.clear();
		for (std::string line : this->rawData)
		{
			data.push_back(line);
		}

		nodes.push_back(new Node);
		nodes[0]->name = "/";
		nodes[0]->size = 0;
		nodes[0]->parent = nullptr;
		nodes[0]->fileType = filetype::dir;

		Node* current = nodes[0];

		size_t i = 1;
		while (i < data.size())
		{
			// Comands
			// Go up	
			if (data[i][0] == '$' && data[i].substr(2, 2) == "cd" && data[i][5] == '.')
			{
				current = current->parent;
				i++;
			}

			// Go to root
			if (data[i][0] == '$' && data[i].substr(2, 2) == "cd" && data[i][5] == '/')
			{
				current = nodes[0];
				i++;
			}

			// Change dir
			if (data[i][0] == '$' && data[i].substr(2, 2) == "cd" && data[i][5] != '.' && data[i][5] != '/')
			{
				std::string dirname = data[i].substr(5, data[i].length() - 5);
				for (size_t j = 0; j < current->children.size(); j++)
					if (dirname == current->children[j]->name)
					{
						current = current->children[j];
						i++;
						break;
					}
			}

			// List
			if (data[i][0] == '$' && data[i].substr(2, 2) == "ls") // List
			{
				i++;
			}

			// Add files
			// Add Dir
			if (data[i][0] != '$' && data[i].substr(0, 1) == "d")
			{
				nodes.push_back(new Node);
				std::string dir;
				std::string dirname;
				this->split(data[i], " ", dir, dirname);
				nodes.back()->name = dirname;
				nodes.back()->size = 0;
				nodes.back()->parent = current;
				nodes.back()->fileType = filetype::dir;
				current->children.push_back(nodes.back());
				i++;
			}

			//Add file
			if (data[i][0] != '$' && data[i].substr(0, 1) != "d")
			{
				nodes.push_back(new Node);
				std::string filename;
				std::string filesize;
				this->split(data[i], " ", filesize, filename);
				nodes.back()->name = filename;
				nodes.back()->size = std::stoi(filesize);
				nodes.back()->parent = current;
				nodes.back()->fileType = filetype::file;
				current->children.push_back(nodes.back());
				i++;
			}

		}

	}

	int getDirSize(Node* node)
	{
		int sum = 0;

		if (node->children.size() == 0)
			sum += 0;
		else
			for (size_t i = 0; i < node->children.size(); i++)
			{
				if (node->children[i]->fileType == filetype::file)
					sum += node->children[i]->size;
				else
					sum += this->getDirSize(node->children[i]);
			}

		return sum;
	}

	void printNodes(Node* node, std::string& tab)
	{
		if (node->fileType == filetype::dir)
		{
			std::cout << tab << node->name << " (dir)" << std::endl;
		}
		else
			std::cout << tab << node->name << std::endl;


		if (node->children.size() != 0)
			for (size_t i = 0; i < node->children.size(); i++)
			{

				this->printNodes(node->children[i], tab);
			}
		else
			return;
	}


	std::string part1() override
	{
		std::vector<int> sizes(nodes.size(), 0);
		int result = 0;

		for (size_t i = 0; i < nodes.size(); i++)
			if (nodes[i]->fileType == filetype::dir)
			{
				sizes[i] = getDirSize(nodes[i]);
				//std::cout << i << " " << sizes[i] << std::endl;
				if (sizes[i] <= 100000)
					result += sizes[i];
			}

		//std::string tab = "-";
		//this->printNodes(nodes[0],tab);

		std::cout << "AoC 2022 - Day 07 - Part 1";
		return std::to_string(result);
	}

	std::string part2() override
	{

		int TOTAL_SIZE = 70000000;
		int UNUSED_SPACE = 30000000;

		std::vector<int> sizes(nodes.size(), 0);

		for (size_t i = 0; i < nodes.size(); i++)
			if (nodes[i]->fileType == filetype::dir)
				sizes[i] = getDirSize(nodes[i]);

		int free_space = TOTAL_SIZE - sizes[0];
		int space_to_delete = UNUSED_SPACE - free_space;

		std::sort(sizes.begin(), sizes.end());

		int result = 0;
		for (int i = 0; i < sizes.size(); i++)
			if (sizes[i] > space_to_delete)
			{
				result = sizes[i];
				break;
			}


		std::cout << "AoC 2022 - Day 07 - Part 2";
		return std::to_string(result);
	}

};
