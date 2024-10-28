/*
Includes class implementations of:
    - Individual share in a company
    - A company
    - The market
*/

#include <string>
#include <vector>
#include <ctime>
using namespace std;

#ifndef EECE2560_FINAL_PROJECT_MARKET_H
#define EECE2560_FINAL_PROJECT_MARKET_H

class Share;
class Company;
class Market;
struct SharePrice;

struct SharePrice{
    time_t t;
    double price;
};

class Market{
private:
    vector<Company> companies;
public:
    Market();
    string print();
};

class Company{
private:
    string ticker;
    SharePrice curr_share_price;
    vector<SharePrice> price_history;
public:
    Company();
    Company(string t, vector<SharePrice> ph);
    string print();
    string printHistory();
    string getTicker();
    SharePrice getPrice();
};

class Share{
private:
    Company company;
    string ticker;
    SharePrice buy_price, current_price;

public:
    Share(Company C);
    string print();
    Company getCompany();
    void updatePrice();
};

#endif //EECE2560_FINAL_PROJECT_MARKET_H
