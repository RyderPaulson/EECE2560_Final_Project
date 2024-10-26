/*
Includes class implementations of:
    - Individual share in a company
    - A company
    - The market
*/

#include <string>
#include <vector>
using namespace std;

#ifndef EECE2560_FINAL_PROJECT_MARKET_H
#define EECE2560_FINAL_PROJECT_MARKET_H

class User;
class Share;
class Company;
class Market;

class Market{
private:
    vector<Company> companies;
public:
    Market();
    void print();
};

class User{
private:
    string username;
    string password;
    vector<Share> owned_shares;
public:
    User();
    void print();
};

class Company{
private:
    vector<Share> owned_shares;
    string ticker;
    double share_price;
public:
    Company();
    void print();
};

class Share{
private:
    Company comp;
    string ticker;
    string owner;
    double buy_price, current_price;

public:
    Share();
    void print();
    Company tick();
    void updatePrice();

};

#endif //EECE2560_FINAL_PROJECT_MARKET_H
