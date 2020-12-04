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
#include <map>
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

class order
{
    int orderID;
    int status; //1 = Ordering, 2 = Paying, 3 = Cooking, 4 = Finished
    bool paid;
    map<item, int> items; //Int is for amount
    
public:
    order(); //Default Constructor
    order createOrder(); //Creates Random Orders
    int generateID();
  
  //Menu Functions
    vector<item> createMenu(); //Show Menu
    void readMenu();
  
  //Item Functions
    void addItem(int, int);
  
  //Status Functions
    void setStatus(int);
    string reportStatus();
    void getSummary();
  
  //Paying Functions
    void pay(double);
    void finishOrder();
};

order::order() //Default Constructor
{
  orderID = generateID();
  status = 1;
  paid = false;
}

int order::generateID() //Generates Random ID
{
  srand((unsigned)time(NULL));
  int ID = rand() % 899999 + 100000;
  
  return ID;
}

order order::createOrder()
{
  srand((unsigned)time(NULL));
  order newOrder;
  vector<item> menu = createMenu();
  for(auto& it: menu)
  {
    int amount = rand() % it.maxAmt;
    newOrder.addItem(it.idNumber, amount);
  }
  return newOrder;
}

vector<item> order::createMenu() //Creates Menu to Read
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
      tempItem.maxAmt = stoi(maxAmt);
    }
  
  return returnMenu;
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
    item tempItem;
    vector<item> menu = createMenu();
    for(auto& it: menu)
    {
      if(it.idNumber == idNumber)
      {
        tempItem.name = it.name;
        tempItem.idNumber = it.idNumber;
        tempItem.price = it.price;
        //tempItem.amount = amount;
        items.insert(pair<item, int>(tempItem, amount));
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
  cout << endl;
}

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
      returnValue = "Status: Paying";
      break;
    case 3:
      returnValue = "Status: Cooking";
      break;
    case 4:
      returnValue = "Status: Order Finished";
      break;
    default:
      returnValue = "No Status";
  }
  
  return returnValue;
}

void order::pay(double tax)
{
  double total = 0;
  map<item, int>::iterator it;
  vector<item> menu = createMenu();
  for(it = items.begin(); it != items.end(); it++)
  {
    for(int i = 0; i < it->second; it++)
    {
      total += it->first.price;
    }
  }
  
  total += (tax * total);
  paid = true;
}

void order::finishOrder()
{
  
}

#endif /* Order_h */
