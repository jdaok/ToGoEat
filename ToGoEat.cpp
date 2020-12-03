//
//  ToGoEat.cpp
//  
//
//  Created by Max Raffield on 11/29/20.
//

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <map>
#include <string>
#include <cstring>
#include "DynamicArray.h"

using namespace std;

//Function Templates
int askMode();
bool getPassword();
int askManager();


struct item
{
    double price;        // ex. 1.50$
    int avgPrepTime;  // ex. 15 minutes
    int maxAmt;          // maximum amount of this item per order: ex. you can only order 5 pizza's at a time
};


struct Restaurant
{
    string name;
    map<string, item> items; // menu of items. key = name string, value = struct item
    double dailyIncome;
    double netIncome;
    int ordersCompleted;
    int deliveriesCompleted;
};



int main()
{
    //Modes
    int mode = 0; //1 - Customer, 2 - Manager
    mode = askMode();
    cin.ignore();
    cout << endl;

    string input;
    ifstream fin;
    char* token;
    char buf[1000];
    const char* const tab = "\t";

    //Manager Side

    if(mode == 2)
    {
        //Check Password
        cout << "You are attempting to use the Manager-side of the program." << endl<< endl;

        // Create restuarant

        Restaurant restaurant;

        cout<<"Create your first restaurant!"<<endl<<"Give your restaurant a name:  ";
        cin >> input;
        restaurant.name = input;
        cout<<endl<<"Great! Loading menu for "<<restaurant.name<<"... "<<endl;

        // Load menu.txt

        fin.open("menu.txt");
        if (!fin.good())
            cout << "I/O error. File can't find!\n";

        while (fin.good())
        {
            // read the line

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


            // add item to restaurant menu map
            item tempItem;
            tempItem.price = stod(price);
            tempItem.avgPrepTime = stoi(avgPrepTime);
            tempItem.maxAmt = stoi(maxAmt);
            restaurant.items.insert(pair<string, item>(name, tempItem));
        }

        cout<<"Loaded "<<restaurant.items.size()<<" items onto the menu."<<endl;
        fin.close();
      
      //Manager Options
      //-1 = Quit, 1 = Create Item, 2 = Remove Item
      int managerMode = 0;
      bool continueManager = true;
      int managerInput = 0;
      
      while(continueManager)
      {
        managerInput = askManager();
        
        switch(managerInput)
        {
          case -1:
            continueManager = false;
            break;
          case 1:
            managerMode = 1;
          case 2:
            managerMode = 2;
            default:
            cout << "Invalid choice." << endl;
        }
        
        if(managerMode == 1) //Adding Menu Item
        {
          item newItem;
          string newName = "", newPrice = "", newTime = "", newAmt = "";
          cout << endl;
          cout << "What is the item's name?" << endl;
          getline(cin, newName);
          cout << "What is the item's price?" << endl;
          getline(cin, newPrice);
          cout << "What is the average preparation time?" << endl;
          getline(cin, newTime);
          cout << "What is the maximum amount?" << endl;
          getline(cin, newAmt);
          
          newItem.price = atof(newPrice.c_str());
          newItem.avgPrepTime = atoi(newTime.c_str());
          newItem.maxAmt = atoi(newAmt.c_str());
          restaurant.items.insert(pair<string, item>(newName, newItem));
        }
        
        else if(managerMode == 2) //Removing Menu Item
        {
          string itemName = "";
          cout << endl;
          cout << "What is the name of the item to be removed?" << endl;
          getline(cin, itemName);
          if(restaurant.items.find(itemName) != restaurant.items.end()) //Item Found
          {
            restaurant.items.erase(restaurant.items.find(itemName));
          }
          else //Not Found
          {
            cout << "Item was not found. " << endl;
          }
        }
      }

        /*

        bool correctPassword = getPassword();
            if(correctPassword == false)
            {
              cout << endl;
              cout << "Switching over to Customer-side." << endl;
              mode = 1;
            }

            if(correctPassword == true)
            {
              cout << endl;
              cout << "Successfully using Manager-side of the program." << endl;
            }

            if(mode == 2) //Re-checking for Manager-side
            {

            */

    }

    //Customer Side
    if(mode == 1)
    {
      cout << "You are now using the Customer-side of the program." << endl;
        while (true)
        {
          cout << endl;
          cout << "What would you like to order?" << endl;
          
          //Open Menu and Read
          
          //Place Order
          
        }
    }

}

int askMode() //Ask for Customer or Manager
{
    string buf = "";
    int buffer = 0, returnValue = 0;
    bool valid = false;

    while(valid == false)
    {
        cout << endl;
        cout << "Customer or manager? [1 = Customer, 2 = Manager]" << endl;
        cin >> buf;
        buffer = atoi(buf.c_str());

        switch(buffer)
        {
        case 1:
            returnValue = 1;
            valid = true;
            break;
        case 2:
            returnValue = 2;
            valid = true;
            break;
        default:
            cout << endl;
            cout << "Invalid input, try again." << endl;
        }
    }

    return returnValue;
}

bool getPassword() //Password-checker
{
    bool returnValue = false;
    bool keepPlaying = true;
    string userPass = "", realPass = "";
    ifstream fin;

    fin.open("password.txt");
    if(!fin.good())
        cout << "I/O error. Can't find file!\n";

    while(fin.good())
    {
        getline(fin, realPass);
    }

    while(keepPlaying == true)
    {
        cout << endl;
        cout << "Enter the password: [Enter XXX to switch to Customer]" << endl;
        getline(cin, userPass);

        //Change to Customer-side
        if(userPass == "XXX")
        {
            keepPlaying = false;
            break;
        }

        //Correct Password
        if(userPass == realPass)
        {
            returnValue = true;
            keepPlaying = false;
            break;
        }

        //Incorrect Password
        if(userPass != realPass)
        {
            cout << endl;
            cout << "Incorrect Password, try again." << endl;
        }
    }
    return returnValue;
}

int askManager()
{
  int returnValue = 0;
  cout << endl;
  cout << "Select an option: " << endl;
  cout << "[-1 = Quit]" << endl;
  cout << "[1 = Create a Menu Item]" << endl;
  cout << "[2 = Remove a Menu Item]" << endl;
  cin >> returnValue;
  
  return returnValue;
}
