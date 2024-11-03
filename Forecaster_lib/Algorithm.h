/*
 * All functions used for forecasting future stock values.
 */

#include "Market.h"
#include <string>
#include <ctime>
#include <cmath>
using namespace std;

#ifndef EECE2560_FINAL_PROJECT_ALGORITHM_H
#define EECE2560_FINAL_PROJECT_ALGORITHM_H

SharePrice forecastValue(Company company); // Entrypoint for algorithm
vector<SharePrice> meanLine(vector<SharePrice> vec);
void normalizeXAxis(vector<SharePrice>& vec);
double volatility(vector<SharePrice>& vec);
double standardDeviation(vector<SharePrice>& vec);

#endif //EECE2560_FINAL_PROJECT_ALGORITHM_H
