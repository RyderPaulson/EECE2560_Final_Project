/*
 * General tips for using these classes:
 * 1. If you need to print one out, use a normal cout, ostream, oss,
 * etc but then use the .print() method. This will returns a string
 * which will then be printed.
 * 2. SharePrice has two time variables. t is better for human readability
 * while std_t is better for math.
 * 3. Broad class structure:
 *      a. Company - vector of SharePrices (price_history)
 *      b. SharePrice - kindof like an (x,y) point where
 *      time is x and y is price. std_t should be used for math
 *      and t should be used for io.
 *      c. Date - a class representing a date. Can be constructed
 *      using one string ('mm/dd/yyyy'), 3 strings ('mm', 'dd', 'yyyy')
 *      or 3 ints (m, d, y).
 *
 * I ended up not really using the Share class for anything.
 */

#include <string>
#include <vector>
#include <ctime>
using namespace std;

#ifndef EECE2560_FINAL_PROJECT_MARKET_H
#define EECE2560_FINAL_PROJECT_MARKET_H

class Date;
struct SharePrice;
class Share;
class Company;

Date Time_tToDate(time_t time);
time_t convertToTime_t(Date date);
void addTime_T(vector<SharePrice>& vec);
vector<SharePrice> readCSV(const std::string& filename);
SharePrice parseCSVLine(std::string& line);
string formatForMatlab(const Company& company, const std::vector<SharePrice>& meanLine, const std::vector<SharePrice>& forecasted);
void plotCompanyData(Company& company, const std::vector<SharePrice>& meanLine, const std::vector<SharePrice>& forecasted);

class Date{
public:
    int month, day, year;

    Date();
    Date(string date);
    Date(string m, string d, string y);
    Date(int m, int d, int y);
    Date operator+(Date* other);
    Date operator-(Date* other);
    string print() const;
};

struct SharePrice{
    Date t;
    time_t std_t;
    double price;
};

class Company{
private:
    string ticker;
    SharePrice curr_share_price;
    vector<SharePrice> price_history;
public:
    Company();
    Company(string t, vector<SharePrice> ph);
    Company(string& t, string& filename);
    string print();
    string printHistory();
    string getTicker();
    SharePrice getPrice();
    vector<SharePrice> getPriceHistory();
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
