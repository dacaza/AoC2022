#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <set>
#include <utility>
#include <algorithm>


void ReadFile01(const char* filename, std::vector<int>& data);
void ReadFile(const char* filename, std::vector<int>& data);
void ReadFile(const char* filename, std::vector<float>& data);
void ReadFile(const char* filename, std::vector<std::pair<std::string, int>>& data);
void ReadFile(const char* filename, std::vector<std::pair<std::string, std::string>>& data);
void ReadFile(const char* filename, std::vector<std::string>& data);
void ReadFile(const char* filename, std::vector<int>& data, std::vector<std::vector<std::vector<std::pair<int,bool>>>>& boards);
void ReadFile(const char* filename, std::vector<int>& x0, std::vector<int>& y0, std::vector<int>& x1, std::vector<int>& y1);
void ReadFile(const char* filename, std::vector<std::vector<std::string>>& patern, std::vector<std::vector<std::string>>& output);
void ReadFile(const char* filename, std::vector<std::vector<int>>& data);
void ReadFile12(const char* filename, std::vector<std::string>& data);
void ReadFile13(const char* filename, std::vector<std::pair<int, int>>& data, int& x, int& y);
void ReadFile14(const char* filename, std::string& polymerTemplate, std::map<std::string, std::string>& input);
void ReadFile16(const char* filename, std::string& data);
//void ReadFile19(const char* filename, std::vector<std::vector<Vec>>& scanners);
void ReadFile20(const char* filename, std::vector<bool>& iea, std::vector<std::vector<bool>>& image);
void ReadFile22(const char* filename, std::vector<bool>& states, std::vector<std::pair<int, int>>& X, std::vector<std::pair<int, int>>& Y, std::vector<std::pair<int, int>>& Z);

