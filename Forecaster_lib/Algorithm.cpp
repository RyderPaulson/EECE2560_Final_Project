#include "Algorithm.h"
#include "Market.h"
using namespace std;

Regression::Regression() {
    normalized = false;
    calculatedMeanLine = false;
    coeff = 0;
    const_term = 0;
    sum_y = 0;
    sum_y_square = 0;
    sum_x_square = 0;
    sum_x = 0;
    sum_xy = 0;
}

Regression::Regression(vector<SharePrice>& vec) {
    data = vec;

    normalizeXAxis();
    standardInterval();

    for(int i =0; i < vec.size(); i++) {
        sum_x += data[i].std_t;
        sum_y += data[i].price;
        sum_xy += data[i].std_t * data[i].price;
        sum_x_square += data[i].std_t * data[i].std_t;
        sum_y_square += data[i].price * data[i].price;
    }

    calculateCoefficient();
    calculateConstantTerm();

    for(int i = 0; i < data.size(); i++) {
        mean_line.push_back(meanLineFofX(data[i].std_t));
    }
    calculatedMeanLine = true;

    calcVolatility();
    standardDeviation();
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
    coeff = numerator / denominator;
    return coeff;
}

double Regression::calculateConstantTerm()
{
    double N = data.size();
    double numerator = sum_y * sum_x_square - sum_x * sum_xy;
    double denominator = N * sum_x_square - sum_x * sum_x;
    const_term = numerator / denominator;
    return const_term;
}

void Regression::forecastMeanLine(int n) {
    vector<SharePrice> new_values;
    for(int i = 0; i < n; i++) {
        new_values.push_back(meanLineFofX(std_interval*(mean_line.size() + i)));
    }
    mean_line.insert(mean_line.end(), new_values.begin(), new_values.end());
}

void Regression::forecastFutureValues(int n) {
    forecastMeanLine(n);

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
    sp.price = coeff * x + const_term;
    return sp;
}

double Regression::standardDeviation() {
    int n = data.size();

    double mean_y = sum_y / n;

    double sum_x_diff_squared = 0, sum_y_diff_squared = 0;
    for (int i = 0; i < n; i ++) {
        // sum_y_diff_squared += ( - mean_y) * (point.y - mean_y);
    }
    double variance_x = sum_x_diff_squared / (n - 1);
    double variance_y = sum_y_diff_squared / (n - 1);

    double x_std_dev = sqrt(variance_x);
    double y_std_dev = sqrt(variance_y);
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