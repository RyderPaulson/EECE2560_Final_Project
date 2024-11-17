#include "io.h"



bool outputCSV(Regression forecast){
    fstream fout;
    bool start_forecast = false;
    int forecast_start;
    string date;

    fout.open("data/output.csv", ios::out);

    if(!fout.is_open()) {
        cerr << "Failed to open file. Current working directory is: " << filesystem::current_path() << endl;
        return false;
    }

    fout<<"Date,Price,MeanLine,Forecasted,Ticker"<<endl;
    date = forecast.getNthDate(0).print();
    fout<<date;
    fout<<","<<forecast.getNthPrice(0);
    fout<<","<<forecast.mean_line[0].price<<",,"<<forecast.company->getTicker()<<endl;

    for(int i = 1; i < forecast.getSize() - 1; i++) {
        date = forecast.getNthDate(i).print();
        fout<<date;
        if(i == forecast.getInitialSize() - 1) {
            // Check to see if the forecast line has started yet
            start_forecast = true;
            forecast_start = i;
            fout<<","<<forecast.getNthPrice(i);
            fout<<","<<forecast.mean_line[i].price;
            fout<<","<<forecast.forecasted_line[i-forecast_start].price;
            fout<<","<<endl;
        }
        if(start_forecast && (i != forecast_start)) {
            // If started, print it
            fout<<",,"<<forecast.mean_line[i].price;
            fout<<","<<forecast.forecasted_line[i-forecast_start].price;
            fout<<","<<endl;
        }
        else if(!start_forecast){
            // Otherwise just print comma to make empty value
            fout<<","<<forecast.getNthPrice(i);
            fout<<","<<forecast.mean_line[i].price;
            fout<<",,"<<endl;
        }
    }

    fout.close();

    return true;
}
