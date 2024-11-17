#include "Algorithm.h"
#include "Market.h"
#include <algorithm>
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

Regression::Regression(vector<SharePrice>& vec, int n, Company &c) {
    // ------------------------------- Initial setup -------------------------------
    company = &c;
    initial_size = vec.size();
    size = initial_size;
    slope = 0;
    intercept = 0;
    sum_y = 0;
    sum_y_square = 0;
    sum_x_square = 0;
    sum_x = 0;
    sum_xy = 0;
    volatility = 0;
    std_interval = 0;
    std_deviation = 0;

    data = vec;

    // Reverse if not in ascending order
    if(data[1].std_t<=data[0].std_t) {
        reverse(data.begin(), data.end());
    }

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

    size = mean_line.size();

    denormalizeXAxis(vec[initial_size-1].std_t);
    addDate(mean_line);
    addDate(forecasted_line);
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
    for(int i = 0; i < data.size(); i++) {
        data[i].std_t -= norm_factor;
    }
    normalized = true;
}

void Regression::denormalizeXAxis(time_t norm_factor) {
    for(int i = 0; i < initial_size; i++) {
        data[i].std_t += norm_factor;
    }
    for(int i = 0; i < mean_line.size(); i++) {
        mean_line[i].std_t += norm_factor;
    }
    for(int i = 0; i < forecasted_line.size(); i++) {
        forecasted_line[i].std_t += norm_factor;
    }
    normalized = false;
}

double Regression::calcVolatility() {
    double numerator = 0;
    for(int i = 0; i < data.size() - 1; i++){
        numerator += data[i+1].price - data[i].price;
    }
    volatility = numerator/data.size();
    return volatility;
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
    for(int i = 0; i < initial_size; i++) {
        mean_line.push_back(meanLineFofX(data[i].std_t));
    }
    for(int i = initial_size; i < initial_size + n; i++) {
        mean_line.push_back(meanLineFofX(std_interval*(i)));
    }
    calculatedMeanLine = true;
}

void Regression::forecastFutureValues(int n) {
    double deviation = 0, change = 0;
    SharePrice sp;

    forecasted_line.push_back(data[initial_size - 1]);
    for(int i = 1; i < n; i++) {
        sp.std_t = mean_line[initial_size - 1 + i].std_t;
        deviation = forecasted_line[i-1].price - mean_line[initial_size - 1 + i].price;
        change = 2 * deviation/std_deviation*volatility;
        sp.price = forecasted_line[i-1].price - addRandomness(change);

        forecasted_line.push_back(sp);
    }
}

double Regression::addRandomness(double price) {
    // Random number generator
    random_device rd;
    mt19937 generator(rd());

    int value;

    normal_distribution normal(25.0, std_deviation);
    binomial_distribution binomial(static_cast<int>(std_deviation), 0.5);
    bernoulli_distribution bernoulli(0.5);

    value = binomial(generator);
    //value = normal(generator);
    price = price * value;

    int upOrDown = bernoulli(generator);

    if(upOrDown == 1) return -1 * price;

    return price;
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
    std_interval = data[initial_size-1].std_t/initial_size;
    return std_interval;
}

int Regression::getSize() {
    return size;
}

int Regression::getInitialSize() {
    return initial_size;
}

vector<SharePrice>& Regression::getMeanLine() {
    return mean_line;
}

vector<SharePrice>& Regression::getForecast() {
    return forecasted_line;
}

Date Regression::getNthDate(int n) {
    return mean_line[n].t;
}

double Regression::getNthPrice(int n) {
    // Returns the nth element of data
    return data[n].price;
}

double Regression::getStandardDeviation() {
    return std_deviation;
}







