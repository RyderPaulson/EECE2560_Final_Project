#include "Algorithm.h"
#include "Market.h"
using namespace std;

// Entrypoint
SharePrice forecastValue(Company company){
    vector<SharePrice> price_history = company.getPriceHistory();
    vector<SharePrice> mean_line = meanLine(price_history);
    double mean_derivative = volatility(price_history);
    double standard_deviation = standardDeviation(price_history);

}

vector<SharePrice> meanLine(vector<SharePrice>) {

}

double volatility(vector<SharePrice>) {

}

double standardDeviation(vector<SharePrice>) {

}