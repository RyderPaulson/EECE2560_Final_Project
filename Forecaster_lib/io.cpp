#include "io.h"

void outputCSV(Regression forecast){
    fstream fout;
    bool start_forecast = false;
    int forecast_start;
    string date;
    fout.open("data/output.csv");

    date = forecast.company->getPriceHistory()[0].t.print();
    fout<<date;
    fout<<","<<forecast.company->getPriceHistory()[0].price;
    fout<<","<<forecast.mean_line[0].price<<",,"<<forecast.company->getTicker()<<endl;

    fout<<"Date,Price,MeanLine,Forecasted,Ticker"<<endl;
    for(int i = 1; i < forecast.getSize(); i++) {
        date = forecast.company->getPriceHistory()[i].t.print();
        fout<<date;
        fout<<","<<forecast.company->getPriceHistory()[i].price;
        fout<<","<<forecast.mean_line[i].price;
        if(date == forecast.forecasted_line[0].t.print()) {
            // Check to see if the forecast line has started yet
            start_forecast = true;
            forecast_start = i;
        }
        if(start_forecast) {
            // If started, print it
            fout<<","<<forecast.forecasted_line[i-forecast_start].price;
        }
        else {
            // Otherwise just print comma to make empty value
            fout<<",";
        }
        fout<<","<<endl;
    }

    fout.close();
}