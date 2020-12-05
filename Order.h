
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

#include "common.h"
#include "restaurant.h"
#include "Manager.h"

using namespace std;

class Order
{
public:
    string name;
    int orderID;
    int status; //1 = Ordering, 2 = Cooking, 3 = Finished
    queue<MenuItem> items;
    double totalPayment;

    Order(); //Default Constructor
    void createOrderItems(vector<MenuItem> menu); //Creates Random Orders
    //todo let user type the order
    bool makeOrder(const vector<MenuItem> &menu);
    //todo
    bool pay();

    int generateID();

    //Item Functions
    void addItem(int, vector<MenuItem> menu);
    void deleteItems();
    double getTotal();
    int getServiceTime();

    //Status Functions
    void setStatus(int);
    string reportStatus();
    void getSummary();
    void printOrder();

    //Paying Functions
    void finishOrder();

};

Order::Order() //Default Constructor
{

    orderID = generateID();
    status = 1;
    totalPayment = 0;
    for(int i = 0; i < items.size(); i++)
    {
      items.pop();
    }
    //todo remark this one. we let user input the menu
    //createOrderItems(menu);
}


void Order::printOrder()
{
    queue<MenuItem> itemsCopy = items;
    while(itemsCopy.empty() == false)
    {
        cout<< itemsCopy.front().name<<endl;
        itemsCopy.pop();
    }
  
    getTotal();

    cout<<"----- Total $: " << totalPayment <<endl;
}

int Order::generateID() //Generates Random ID
{
    srand((unsigned)time(NULL));
    int ID = rand() % 899999 + 100000;
    return ID;
}

//todo let user type the order
bool Order::makeOrder(const vector<MenuItem>& menu)
{
    //Create New Order
    Order newOrder;
  
    cout << "Displaying Menu:";
    showMenu(menu);
  
    //Ask Name
    cout << endl;
    cout << "Enter Customer Name: " << endl;
    string customerName;
    getline(cin, customerName);
    newOrder.name = customerName;
  
    int selection;
    bool next = false;
    do
    {
        cout << "Select an option [1 = Add Item, 2 = Clear Items, 3 = Print Order, -1 = Finish, -2 = Cancel]";
        cout << endl;
        cin >> selection;
        cin.ignore();

        switch (selection)
        {
        case 1:
            int itemID;
            cout << "Add a food with the ID" << endl;
            cin >> itemID;
            cin.ignore(1000, 10);
            if(itemID <= menu.size() && itemID > -1)
            {
              newOrder.addItem(itemID, menu);
            }
            break;
        case 2:
            newOrder.deleteItems();
            break;
          case 3:
            printOrder();
            break;
        case -1:
            //finish the order
            finishOrder();
            next = true;
            break;
        case -2:
            next = true;
            break;
        default:
            cout << "Incorrect menu ID, please enter a correct one.";

        }
       
    } while (!next);

    //customer finish the order
    if (selection == -1)
    {
        //now need to let customer pay the money
        //inside the pay function show the price and let
        bool ret = pay();
        if (!ret)
        {
            //todo cancel the payment, need to delete the items
            //deleteItems();
          newOrder.deleteItems();
        }
        return ret;
    }
    else if (selection == -2)  //customer cancel the order
    {
        //todo cancel the payment, need to delete the items
            //deleteItems();
        newOrder.deleteItems();
        return false;
    }
    else
    {
        return false;
    }
}

//todo
bool Order::pay()
{
    //show the items and their price, the tax(sum of items price*defalut tax rate), total price
    //let user type to pay
    int input = 0;
    while (true)
    {
      cout << "The total is: " << getTotal() << endl;
        cout << "[1 = Pay, -1 = Cancel]" << endl;
        cin >> input;
        if (input == 1)
        {
            cout << "Thank you!" << endl;
            printOrder();
            return true;
        }
        else if (input == -1)
        {
            cout << "Order has been cancelled." << endl;
            return false;
        }
        else
        {
            cout << "Incorrect number. Please Re-enter." << endl;
        }
    }

}

void Order::createOrderItems(vector<MenuItem> menu) // add items to order items randomly
{
    srand((unsigned)time(NULL));

    int maxAmount = rand() % 5;
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

void Order::addItem(int idNum, vector<MenuItem> menu) //Adds Item to Order
{
    MenuItem tempItem;
    //vector<item> menu = loadMenu();
    for(auto& it: menu)
    {
        if(it.idNumber == idNum)
        {
            tempItem.name = it.name;
            tempItem.idNumber = it.idNumber;
            tempItem.price = it.price;
            //tempItem.amount = amount;
            //items.insert(pair<item, int>(tempItem, amount));
            items.push(tempItem);
            break;
        }
    }
}

void Order::deleteItems()
{
  for(int i = 0; i < items.size(); i++)
  {
    items.pop();
  }
}

int Order::getServiceTime()
{
  int returnValue = 0;
  queue<MenuItem> copyQueue;
  copyQueue = items;
  for(int i = 0; i < items.size(); i++)
  {
    returnValue += copyQueue.front().avgPrepTime;
    copyQueue.pop();
  }
  return returnValue;
}

double Order::getTotal()
{
  totalPayment = 0;
  double tax = .10;
  queue<MenuItem> copyQueue;
  copyQueue = items;
  for(int i = 0; i < items.size(); i++)
  {
    totalPayment += copyQueue.front().price;
    items.pop();
  }
  totalPayment = totalPayment + (totalPayment * tax);
  return totalPayment;
}

void Order::setStatus(int setValue) //Set Value of Status
{
    status = setValue;
}

string Order::reportStatus() //Returns Order Status
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

void Order::finishOrder()
{
  
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
    map<item, int>::iterator it;
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

#endif /* Order_h */
