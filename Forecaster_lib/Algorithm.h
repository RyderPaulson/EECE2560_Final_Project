/*
 * All functions used for forecasting future stock values.
 */

#include "Market.h"
#include <string>
#include <ctime>
#include <cmath>
#include <random>
using namespace std;

#ifndef EECE2560_FINAL_PROJECT_ALGORITHM_H
#define EECE2560_FINAL_PROJECT_ALGORITHM_H

class Regression{
private:
    vector<SharePrice> data;
    vector<SharePrice> modified_data;
    bool normalized, calculatedMeanLine;
    int initial_size, size;
    double sum_xy;
    double sum_x;
    double sum_y;
    double sum_x_square;
    double sum_y_square;
    double volatility;
    double std_interval;
    double std_deviation;

    // Functions for generating regression
    void normalizeXAxis();
    void denormalizeXAxis(time_t norm_factor);
    double calcVolatility();
    double calculateCoefficient();
    double calculateConstantTerm();
    void forecastMeanLine(int n);
    void forecastFutureValues(int n);
    double addRandomness(double price);
    SharePrice meanLineFofX(time_t x);
    double standardDeviation();
    double standardInterval();
public:
    vector<SharePrice> mean_line;
    // Mean line should have values for every original data point
    // and every forecasted data point

    vector<SharePrice> forecasted_line;
    // Index 0 of the forecasted line should be the same as the last
    // element in the original data so that the line looks continuous

    double slope, intercept;
    Company* company;   // Point to company the data is from.

    // Functions for entering and returning values from regression
    Regression();
    Regression(vector<SharePrice>& vec, int n, Company &c);
    void importData(vector<SharePrice>& vec, int n);
    int getSize();
    int getInitialSize();
    vector<SharePrice>& getMeanLine();
    vector<SharePrice>& getForecast();
    Date getNthDate(int n);
    double getNthPrice(int n);
    double getStandardDeviation();
};


#endif //EECE2560_FINAL_PROJECT_ALGORITHM_H
