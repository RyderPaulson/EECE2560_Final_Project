#include "Algorithm.h"
#include "Market.h"
using namespace std;

Regression::Regression() {
    normalized = false;
    calculatedMeanLine = false;
    slope = 0;
    intercept = 0;
    sum_y = 0;
    sum_y_square = 0;
    sum_x_square = 0;
    sum_x = 0;
    sum_xy = 0;
}

Regression::Regression(vector<SharePrice>& vec, int n) {
    // ------------------------------- Initial setup -------------------------------
    data = vec;

    normalizeXAxis();
    standardInterval();

    // ------------------------------- Calculating mean line -------------------------------
    for(int i =0; i < vec.size(); i++) {
        sum_x += data[i].std_t;
        sum_y += data[i].price;
        sum_xy += data[i].std_t * data[i].price;
        sum_x_square += data[i].std_t * data[i].std_t;
        sum_y_square += data[i].price * data[i].price;
    }

    calculateCoefficient();
    calculateConstantTerm();

    forecastMeanLine(n);
    calculatedMeanLine = true;

    // ------------------------------- Forecasting Values -------------------------------
    calcVolatility();
    standardDeviation();
    forecastFutureValues(n);
}

void Regression::importData(vector<SharePrice> &vec, int n) {
    // ------------------------------- Initial setup -------------------------------
    data = vec;

    normalizeXAxis();
    standardInterval();

    // ------------------------------- Calculating mean line -------------------------------
    for(int i =0; i < data.size(); i++) {
        sum_x += data[i].std_t;
        sum_y += data[i].price;
        sum_xy += data[i].std_t * data[i].price;
        sum_x_square += data[i].std_t * data[i].std_t;
        sum_y_square += data[i].price * data[i].price;
    }

    calculateCoefficient();
    calculateConstantTerm();

    forecastMeanLine(n);

    // ------------------------------- Forecasting Values -------------------------------
    calcVolatility();
    standardDeviation();
    forecastFutureValues(n);
}

void Regression::normalizeXAxis() {
    double norm_factor = data[0].std_t;
    for(int i = 0; i < data.size() - 1; i++) {
        data[i].std_t -= norm_factor;
    }
    normalized = true;
}

double Regression::calcVolatility() {
    double numerator = 0;
    for(int i = 0; i < data.size() - 1; i++){
        numerator += data[i+1].price - data[i].price;
    }
    volatility = numerator/data.size();
    return numerator/data.size();
}

double Regression::calculateCoefficient() {
    double N = data.size();
    float numerator = (N * sum_xy - sum_x * sum_y);
    double denominator = (N * sum_x_square - sum_x * sum_x);
    slope = numerator / denominator;
    return slope;
}

double Regression::calculateConstantTerm()
{
    double N = data.size();
    double numerator = sum_y * sum_x_square - sum_x * sum_xy;
    double denominator = N * sum_x_square - sum_x * sum_x;
    intercept = numerator / denominator;
    return intercept;
}

void Regression::forecastMeanLine(int n) {
    vector<SharePrice> new_values;
    for(int i = 0; i < n; i++) {
        new_values.push_back(meanLineFofX(std_interval*(mean_line.size() + i)));
    }
    mean_line.insert(mean_line.end(), new_values.begin(), new_values.end());
    calculatedMeanLine = true;
}

void Regression::forecastFutureValues(int n) {
    double deviation;
    SharePrice sp;

    sp.std_t = data.end()->std_t;
    deviation = data[size].price - mean_line[size].price;
    sp.price = deviation/std_deviation*volatility;
    for(int i = 1; i < n; i++) {
        sp.std_t = std_interval*(size+i);
        deviation = data[i-1].price - mean_line[i-1].price;
        sp.price = deviation/std_deviation*volatility;
        forecasted_line.push_back(sp);
    }
}

SharePrice Regression::meanLineFofX(time_t x) {
    SharePrice sp;
    sp.std_t = x;
    sp.price = slope * x + intercept;
    return sp;
}

double Regression::standardDeviation() {
    int n = initial_size;

    double mean_y = sum_y / n;

    double sum_y_diff_squared = 0;
    for (int i = 0; i < n; i ++) {
        sum_y_diff_squared += pow((data[i].price - mean_y), 2);
    }
    double variance_y = sum_y_diff_squared / (n - 1);

    std_deviation = sqrt(variance_y);
    return std_deviation;
}

double Regression::standardInterval() {
    double sum = 0;
    if(!normalized) normalizeXAxis();
    for(int i = 0; i < data.size(); i++) {
        sum += data[i].std_t;
    }
    std_interval = sum/data.size();
    return std_interval;
}

int Regression::getSize() {
    return size;
}

vector<SharePrice>& Regression::getMeanLine() {
    return mean_line;
}

vector<SharePrice>& Regression::getForecast() {
    return forecasted_line;
}

double Regression::getStandardDeviation() {
    return std_deviation;
}







