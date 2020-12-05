#ifndef RESTAURANT_H
#define RESTAURANT_H
#include <iostream>
#include <string>
#include <cstdlib>
#include <map>

using namespace std;

#include <iostream>
#include <string>
#include <cstdlib>
#include <map>

using namespace std;

#include "common.h"

vector<MenuItem> foodChefs;
vector<MenuItem> drinkChefs;

struct Restaurant
{
    string name;
    double dailyIncome;
    double netIncome;
    int ordersCompleted;
    int deliveriesCompleted;
  
    //Functions
    void getSummary();
};

void Restaurant::getSummary()
{
  cout << "Name: " << name << endl;
  cout << "Daily Income: " << dailyIncome << endl;
  cout << "Net Income: " << netIncome << endl;
  cout << "Orders Completed: " << ordersCompleted << endl;
  cout << "Deliveries Completed: " << deliveriesCompleted << endl;
}

#endif
