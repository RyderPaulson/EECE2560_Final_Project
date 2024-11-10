#include <fstream>
#include <string>
#include "Market.h"
#include "Algorithm.h"
using namespace std;

#ifndef EECE2560_FINAL_PROJECT_IO_H
#define EECE2560_FINAL_PROJECT_IO_H

std::vector<SharePrice> readCSV(const std::string& filename);
void outputCSV(Regression forecast);

#endif //EECE2560_FINAL_PROJECT_IO_H
