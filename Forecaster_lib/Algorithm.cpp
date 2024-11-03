#include "Algorithm.h"
#include "Market.h"
using namespace std;

// Entrypoint
SharePrice forecastValue(Company company){
    vector<SharePrice> price_history = company.getPriceHistory();
    addTime_T(price_history);
    normalizeXAxis(price_history);
    double mean_difference = volatility(price_history);
    vector<SharePrice> mean_line = meanLine(price_history);
    double standard_deviation = standardDeviation(price_history);

}

vector<SharePrice> meanLine(vector<SharePrice>) {

}

void normalizeXAxis(vector<SharePrice>& vec) {
    double norm_factor = vec[0].std_t;
    for(int i = 0; i < vec.size() - 1; i++) {
        vec[i].std_t -= norm_factor;
    }
}

double volatility(vector<SharePrice>& vec) {
    double numerator = 0;
    for(int i = 0; i < vec.size() - 1; i++){
        numerator += vec[i+1].price - vec[i].price;
    }
    return numerator/vec.size();
}

double standardDeviation(vector<SharePrice> vec) {

}