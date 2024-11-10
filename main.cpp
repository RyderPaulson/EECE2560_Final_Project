// Source File

#include <iostream>
#include "Market.h"
#include "Algorithm.h"
#include "io.h"
#include <sstream>
using namespace std;

void tests();
string getFilePathFromUser();
string extractCompanyName(const string& filepath);
void PlotData(const string& filepath);

int main() {
    string filePath;
    int input;
    bool while_control = true;
    cout<<"Would you like to run tests?\n\t1. Yes\n\t2. No\n";
    cin>>input;
    if(input==1) tests();

    while(while_control) {
        cout<<"Choose your action.\n"
              "\t1. Import data for analysis\n"
              "\t2. Plot\n"
              "\t3. End program\n";
        cin>>input;
        switch(input){
            case 1: {
                //cout<<"Placeholder\n";
                filePath = getFilePathFromUser();
                cout << "Data file path saved: " << filePath << endl;
                break;
            }
            case 2: {
                cout<<"Generating plot\n";
                //system("matlab -nodesktop -r MakePlot");
                PlotData(filePath);
                break;
            }
            default:
                while_control = false;
        }
        cout<<"\n\n"<<endl;
    }

    //string filename = "C:/Users/kl198/CLionProjects/EECE2560_Final_Project/data/AAPL 10.2.2023 - 10.1.2024.csv";
    //Company test("AAPL",filename);
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

bool testRegression() {
    return 0; //PLACEHOLDER
}

bool testOutput() {
    return 0; //PLACEHOLDER
}

void tests(){
    if(testDate()) cout<<"\n\nDate tests: successful\n\n";
    if(shareTests()) cout<<"\n\nShare tests: successful\n\n";
    if(testOutput()) cout<<"\n\nOutput tests: successful\n\n";
}

void PlotData(const string& filepath) {
    vector<SharePrice> priceHistory = readCSV(filepath);
    string companyName = extractCompanyName(filepath);
    Company company(companyName, priceHistory);
    Regression reg(priceHistory, 30);
    vector<SharePrice> meanLine = reg.getMeanLine();
    vector<SharePrice> forecasted = reg.getForecast();
    plotCompanyData(company, meanLine, forecasted);
}

// Function to extract the company name from the file path
string extractCompanyName(const string& filepath) {
    size_t lastSlashPos = filepath.find_last_of("/\\");
    string filename = (lastSlashPos == string::npos) ? filepath : filepath.substr(lastSlashPos + 1);
    size_t dotPos = filename.find_last_of('.');
    if (dotPos != string::npos) {
        filename = filename.substr(0, dotPos);
    }
    size_t spacePos = filename.find(' ');
    string companyName = (spacePos != string::npos) ? filename.substr(0, spacePos) : filename;
    return companyName;
}

string getFilePathFromUser() {
    string path;
    cout << "Enter the full path to the CSV data file: ";
    cin.ignore(); // Clear input buffer
    getline(cin, path); // Get entire line in case of spaces
    return path;
}