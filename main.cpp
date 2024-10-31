// Source File

#include <iostream>
#include "lib/Market.h"
#include "lib/Algorithm.h"
#include "lib/io.h"
using namespace std;

int main() {
    string cname = "NEU";
    vector<SharePrice> NEUPriceHistory = {{Date("10/25/2024"), 50}, {Date("10/26/2024"), 55}, {Date("10/27/2024"), 42}, {Date("10/28/2024"), 76}};
    Company northeastern = Company(cname, NEUPriceHistory);
    Share NEUS1 = Share(northeastern);
    cout<<NEUS1.print()<< endl;
    cout<<northeastern.printHistory();
    return 0;
}