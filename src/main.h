#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <filesystem>
#include <stdexcept>

using namespace std;

bool is_valid_char(char c);
int deal_with_arg(int argc, char* argv[], int& func_type, char& head, char& tail, char& jinz, bool& loop, string& filename);
ifstream open_file(const string& filename);
vector<char*> extract_words(ifstream& file);