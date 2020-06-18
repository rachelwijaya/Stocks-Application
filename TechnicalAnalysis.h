//
// Created by Rachel on 6/18/2020.
//

#ifndef STOCKAPPLICATION_TECHNICALANALYSIS_H
#define STOCKAPPLICATION_TECHNICALANALYSIS_H

#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <algorithm>

// Used for finding absolute value
#include <cmath>

// Used for evaluating assertion
#include <assert.h>

// #include <boost/optional.hpp> //optional return values

using namespace std;

/*  Stores the calculations in the TechnicalIndicators struct from the calculation in TechnicalAnalysis.cpp */

//----------------------------------------------------------------------------//

class TechnicalAnalysis{
    struct TechnicalIndicators {
        vector<double> RSI, stochRSI, standardDeviation, MACD, MACD_Signal, fiftySMA, hundredSMA, twoHundSMA;
    } indicators;

public:

    // void accessSignal(vector<double> vector, double temp );

    /* void accessMACD(boost::optional<std::vector<double> &> copy = boost::none,
                    boost::optional<double> temp = boost::none);

    void accessRSI(boost::optional<std::vector<double> &> copy = boost::none,
                   boost::optional<double> temp = boost::none);

    void accessStoch(boost::optional<std::vector<double> &> EMPTY_VEC = boost::none,
                     boost::optional<double> temp = boost::none);

    void accessFifSMA(boost::optional<std::vector<double> &> EMPTY_VEC = boost::none,
                      boost::optional<double> temp = boost::none);

    void accessHundSMA(boost::optional<std::vector<double> &> EMPTY_VEC = boost::none,
                       boost::optional<double> temp = boost::none); */


// Setter and getter methods

    void getMACD(vector<double> V) const;

    void getSignal(vector<double> V) const;

    void getRSI(vector<double> V) const{
        V = indicators.RSI;
    };

    void getStoch(){
        for (int i = 0; i < indicators.stochRSI.size(); i++){
            cout << indicators.stochRSI[i] << endl;
        }
    } ;

    void getFiftySMA() const{
        int day = 50;
        cout << indicators.fiftySMA[day] << endl;
    };

    void getHundredSMA() const{
        int day = 100;
        cout << indicators.hundredSMA[day] << endl;
    };

    void getTwoHundSMA()const {
        int day = 200;
        cout << indicators.twoHundSMA[day] << endl;
    }

    void setFiftySMA(const double n) { indicators.fiftySMA.push_back(n); }

    void setHundredSMA(const double n){ indicators.hundredSMA.push_back(n); }

    void setRSI(const double n){ indicators.RSI.push_back(n); }

    void setStoch(const double n){ indicators.stochRSI.push_back(n); }

    void setTwoHundSMA(const double n ){ indicators.twoHundSMA.push_back(n);}


// Functions from the cpp.files
// Values are stored in the struct above

// NOTE REPLACE V WITH THE VECOTR VARIABLE IN UR CODE

    //calculate 50 SMA
    void calcFiftySMA(vector<double> V)
    {
        // assert(V.isEmpty());
        int day = 50;
        double total;

        vector<double> closePrices = V;

        if (closePrices.size() <= day)
        {
            cout << endl << "Not enough data for " << day << " days!";
            cout << endl << "please insert the exact data for" << day << " days.";
            return;
        }

        for (int i = 0; i <= (closePrices.size() - day); i++)
        {
            total = 0.0;

            for (int j = i; j < i + day; j++)
                total += closePrices[j];

            setFiftySMA(total / day);
        }
    }

    //calculate 100 SMA
    void calcHundredSMA(vector<double> V)
    {
        int day = 100;
        double total;
        vector<double> closePrices = V;
        if (closePrices.size() <= day)
        {
            cout << endl << "Not enough data for " << day << " days!";
            cout << endl << "please insert the exact data for" << day << " days.";
            return;
        }

        for (int i = 0; i <= (closePrices.size() - day); i++)
        {
            total = 0.0;

            for (int j = i; j < i + day; j++)
                total += closePrices[j];

            setHundredSMA(total / day);
        }
    }

    void calcTwoHundSMA(vector<double> V)
    {
        double total;
        int day = 200;
        vector<double> closePrices = V;
        if(closePrices.size() <= day){
            cout << endl << "Not enough data for " << day << " days!";
            cout << endl << "please insert the exact data for" << day << " days.";
            return;
        }

        for(int i = 0; i <= (closePrices.size() - day); i++) {
            total = 0.0;

            for (int j = i; j < i + day; j++)
                total += closePrices[j];

            setTwoHundSMA( total / day);
        }
    }

    void calcRSI(vector<double> V)
    {

        auto pushCurrentPeriod = [] (const vector<long double> &currPeri, vector<long double> &change){
            for(int i = 1; i < currPeri.size(); i++)
                change.push_back(currPeri[i] - currPeri[i-1]);
        };

        vector<long double> gain, loss, change, avgGain, avgLoss, RS;
        vector<double> closePrices = V;


        //When there hasn't been 250 data points yet.
        if(closePrices.size() > 250) {
            vector <long double> currentPeriod(closePrices.end()-250,closePrices.end());
            pushCurrentPeriod(currentPeriod, change);
        }

        else{
            vector <long double> currentPeriod(closePrices.begin(),closePrices.end());
            pushCurrentPeriod(currentPeriod, change);
        }

        double totalGain = 0, totalLoss = 0;

        for(int i = 0; i < change.size(); i++) {
            change[i] > 0 ? gain.push_back(change[i]) : gain.push_back(0);
            change[i] < 0 ? loss.push_back(abs(change[i])) : loss.push_back(0);
            totalGain += gain[i];
            totalLoss += loss[i];
        }

        avgGain.push_back(totalGain/14);
        avgLoss.push_back(totalLoss/14);

        for(int i = 14, j = 1; i < gain.size(); i++) {
            avgGain.push_back(((avgGain[j-1] * 13)+ gain[i])/14);
            avgLoss.push_back(((avgLoss[j-1] * 13)+ loss[i])/14);
            j++;
        }

        for(int i = 0; i < avgGain.size(); i++) {
            RS.push_back(avgGain[i]/avgLoss[i]);
            setRSI(avgLoss[i] == 0 ? 100 : 100 - (100/(1+RS[i])));
        }
        calcStochRSI();

        for(int i : indicators.RSI) {
            cout<< endl << i;
        }
    }

    void calcStochRSI()
    {
        assert(!indicators.RSI.empty());

        auto copy = [] (const vector<double> &RSI, vector<double> &temp, const int &loc){
            for(int i = 13; i >= 0; i--)
                temp.push_back(RSI[loc-i]);
        };

        vector<double> tempVec, tempRSI;
        getRSI(tempRSI);

        for(int i = 13; i <tempRSI.size(); i++) {
            copy(tempRSI,tempVec,i);
            auto lowIt= *min_element(tempVec.begin(), tempVec.end());
            auto highIt= *max_element(tempVec.begin(), tempVec.end());
            setStoch((tempVec.back()-lowIt)/(highIt-lowIt));
            tempVec.clear();
        }
    }

};




#endif //STOCKAPPLICATION_TECHNICALANALYSIS_H
