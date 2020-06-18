#include <iostream>
#include <string>
#include "VectorData.h"
#include "Inventory.h"
#include "TechnicalAnalysis.h"

using namespace std;

void inventoryMenu()
{
    cout << "\n----------  I N V E N T O R Y  M E N U ----------" << endl;
    cout << "1. Display Shares" << endl;
    cout << "2. Display Units" << endl;
    cout << "3. Check Balance" << endl;
    cout << "4. Top Up Balance" << endl;
    cout << "5. Exit" << endl;
}

int main() {

    VectorData vectorData;
    vectorData.readFile();

    Inventory inventoryData;

    TechnicalAnalysis technicalAnalysis;

    string name;
    cout << "Please enter your name: ";
    cin >> name;
    cout << "Welcome " << name << endl;

    cout << "\n----------  M A R K E T  M E N U ----------" << endl;
    cout << "1. Display prices" << endl;
    cout << "2. Buy stocks" << endl;
    cout << "3. Sell stocks" << endl;
    cout << "4. View indicators" << endl;
    cout << "5. Go to Inventory" << endl;
    cout << "6. Exit" << endl;

    int option, indicator, unitsBuy, unitsSell, vectorSize;
    double priceBuy, priceTotalBuy, priceSell, priceTotalSell, balance, topUp;
    string FifoLifo, answer;
    cout << "\nWhat would you like to do?" << endl;
    cin >> option;

    while (option != 6) {
        switch (option) {
            case 1:
                vectorData.printRecentPrices();
                break;

            case 2:
                cout << "\nMarket Order" << endl;
                cout << "Enter how many units would you like to purchase:" << endl;
                cin >> unitsBuy;
                priceBuy = vectorData.stockData.open[0];
                priceTotalBuy = priceBuy * unitsBuy;
                inventoryData.addNewInventory(unitsBuy, priceBuy, priceTotalBuy);
                inventoryData.deductBalance(priceTotalBuy);

                break;

            case 3:
                cout << "\nEnter how many units would you like to sell" << endl;
                cin >> unitsSell;
                cout << "Please type LIFO/FIFO: " << endl;
                cin >> FifoLifo;

                vectorSize = inventoryData.inventoryData.units.size();

                if (FifoLifo == "LIFO" && unitsSell > inventoryData.inventoryData.units.back()) {
                    cout << "You dont have enough shares to sell using FIFO method" << endl;
                }

                if (FifoLifo == "FIFO" && unitsSell > inventoryData.inventoryData.units.front()) {
                    cout << "You dont have enough shares to sell using LIFO method" << endl;
                }

                if (FifoLifo == "LIFO" && unitsSell <= inventoryData.inventoryData.units.front()) {
                    inventoryData.inventoryData.units[0] -= unitsSell; // reduces amount of shares
                    priceSell = inventoryData.inventoryData.pricePerUnit[vectorSize - 1];
                    priceTotalSell = priceSell * unitsSell;
                    inventoryData.topUpBalance(priceTotalSell);
                    cout << "Shares has been sold for: " << priceTotalSell << endl;

                }

                if (FifoLifo == "FIFO" && unitsSell <= inventoryData.inventoryData.units.back()) {
                    inventoryData.inventoryData.units[vectorSize - 1] -= unitsSell; // reduces amount of shares
                    priceSell = inventoryData.inventoryData.pricePerUnit[vectorSize - 1];
                    priceTotalSell = priceSell * unitsSell;
                    inventoryData.topUpBalance(priceTotalSell);
                    cout << "Shares has been sold for: " << priceTotalSell << endl;
                }

                break;

            case 4:
                // view indicators
                cout << "\n----------  M A N U A L  ----------" << endl;
                cout << "Simple Moving Average (SMA) are indicator that track stock" << endl;
                cout << "over a series of time, we look at the stock average price changes overtime" << endl;
                cout << "from there we can see the trend of increase or decrease of price!" << endl;
                cout << "The more period its averaged by the more accurate. " << endl;
                cout
                        << "Some stocks are better for short term, so make sure you choose the highest average of the three for maximum profit."
                        << endl;
                cout
                        << "Example: If fifty SMA is the highest among the other averages, it's best to hold on to your stocks for around 50 days."
                        << endl;
                cout << "\nChoose how many days to average it by 50/100/200 :" << endl;
                cout << "Fifty SMA (50)" << endl;
                cout << "One Hundred SMA (100)" << endl;
                cout << "Two Hundred SMA(200)" << endl;
                cin >> indicator;

                if (indicator == 50) {
                    technicalAnalysis.calcFiftySMA(vectorData.stockData.close);
                    technicalAnalysis.getFiftySMA();
                    cout << "Make sure to compare it with your buying price, decide to sell it or not for profit!"
                         << endl;
                } else if (indicator == 100) {
                    technicalAnalysis.calcHundredSMA(vectorData.stockData.close);
                    technicalAnalysis.getHundredSMA();
                    cout << "Make sure to compare it with your buying price, decide to sell it or not for profit!"
                         << endl;
                } else if (indicator == 200) {
                    technicalAnalysis.calcTwoHundSMA(vectorData.stockData.close);
                    technicalAnalysis.getTwoHundSMA();
                    cout << "Make sure to compare it with your buying price, decide to sell it or not for profit!"
                         << endl;
                } else { cout << "SMA Indicator not available" << endl; }
                cout << "Would you like to use RSI? [Y/N]" << endl;
                cin >> answer;
                if (answer == "Y") {
                    cout << "A brief explanation of what RSI is. Relative Strength Index is an oscillator that measures"
                            " the speed and change of price movements. When the index reaches above 70, it is overbought."
                            " Meanwhile, when the index shows below 30, it is oversold." << endl;
                    technicalAnalysis.calcRSI(vectorData.stockData.close);
                } else {
                    continue;
                }

                break;

            case 5:
                inventoryMenu();
                int option2;
                cout << "\n(Inventory) What would you like to do?" << endl;
                cin >> option2;
                while (option2 != 5) {
                    switch (option2) {
                        case 1:
                            inventoryData.displayVector();
                            break;

                        case 2:
                            inventoryData.displayUnit();
                            break;

                        case 3:
                            balance = inventoryData.checkBalance();
                            cout << "Your balance is: " << balance << endl;
                            break;

                        case 4:
                            cout << "How much would you like to top up? " << endl;
                            cin >> topUp;
                            inventoryData.topUpBalance(topUp);
                            break;

                        case 5:
                            option2 = 5;
                            break;

                        default:
                            break;
                    }
                    inventoryMenu();
                    cout << "\n(Inventory) What would you like to do?" << endl;
                    cin >> option2;
                    break;
                }
                break;
            case 6:
                exit(0);

            default:
                break;
        }
        cout << "\n(Main Menu) What would you like to do?";
        cin >> option;
    }
    return 0;
}