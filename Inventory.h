//
// Created by Rachel on 6/18/2020.
//

#ifndef STOCKAPPLICATION_INVENTORY_H
#define STOCKAPPLICATION_INVENTORY_H
#include <iostream>
#include <vector>
using namespace std;

class Inventory{
public:
    struct inventoryD{
        vector<int > units;
        vector <double> pricePerUnit, priceInTotal;

    }inventoryData;
    void displayVector(); // display specification of units that you owned
    void displayUnit(); //display amounts of units
    double checkBalance();
    void topUpBalance(double value);
    void addNewInventory(int units, double pricePerUnit, double priceInTotal);
    double deductBalance(double value);

protected:
    double balance = 0;
};


double Inventory::checkBalance()
{
    return balance;
}

void Inventory::topUpBalance(double value) {
    if(value >= 0){
        balance += value;
        cout << "An amount of " << balance << " has been added.";
    }
    else
    {
        cout << "Top Up Balance has to be >= 0 value" << endl;
    }
}

void Inventory::displayVector()
{
    if  (inventoryData.units.size() == 0)
    {

        cout << "You don't have any unit at the moment"<<endl;
    }else
    {
        for(int i = 0; i < inventoryData.units.size(); i++)
        {
            cout << "For the " << inventoryData.units[i] << "share(s), " << "it was bought at the price of " <<
                 inventoryData.pricePerUnit[i] <<  " per unit, costing at a total of " << inventoryData.priceInTotal[i] << "." << endl;
        }
    }
}

void Inventory::displayUnit()
{
    cout << "You currently have "<< inventoryData.units.size() << " unit/s"<<endl;
    cout << "Below is the list of unit/s you owned: " << endl;
    for (int i = 0; i < inventoryData.units.size(); i ++)
    {
        cout << i << "." << inventoryData.units[i] << endl;
    }
}


void Inventory::addNewInventory(int units, double pricePerUnit, double priceInTotal) {
    if (priceInTotal  > balance){
        cout << "Not enough balance. Please top up and try again" << endl;
    } else {
        inventoryData.units.push_back(units);
        inventoryData.pricePerUnit.push_back(pricePerUnit);
        inventoryData.priceInTotal.push_back(priceInTotal);
        cout << "Your purchase was successful!" << endl;
    }
}

double Inventory::deductBalance(double value) {
    balance -= value;
    return balance;
}

#endif //STOCKAPPLICATION_INVENTORY_H
