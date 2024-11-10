#include "Market.h"
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <fstream>
#include <stdexcept>

// Converts a ctime time_t var to the Date class.
Date Time_tToDate(time_t time){
    // This section was pulled from online.

    Date date;
    // Convert to UTC tm structure
    tm* utcTime = gmtime(&time);
    if (!utcTime) {
        throw runtime_error("Failed to convert time.");
    }

    // Adjust for New York time zone
    // New York is typically UTC-5 hours (EST) or UTC-4 hours (EDT during daylight saving time)
    const int NY_STANDARD_OFFSET = -5; // UTC-5 hours
    const int NY_DST_OFFSET = -4;      // UTC-4 hours for daylight saving time

    // Determine if daylight saving time is in effect
    bool isDST = utcTime->tm_mon > 2 && utcTime->tm_mon < 10; // April to October (simplified check)
    int nyOffset = isDST ? NY_DST_OFFSET : NY_STANDARD_OFFSET;

    // Adjust UTC time by New York offset (in seconds)
    time_t nyTimeT = time + nyOffset * 3600;

    // Convert to local New York time as tm struct
    tm* nyTime = gmtime(&nyTimeT);
    if (!nyTime) cerr << "Failed to convert time to New York time." << endl;
    // End of section from online

    date.month = nyTime->tm_mon + 1;
    date.day = nyTime->tm_mday;
    date.year = nyTime->tm_year+1900;

    return date;
}

// Converts a date class to the time_t var.
time_t convertToTime_t(Date date) {
    tm tm = {};
    istringstream ss(date.print());
    ss >> get_time(&tm, "%m/%d/%Y");    // CLion shows error but runs fine

    if (ss.fail()) {
        throw invalid_argument("Invalid date format");
    }

    // Set hours, minutes, and seconds to zero for the beginning of the day
    tm.tm_hour = 4+12-1; // Set for market close (4pm) and subtracts one because tm_hour range: [0-23].
    tm.tm_min = 0;
    tm.tm_sec = 0;

    return mktime(&tm);
}

// Fills in the std_t var in the SharePrice struct.
void addTime_T(vector<SharePrice>& vec){
    for(int i = 0; i < vec.size() - 1; i++) vec[i].std_t = convertToTime_t(vec[i].t);
}

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

Date Date::operator+(Date *other) {
    Date sum = Date();
    return sum;
}

Date Date::operator-(Date *other) {
    Date difference = Date();
    return difference;
}

string Date::print() const{
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

Company::Company(string& t, string& filename) {
    this->ticker = t;
    //this->price_history = ph;
    this->price_history = readCSV(filename);
    if (!price_history.empty()) {
        this->curr_share_price = price_history.back(); // Set the current share price to the most recent one
    }
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
    return ticker;
}

SharePrice Company::getPrice(){
    return curr_share_price;
}

vector<SharePrice> Company::getPriceHistory(){
    return price_history;
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

//Function to parse line of CSV data into SharePrice
SharePrice parseCSVLine(string& line) {
    stringstream ss(line);
    string dateStr, openStr, highStr, lowStr, closeStr, volumeStr;

    // Read each field separated by commas
    getline(ss, dateStr, ',');
    getline(ss, openStr, ',');
    getline(ss, highStr, ',');
    getline(ss, lowStr, ',');
    getline(ss, closeStr, ',');
    getline(ss, volumeStr, ',');
    // Ensure the closeStr is not empty
    if (closeStr.empty()) {
        cerr << "Error: Empty 'Close' value on line: " << line << endl;
        throw invalid_argument("Empty close value");
    }

    // Convert the strings to appropriate types
    Date date(dateStr);
    try {
        // Remove quotes from the string if they are present
        if (closeStr.front() == '"' && closeStr.back() == '"') {
            closeStr.erase(0, 1); // Remove the first quote
            closeStr.erase(closeStr.size() - 1); // Remove the last quote
        }
        double close = stod(closeStr);
        SharePrice sp;
        sp.t = date;
        sp.price = close;
        sp.std_t = convertToTime_t(date);
        return sp;
    } catch (const std::exception& e) {
        cerr << "Error converting 'Close' to double: " << closeStr << endl;
        throw;
    }
}

vector<SharePrice> readCSV(const string& filename) {
    ifstream file(filename);
    vector<SharePrice> priceHistory;
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return priceHistory;
    }
    string line;// Ignore header
    if (!getline(file, line)) {
        cerr << "Error reading the header line." << endl;
        return priceHistory;
    }
    while (getline(file, line)) {
        try {
            SharePrice sp = parseCSVLine(line);
            priceHistory.push_back(sp);
        } catch (const std::invalid_argument& e) {
            cerr << "Skipping invalid line: " << line << endl;
        }
    }
    file.close();
    return priceHistory;
}

// Convert data from Company object to MATLAB-friendly format
string formatForMatlab(Company& company, const std::vector<SharePrice>& meanLine, const std::vector<SharePrice>& forecasted) {
    const auto& priceHistory = company.getPriceHistory();
    std::stringstream datesStream, pricesStream, meanLineStream, forecastedStream;
    // Extract Dates and Prices from the company data
    for (const auto& sp : priceHistory) {
        datesStream << "'" << sp.t.print() << "',"; // Add quotes around dates
        pricesStream << sp.price << ",";
    }
    // Extract MeanLine data
    for (const auto& sp : meanLine) {
        meanLineStream << sp.price << ",";
    }
    // Extract Forecasted data
    for (const auto& sp : forecasted) {
        forecastedStream << sp.price << ",";
    }
    // Remove trailing commas
    string dates = datesStream.str(); dates.pop_back();
    string prices = pricesStream.str(); prices.pop_back();
    string meanLineStr = meanLineStream.str(); meanLineStr.pop_back();
    string forecastedStr = forecastedStream.str(); forecastedStr.pop_back();
    // Format as MATLAB-compatible inputs
    return "{" + dates + "}, [" + prices + "], [" + meanLineStr + "], [" + forecastedStr + "]";
}

void plotCompanyData(Company& company, const std::vector<SharePrice>& meanLine, const std::vector<SharePrice>& forecasted) {
    std::string dataString = formatForMatlab(company, meanLine, forecasted);
    std::string command = "matlab -nodesktop -nosplash -r \"MakePlot(" + dataString + "); exit\"";
    system(command.c_str());
}