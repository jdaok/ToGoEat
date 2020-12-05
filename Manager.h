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
    Manager();
    int managerLoop();
};

Manager::Manager() //Default Constructor  setup the restaurant + load items
{
    string input;

    cout<<"Create your first restaurant!"<<endl<<"Give your restaurant a name:  ";
    getline(cin, input);
    cin.ignore(1000,10);
    restaurant.name = input;
    cout<<endl<<"Great! Loading menu for "<<restaurant.name<<"... "<<endl;

    loadMenu(MENU);
    cout<<"Loaded "<<MENU.size()<<" items onto the menu."<<endl;
    showMenu(MENU);
}

int Manager::managerLoop()
{
    string buf2;
    int selection;

    while (true)
    {
        cout<<endl<<"Pick an action:"<<endl;
        cout<<"                 [0] Continue"<<endl;
        cout<<"                 [1] Add Item"<<endl;
        cout<<"                 [2] Remove Item"<<endl;
        cout<<"                 [3] Print Current Menu"<<endl;

        cin >> buf2;
        cin.ignore(1000,10);
        selection = stoi(buf2);

        switch (selection)
        {
        case 0:                     // break
        {
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

            tempItem.idNumber = 999;

            MENU.push_back(tempItem); // add the item to the menu

            fstream menustr;                             // sync the c++ menu with the text file by adding a line
            menustr.open("menu.txt", fstream::app);
            menustr<<tempItem.name<<"\t"<<tempItem.price<<"\t"<<tempItem.avgPrepTime<<"\t"<<endl;
            menustr.close();

            loadMenu(MENU);
            showMenu(MENU);
            cout<<endl<<"                        "<<tempItem.name<<" was added."<<endl;
            break;

        }
        case 2:
        {
            string line, deleteID;
            cout<<"Ok. Enter the ID to delete.";
            cin>>deleteID;

            if (stoi(deleteID)<0 || stoi(deleteID) >= MENU.size())
            {
                cout<<"INVALID ID. Try again."<<endl;
                break;
            }

            string deleteName = MENU[stoi(deleteID)].name; // find the name of the item of the id

            ifstream file;
            ofstream outfile;

            file.open("menu.txt");               // create a new menu file and copy all the lines over except the deleted one
            outfile.open("newMenu.txt");

            char* token;
            char buf[1000];
            const char* const tab = "\t";


            while(getline(file,line))
            {
                strcpy(buf, line.c_str());
                if (buf[0] == 0) continue; // skip blank lines

                const string searchName(token = strtok(buf, tab));
                if(searchName!=deleteName)
                    outfile<<line<<endl;
            }
            outfile.close();
            file.close();
            remove("menu.txt");
            rename("newMenu.txt","menu.txt");

            loadMenu(MENU);
            showMenu(MENU);
            cout<<endl<<"                        "<<deleteName<<" was deleted."<<endl;
            break;
        }
        case 3:    // show menu
        {
            showMenu(MENU);
            break;
        }
        default:
            cout<< " Incorrect menu ID.. retry!";
            break;
        }
    }
}

#endif
