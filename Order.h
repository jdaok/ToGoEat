
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
//#include "restaurant.h"
//#include "Manager.h"

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

    int generateID();

    //Item Functions
    void addItem(int, vector<MenuItem> menu);
    void deleteItems();
    void getTotal();
    int getServiceTime();

    //Status Functions
    void setStatus(int);
    string reportStatus();
    void getSummary();
    void printOrder();

    //Paying Functions
    bool pay();
    //void finishOrder();

};

Order::Order() //Default Constructor
{

    orderID = generateID();
    status = 1;
    totalPayment = 0;
    for(unsigned int i = 0; i < items.size(); i++)
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
    //Order newOrder;

    cout << "Displaying Menu:" << endl;
    cout << endl;
    showMenu(menu);

    //Ask Name
    cout << endl;
    cout << "Enter Customer Name: " << endl;
    string customerName;
    getline(cin, customerName);
    name = customerName;

    string buf;
    char selection;
    bool next = false;
    do
    {
      cout << "Select an option: " << endl;;
      cout << "[1 = Add Item, 2 = Clear Items, 3 = Print Order, 4 = Finish, 5 = Cancel]" << endl;;
        cout << endl;
        cin >> selection;
        cin.ignore();

        switch (selection)
        {
        case '1':
            int itemID;
            cout << "Add a food with the ID: " << endl;
            cin >> buf;
            cin.ignore(1000, 10);

            try
            {
              itemID = stoi(buf.c_str());
              addItem(itemID, menu);
            }
            catch(exception &err)
            {
              cout << endl;
              cout << "Please enter a valid input." << endl;
              cout << endl;
              break;
            }
            break;
        case '2':
            cout << endl;
            cout << "Items Cleared." << endl;
            deleteItems();
            cout << endl;
            break;
        case '3':
            cout << endl;
            cout << "Order Details: " << endl;
            printOrder();
            break;
        case '4':
            //finish the order
            //finishOrder();
            next = true;
            break;
        case '5':
            next = true;
            break;
        default:
            cout << "Please enter a valid input." << endl;
            cout << endl;
            cin.ignore(1000, 10);
            //selection = 0;
            break;
        }

    } while (!next);

    //customer finish the order
    if (selection == '4')
    {
        //now need to let customer pay the money
        //inside the pay function show the price and let
        bool ret = pay();
        if (!ret)
        {
            //todo cancel the payment, need to delete the items
            //deleteItems();
          deleteItems();
        }
        return ret;
    }
    else if (selection == '5')  //customer cancel the order
    {
        //todo cancel the payment, need to delete the items
            //deleteItems();
        deleteItems();
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
      getTotal();
      cout << "The total is: " << totalPayment << endl;
        cout << "[1 = Pay, -1 = Cancel]" << endl;
        cin >> input;
        if (input == 1)
        {
          if(totalPayment == 0)
          {
            cout << endl;
            cout << "Total is 0, cancelling order." << endl;
            cout << endl;
            return false;
          }
          else
          {
            cout << endl;
            cout << "Thank you!" << endl;
            cout << endl;
            cout << "Order Details: " << endl;
            printOrder();
            return true;
          }
        }
        else if (input == -1)
        {
            cout << endl;
            cout << "Order has been cancelled." << endl;
            return false;
        }
        else
        {
            cout << "Incorrect number. Please Re-enter." << endl;
        }
    }

}

void Order::addItem(int idNum, vector<MenuItem> menu) //Adds Item to Order
{

    MenuItem tempItem;
    for(auto& it: menu)
    {
        if(it.idNumber == idNum)
        {

            tempItem.name = it.name;
            tempItem.idNumber = it.idNumber;
            tempItem.price = it.price;
            tempItem.avgPrepTime = it.avgPrepTime;
            //tempItem.amount = amount;
            //items.insert(pair<MenuItem, int>(tempItem, amount));
            items.push(tempItem);
            break;
        }
    }
}

void Order::deleteItems()
{
  for(unsigned int i = 0; i < items.size(); i++)
  {
        items.pop();
  }
}

int Order::getServiceTime()
{
  int returnValue = 0;
  queue<MenuItem> copyQueue;
  copyQueue = items;
  for(unsigned int i = 0; i < items.size(); i++)
  {
    returnValue += copyQueue.front().avgPrepTime;
    copyQueue.pop();
  }
  return returnValue;
}

void Order::getTotal()
{
  totalPayment = 0;
  double tax = .10;
  queue<MenuItem> copyQueue;
  copyQueue = items;
  for(unsigned int i = 0; i < items.size(); i++)
  {
    this->totalPayment += copyQueue.front().price;
    copyQueue.pop();
  }
  this->totalPayment = this->totalPayment + (this->totalPayment * tax);
  //cout << this->totalPayment << endl;
  //return totalPayment;
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

#endif /* Order_h */
