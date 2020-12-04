#ifndef RESTAURANT_H
#define RESTAURANT_H
#include <iostream>
#include <string>
#include <cstdlib>
#include <map>
using namespace std;

struct item
{
    string name;
    int type;        // 0 = food. 1 = drink. food takes longer
    double price;        // ex. 1.50$
    int avgPrepTime;  // ex. 15 minutes
    bool finished = false;
};

vector<item> menu;

vector<item> foodChefs;
vector<item> drinkChefs;

struct Restaurant
{
    string name;
    double dailyIncome;
    double netIncome;
    int ordersCompleted;
    int deliveriesCompleted;
};



#endif
