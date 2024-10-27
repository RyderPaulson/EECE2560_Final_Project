// Source File

#include <iostream>
#include <vector>
#include <cmath>
#include "Market.h"
using namespace std;


int main() {
    string cname = "NEU";
    vector<SharePrice> NEUPriceHistory = {{0, 50}, {1, 55}, {2, 42}, {3, 76}};
    Company northeastern = Company(cname, NEUPriceHistory);
    Share NEUS1 = Share(northeastern);
    cout<<NEUS1.print()<< endl;
    cout<<northeastern.printHistory();
    return 0;
}