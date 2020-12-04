//
//  Order.h
//  
//
//  Created by Max Raffield on 12/3/20.
//

#ifndef Order_h
#define Order_h

#include <iostream>
#include <string>
#include <cstdlib>
#include <list>
#include <vector>
#include <fstream>

using namespace std;

struct item
{
    string name;
    int idNumber;
    double price;
    int avgPrepTime;
    int maxAmt;
};

struct menuItem
{
  string name;
  int idNumber;
  int amount;
};

class order
{
    int orderID;
    int status; //1 = Ordering, 2 = Paying, 3 = Cooking, 4 = Finished
    bool paid;
    list<item, int> items;
    
public:
    order(); //Default Constructor
    vector<item> createMenu(); //Show Menu
    void readMenu();
    void addItem(int, int);
    void setStatus();
    int getStatus();
    string reportStatus();
    void getSummary();
    
    void pay();
    void finishOrder();
};

order::order() //Default Constructor
{
  status = 1;
  paid = false;
}

vector<item> order::createMenu() //Creates Menu to Read
{
    vector<item> menu;
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
      tempItem.maxAmt = stoi(maxAmt);
    }
  
  return menu;
}

void order::readMenu() //Reads Menu
{
  vector<item> menu = createMenu();
  
  for(auto& it: menu)
  {
    cout << "Item Name: " << it.name << endl;
    cout << "Item ID: " << it.idNumber << endl;
    cout << "Item Price: " << it.price << endl;
  }
}

void order::addItem(int idNumber, int amount) //Adds Item to Order
{
    menuItem tempItem;
    vector<item> menu = createMenu();
    for(auto& it: menu)
    {
      if(it.idNumber == idNumber)
      {
        tempItem.name = it.name;
        tempItem.idNumber = it.idNumber;
        tempItem.amount = amount;
        items.insert(tempItem);
        break;
      }
    }
}

void order::getSummary() //Returns Summary
{
  cout << endl;
  cout << "Order #" << orderID << " - " << endl;
  for(auto& it: this->items)
    {
      cout << it.idNumber << " " << it.name << " (" << it.amount << ")" << endl;
    }
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
      returnValue = "Status: Paying";
      break;
    case 3:
      returnValue = "Status: Cooking";
      break;
    case 4:
      returnValue = "Status: Order Finished";
    default:
      returnValue = "No Status";
  }
  
  return returnValue;
}

void order::finishOrder()
{
    
}

#endif /* Order_h */
