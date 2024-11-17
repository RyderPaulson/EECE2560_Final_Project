#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <filesystem>
#include "Market.h"
#include "Algorithm.h"
using namespace std;

#ifndef EECE2560_FINAL_PROJECT_IO_H
#define EECE2560_FINAL_PROJECT_IO_H

vector<SharePrice> readCSV(const std::string& filename);
bool outputCSV(Regression forecast);

#endif //EECE2560_FINAL_PROJECT_IO_H
