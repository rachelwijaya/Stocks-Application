//
// Created by Rachel on 6/17/2020.
//

#ifndef STOCKAPPLICATION_VECTORDATA_H
#define STOCKAPPLICATION_VECTORDATA_H

#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class VectorData {
public:
    struct stockData {
        vector<long double> volume;
        vector<double> open, high, low, close, adjClose;
        vector<string> date;

    } stockData;
    void readFile() {
        ifstream file;
        file.open("C:/Users/Rachel/CLionProjects/StockApplication/AAPL.csv");
        string dateString, openString, closeString, highString, lowString, volumeString, adjCloseString;

        if (!file.is_open()) {
            cout << "fail to open file" << endl;
        }
        int totalElements = 0; // keeps track of total elements in all the vectors, should be the same for all
        while (file.good()) {
            // assigns the string variables values for each line
            getline(file, dateString, ',');
            getline(file, openString, ',');
            getline(file, highString, ',');
            getline(file, lowString, ',');
            getline(file, closeString, ',');
            getline(file, adjCloseString, ',');
            getline(file, volumeString, '\n');


            // the values of the variable are then pushed into their respective vectors
            stockData.date.push_back(dateString);
            stockData.open.push_back(stod(openString));
            stockData.high.push_back(stod(highString));
            stockData.low.push_back(stod(lowString));
            stockData.close.push_back(stod(closeString));
            stockData.adjClose.push_back(stol(adjCloseString));
            stockData.volume.push_back(stol(volumeString));
            totalElements++;
        }
        /*for (int i = 0; i < totalElements; i++) {
            cout << stockData.date[i] << endl;
            cout << stockData.open[i] << endl;
            cout << stockData.close[i] << endl;
            cout << stockData.high[i] << endl;
            cout << stockData.low[i] << endl;
            cout << stockData.volume[i] << endl;
            cout << stockData.adjClose[i] << endl;
        } This was used to check if the elements had been pushed correctly*/
    }

    void printRecentPrices(){
        int days;
        cout << "How many days of stock prices would you like to see? Please enter integers only: ";
        cin >> days;
        int totalElements = stockData.date.size();
        if (days > totalElements){
            cout << "Sorry the amount of days youve entered has exceeded current data" << endl;
        }
        else {
            for (int i = 0; i < days; i++) {
                cout << "Date: " << stockData.date[i] << endl;
                cout << "Open: " << stockData.open[i] << endl;
                cout << "Low: " << stockData.low[i] << endl;
                cout << "High: " << stockData.high[i] << endl;
                cout << "Close: " << stockData.close[i] << endl;
                cout << "Adjacent Close: " << stockData.adjClose[i] << endl;
                cout << "Volume: " << stockData.volume[i] << endl << endl;
            }
        }
    }
};

#endif //STOCKAPPLICATION_VECTORDATA_H
