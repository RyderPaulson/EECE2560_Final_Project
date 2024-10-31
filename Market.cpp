#include "Market.h"
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

/*
tm dateToTime(string date){
    int i = 0;
    string mm, dd, yyyy;
    tm cDate;

    while(date[i] != '/') {
        mm.push_back(date[i]);
        i++;
    }
    i++;
    while(date[i] != '/') {
        dd.push_back(date[i]);
        i++;
    }
    i++;
    while(date[i]) {
        yyyy.push_back(date[i]);
        i++;
    }


    cDate.tm_mon = stoi(mm);
    cDate.tm_mday = stoi(dd);
    cDate.tm_year = stoi(yyyy);

    return cDate;
}
 */

// ----------------------------------------------------------------

Date::Date(){
    this->month = 1;
    this->day = 1;
    this->year = 2024;
}

Date::Date(string date){
    int i = 0;
    string mm, dd, yyyy;

    while(date[i] != '/') {
        mm.push_back(date[i]);
        i++;
    }
    i++;
    while(date[i] != '/') {
        dd.push_back(date[i]);
        i++;
    }
    i++;
    while(date[i]) {
        yyyy.push_back(date[i]);
        i++;
    }


    this->month = stoi(mm);
    this->day = stoi(dd);
    this->year = stoi(yyyy);
}

Date::Date(string m, string d, string y) {
    this->month = stoi(m);
    this->day = stoi(d);
    this->year = stoi(y);
}

Date::Date(int m, int d, int y) {
    this->month = m;
    this->day = d;
    this->year = y;
}

time_t Date::convertToTime_t() {
    return 0;
}

Date Date::operator+(Date *other) {
    Date sum = Date();
    return sum;
}

Date Date::operator-(Date *other) {
    Date difference = Date();
    return difference;
}

/*
ostream &Date::operator<<(ostream &os) {
    os<<this->month<<"/"<<this->day<<"/"<<this->year;
    return os;
}
 */

string Date::print() {
    ostringstream oss;
    oss<<this->month<<"/"<<this->day<<"/"<<this->year;
    return oss.str();
}



// ----------------------------------------------------------------

Company::Company() {
    this->ticker = "AAA";
    this->curr_share_price = {Date(), 0};
    this->price_history = {this->curr_share_price};

}

Company::Company(string t, vector<SharePrice> ph) {
    this->ticker = t;
    this->price_history = ph;
    this->curr_share_price = price_history.back();
}

string Company::print() {
    return this->ticker;
}

string Company::printHistory() {
    ostringstream oss;
    oss << "Price History for " << ticker << endl;
    for(int i = 0; i < price_history.size(); i++) {
        oss << "Time: " << price_history[i].t.print() << " | Price: " << fixed << setprecision(2) << price_history[i].price << endl;
    }
    return oss.str();
}

string Company::getTicker(){
    return this->ticker;
}

SharePrice Company::getPrice(){
    return this->curr_share_price;
}

vector<SharePrice> Company::getPriceHistory(){
    return this->price_history;
}

// ----------------------------------------------------------------

Share::Share(Company c) {
    this->company = c;
    this->ticker = c.getTicker();
    this->updatePrice();
    this->buy_price = this->current_price;
}

string Share::print() {
    ostringstream oss;

    oss << this->company.print() << " | " << fixed << setprecision(2) << this->current_price.price;
    return oss.str();
}

Company Share::getCompany() {
    return company;
}

void Share::updatePrice() {
    this->current_price = this->company.getPrice();
}
