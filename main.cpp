// Source File

#include <iostream>
#include "Market.h"
#include "Algorithm.h"
#include "io.h"
using namespace std;

void tests();

int main() {

    tests();

    return 1;
}

bool shareTests(){
    string cname = "NEU";
    vector<SharePrice> NEUPriceHistory = {{Date("10/25/2024"), 50}, {Date("10/26/2024"), 55}, {Date("10/27/2024"), 42}, {Date("10/28/2024"), 76}};
    Company northeastern = Company(cname, NEUPriceHistory);
    Share NEUS1 = Share(northeastern);
    cout<<NEUS1.print()<< endl;
    cout<<northeastern.printHistory();
    return true;
}

bool testDate(){
    Date test_date = Date("5/24/2004");
    cout<<"test_date: "<<test_date.print()<<endl;
    time_t test_time = convertToTime_t(test_date);
    cout<<"test_time: "<<test_time<<endl;
    Date same_date = Time_tToDate(test_time);
    cout<<"Converted back to date: "<<same_date.print()<<endl;
    if(test_date.print() == same_date.print()) return true;
    return false;
}

void tests(){
    if(testDate()) cout<<"\n\nDate tests: successful\n\n";
    if(shareTests()) cout<<"\n\nShare tests: successful\n\n";
}
