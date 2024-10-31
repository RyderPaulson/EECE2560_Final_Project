#include "Market.h"
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

tm dateToTime(string date){
    int i = 0;
    string mm, dd, yyyy;
    tm cDate;
    while(reinterpret_cast<const char *>(date[i]) != "/") {
        mm.append(reinterpret_cast<const char *>(date[i]));
        i++;
    }
    i++;
    while(reinterpret_cast<const char *>(date[i]) != "/") {
        dd.append(reinterpret_cast<const char *>(date[i]));
        i++;
    }
    i++;
    while(date[i]) {
        yyyy.append(reinterpret_cast<const char *>(date[i]));
        i++;
    }
    cDate.tm_mon = stod(mm);
    cDate.tm_mday = stod(dd);
    cDate.tm_year = stod(yyyy);

    return cDate;
}

// ----------------------------------------------------------------

/*
Market::Market() {

}

string Market::print() {
    ostringstream oss;
    oss << "Companies in Market" << endl;
    for(int i = 0; i < companies.size(); i++){
        oss << companies[i].getTicker();
        if (i%7 == 1) oss << endl;
    }
    return oss.str();
}
 */

// ----------------------------------------------------------------

Company::Company() {
    this->ticker = "AAA";
    this->curr_share_price = {0, 0};
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
        oss << "Time: " << price_history[i].t << " | Price: " << fixed << setprecision(2) << price_history[i].price << endl;
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