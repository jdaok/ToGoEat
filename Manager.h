#ifndef MANAGER_H
#define MANAGER_H

#include <iostream>
#include <fstream>
#include <cstdlib>

#include <string>
#include <cstring>

#include "Restaurant.h"
#include "common.h"
using namespace std;

class Manager
{
public:
    vector<MenuItem> localMenu;
    Manager();
    int managerLoop();
    void uploadMenuTXT();
};

Manager::Manager() //Default Constructor
{
    string input;

    cout<<"Create your first restaurant!"<<endl<<"Give your restaurant a name:  ";
    getline(cin, input);
    cin.ignore(1000,10);
   // restaurant.name = input;

    localMenu = MENU;

   // cout<<endl<<"Great! Here's the menu for "<<restaurant.name<<"... "<<endl<<endl;
    showLocalMenu(localMenu);
}

void Manager::uploadMenuTXT() // upload vector menu to textfile
{
    ofstream outfile("menu.txt", ios_base::out|ios_base::trunc); // overwrite file

    char* token;
    char buf[1000];
    const char* const tab = "\t";

    outfile<<"-name"<<"\t"<<"price"<<"\t"<<"avgPrepTime"<<endl;

    for(int i=0; i< localMenu.size(); i++)
    {
        outfile<<localMenu[i].name<<"\t"<<localMenu[i].price<<"\t"<<localMenu[i].avgPrepTime<<"\t"<<endl;
    }

    outfile.close();

}

int Manager::managerLoop()
{
    string buf2;
    int selection;

    while (true)
    {
        cout<<endl<<"Pick an action:"<<endl;
        cout<<"[0] Exit"<<endl;
        cout<<"[1] Add Item"<<endl;
        cout<<"[2] Remove Item"<<endl;
        cout<<"[3] Print Current Menu      ";

        cin >> buf2;
        cin.ignore(1000,10);
        selection = stoi(buf2);

        cout<<endl;

        switch (selection)
        {
        case 0:                     // break
        {
            uploadMenuTXT();
            MENU = localMenu;
            return 0;
            break;
        }
        case 1:                     // add item
        {
            string userInput;         // get user input
            MenuItem tempItem;
            cout<<"Ok. What is the item name?"<<endl;
            cin >> buf2;
            cin.ignore(1000,10);
            tempItem.name = buf2;

            cout<<"Ok. How much does "<< tempItem.name<<" cost? (dollars)"<<endl;
            cin >> buf2;
            cin.ignore(1000,10);
            tempItem.price = stod(buf2);

            cout<<"Ok. How many minutes will "<< tempItem.name<<" take to prepare?"<<endl;
            cin >> buf2;
            cin.ignore(1000,10);
            tempItem.avgPrepTime = stoi(buf2);

            tempItem.idNumber = 999; // temp ID number.

            localMenu.push_back(tempItem); // add the item to the menu
            showLocalMenu(localMenu);
            cout<<endl<<"                        "<<tempItem.name<<" was added."<<endl;
            break;

        }
        case 2:
        {
            showLocalMenu(localMenu);
            string deleteID;
            cout<<"Ok. Enter the ID to delete.";
            cin>>deleteID;

            if (stoi(deleteID)<0 || stoi(deleteID) >= localMenu.size())
            {
                cout<<"INVALID ID. Try again."<<endl;
                break;
            }
            string deleteName = localMenu[stoi(deleteID)].name;
            localMenu.erase (localMenu.begin()+stoi(deleteID));
            cout<<endl<<"                        "<<deleteName<<" was deleted."<<endl;
            break;
        }
        case 3:    // show menu
        {
            showLocalMenu(localMenu);
            break;
        }
        default:
            cout<< " Incorrect menu ID.. retry!";
            break;
        }
    }
}

#endif
