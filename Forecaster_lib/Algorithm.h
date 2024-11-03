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

class Regression{
private:
    vector<SharePrice> data;
    vector<SharePrice> modified_data;
    bool normalized, calculatedMeanLine;
    int initial_size, size;
    double coeff;
    double const_term;
    double sum_xy;
    double sum_x;
    double sum_y;
    double sum_x_square;
    double sum_y_square;
    double volatility;
    double std_interval;
    double std_deviation;

public:
    vector<SharePrice> mean_line;
    vector<SharePrice> forecasted_line;
    double slope, intercept;

    Regression();
    Regression(vector<SharePrice>& vec);
    void normalizeXAxis();
    double calcVolatility();
    double calculateCoefficient();
    double calculateConstantTerm();
    void forecastMeanLine(int n);
    void forecastFutureValues(int n);
    SharePrice meanLineFofX(time_t x);
    double standardDeviation();
    double standardInterval();
};


#endif //EECE2560_FINAL_PROJECT_ALGORITHM_H
