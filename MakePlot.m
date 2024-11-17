
% Change to just output.csv in final version
T = readtable("data/Output.csv");
%T = readtable("C:/Users/kl198/CLionProjects/EECE2560_Final_Project/data/Example Output.csv");

Ticker = T.Ticker(1);
Dates = datetime(T.Date, 'InputFormat', 'MM/dd/yyyy');
Price = T.Price;
MeanLine = T.MeanLine;
Forecasted = T.Forecasted;

% Get rid of this in final version
% MeanLine = ([1:1:29]*1.75261+100.301).';

figure(1)
plot(Dates, Price);
hold on
plot(Dates, MeanLine);
plot(Dates, Forecasted);
hold off
title(Ticker);
legend('Price', 'Mean','Forecasted','Location','southeast');
xlabel('Date')
ylabel('Price ($)')

%{
function MakePlot(dates, prices, meanLine, forecasted)
    % Convert dates from cell array of strings to datetime format
    Dates = datetime(dates, 'InputFormat', 'MM/dd/yyyy');
    % Plot the data
    figure;
    plot(Dates, prices, 'LineWidth', 2);
    hold on;
    %plot(Dates, meanLine, '--', 'LineWidth', 1.5);
    %plot(Dates, forecasted, ':', 'LineWidth', 1.5);
    hold off;
    % Set plot title and labels
    title('Stock Prices with Forecasting');
    %legend('Price', 'Mean', 'Forecasted', 'Location', 'southeast');
    xlabel('Date');
    ylabel('Price ($)');
    pause;
end
%}