% Change to just output.csv in final version
T = readtable("data\Example Output.csv");

Ticker = T.Ticker(1);
Dates = datetime(T.Date, 'InputFormat', 'MM/dd/yyyy');
Price = T.Price;
MeanLine = T.MeanLine;
Forecasted = T.Forecasted;

% Get rid of this in final version
MeanLine = ([1:1:29]*1.75261+100.301).';

figure
plot(Dates, Price);
hold on
plot(Dates, MeanLine);
plot(Dates, Forecasted);
hold off
title(Ticker);
legend('Price', 'Mean','Forecasted','Location','southeast');
xlabel('Date')
ylabel('Price ($)')