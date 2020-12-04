
//
//  Created by Max Raffield on 12/3/20.
//

#ifndef Order_h
#define Order_h

#include <iostream>
#include <string>
#include <cstdlib>
#include <map>
#include <queue>
#include <vector>
#include <fstream>
#include <cstring>

#include "Restaurant.h"

using namespace std;

class order
{
public:
    int orderID;
    int status; //1 = Ordering, 2 = Cooking, 3 = Finished
    queue<item> items;
    double totalPayment;

    order(); //Default Constructor
    void createOrderItems(vector<item> menu); //Creates Random Orders
    int generateID();

    //Menu Functions
    vector<item> loadMenu(); //Loads Menu
    void showMenu();

    //Item Functions
    void addItem(int, int, vector<item> menu);

    //Status Functions
    void setStatus(int);
    string reportStatus();
    void getSummary();
    void printOrder();

    //Paying Functions
    void finishOrder();

};

order::order() //Default Constructor
{

    orderID = generateID();
    status = 1;
    createOrderItems(menu);
}


void order::printOrder()
{

    queue<item> itemsCopy = items;
    while(itemsCopy.empty() == false)
    {
        cout<< itemsCopy.front().name<<endl;
        itemsCopy.pop();
    }

    cout<<"----- Total $: " << totalPayment <<endl;
}

int order::generateID() //Generates Random ID
{
    srand((unsigned)time(NULL));
    int ID = rand() % 899999 + 100000;
    return ID;
}

void order::createOrderItems(vector<item> menu) // add items to order items randomly
{
    srand((unsigned)time(NULL));

    int maxAmount = rand() %5;
    if (rand() % 2) maxAmount = 2;
    if (maxAmount == 0 || maxAmount == 1) maxAmount = 1;              // max amount of items in order. Most of the time, it's 1.

    // traverse menu and randomly decide to add item to order


    while(true)
    {
        int menuIndex = rand()%menu.size();
        if (items.size() >= maxAmount) return;
        items.push(menu[menuIndex]);
        totalPayment += menu[menuIndex].price;
    }

    for(int i = 0; i < menu.size() ; i++)
    {
        int amount;
        if (rand()%2) amount = 0;
        else amount = 1;
        for(int j = 0; j < amount; j++)
        {
            if (items.size() >= maxAmount) return;
            items.push(menu[i]);
            totalPayment += menu[i].price;
        }
    }

}
/*
vector<item> order::loadMenu() //Creates Menu to Read
{
    vector<item> returnMenu;
    ifstream fin;
    fin.open("menu.txt");

    int itemID = 0;

    char* token;
    char buf[1000];
    const char* const tab = "\t";

    while(fin.good())
    {
        string line;
        getline(fin, line);
        strcpy(buf, line.c_str());

        if (buf[0] == 0) continue; // skip blank lines

        //parse the line
        const string name(token = strtok(buf, tab));
        if (name.find('-') != string::npos) continue; // skip first line which has a dash in it

        const string price((token = strtok(0, tab)) ? token : "");
        const string avgPrepTime((token = strtok(0, tab)) ? token : "");
        const string maxAmt((token = strtok(0, tab)) ? token : "");

        item tempItem;
        tempItem.name = name;
        tempItem.idNumber = itemID;
        itemID++;
        tempItem.price = stod(price);
        tempItem.avgPrepTime = stoi(avgPrepTime);

        returnMenu.push_back(tempItem);
    }

    return returnMenu;
}
*/
/*
void order::showMenu() //Reads Menu
{
    vector<item> menu = loadMenu();

    for(auto& it: menu)
    {
        cout << "Item Name: " << it.name << endl;
        cout << "Item ID: " << it.idNumber << endl;
        cout << "Item Price: " << it.price << endl;
    }
}

void order::addItem(int idNumber, int amount, vector<item> menu) //Adds Item to Order
{
    item tempItem;
    //vector<item> menu = loadMenu();
    for(auto& it: menu)
    {
        if(it.idNumber == idNumber)
        {
            tempItem.name = it.name;
            tempItem.idNumber = it.idNumber;
            tempItem.price = it.price;
            //tempItem.amount = amount;
            //items.insert(pair<item, int>(tempItem, amount));
            for(int i = 0; i < amount; i++)
            {
                items.push(tempItem);
            }
            break;
        }
    }
}

void order::getSummary() //Returns Summary
{
    cout << endl;
    cout << "Order #" << orderID << ": " << endl;
    string status = reportStatus();
    cout << "Status: " << status << endl;
    cout << "Items: " << endl;

    /*map<item, int>::iterator it;
    for(it = items.begin(); it != items.end(); it++)
    {
      cout << it->first.idNumber << " " << it->first.name << " (" << it->second << ")" << endl;
    }
    queue<item> copyQueue;
    copyQueue = items;
    for(int i = 0; i < items.size(); i++)
    {
        cout << copyQueue.front().idNumber << " " << copyQueue.front().name << endl;
        copyQueue.pop();
    }
    cout << endl;
}
*/
void order::setStatus(int setValue) //Set Value of Status
{
    status = setValue;
}

string order::reportStatus() //Returns Order Status
{
    string returnValue = "";
    switch(this->status)
    {
    case 1:
        returnValue = "Status: Currently Ordering";
        break;
    case 2:
        returnValue = "Status: Cooking";
        break;
    case 3:
        returnValue = "Status: Order Finished";
        break;
    default:
        returnValue = "No Status";
    }

    return returnValue;
}

void order::finishOrder()
{

}

#endif /* Order_h */
