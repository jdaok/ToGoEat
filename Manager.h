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

    cout<<"Give your restaurant a name:  ";
    getline(cin, input);
    //cin.ignore(1000,10);

    cout<<"The restaurant name was set to " << input<<"." <<endl<<endl;

   // restaurant.name = input;

    if (MENU.empty()) loadMenu(MENU); // in case menu wasn't loaded
    localMenu = MENU;
    showLocalMenu(localMenu);
}

void Manager::uploadMenuTXT() // upload vector menu to textfile
{
    ofstream outfile("menu.txt", ios_base::out|ios_base::trunc); // overwrite file

    outfile<<"-name"<<"\t"<<"price"<<"\t"<<"avgPrepTime"<<endl;

    for(unsigned int i=0; i< localMenu.size(); i++)
    {
        outfile<<localMenu[i].name<<"\t"<<localMenu[i].price<<"\t"<<localMenu[i].avgPrepTime<<"\t"<<endl;
    }

    outfile.close();

}

int Manager::managerLoop()
{
    string buf2;
    int selection;
    bool inLoop = true;

    while (inLoop)
    {
        cout<<endl<<"Pick an action:"<<endl;
        cout<<"[0] Exit"<<endl;
        cout<<"[1] Add Item"<<endl;
        cout<<"[2] Remove Item"<<endl;
        cout<<"[3] Print Current Menu      ";

        cin >> buf2;
        cin.ignore();

        try
        {
            selection = stoi(buf2);
        }
        catch(exception &err)
        {
            selection = 4; // error handling => selection = default switch
        }
        cout<<endl;

        switch (selection)
        {
        case 0:                     // break
        {
            uploadMenuTXT();
            MENU = localMenu;
            cout<<"Okay, your menu was updated successfully. Exiting...";
            inLoop = false;
            break;
        }
        case 1:                     // add item
        {
            string userInput;         // get user input
            MenuItem tempItem;
            cout<<"Ok. What is the item name?  "<<endl;
            cin >> buf2;
            cin.ignore(1000,10);
            tempItem.name = buf2;

            cout<<"Ok. How much does "<< tempItem.name<<" cost? (dollars)  "<<endl;
            cin >> buf2;
            cin.ignore(1000,10);
            try
            {
                tempItem.price = stod(buf2);
            }
            catch(exception &err)
            {
                cout << "Please try again and  enter a valid double.  "<<endl;
                break;
            }

            cout<<"Ok. How many minutes will "<< tempItem.name<<" take to prepare?  "<<endl;
            cin >> buf2;
            cin.ignore(1000,10);
            try
            {
                tempItem.avgPrepTime = stoi(buf2);
            }
            catch(exception &err)
            {
                cout << "Please try again and enter a valid integer.  "<<endl;
                break;
            }

            tempItem.idNumber = 999; // temp ID number.

            localMenu.push_back(tempItem); // add the item to the menu
            showLocalMenu(localMenu);
            cout<<endl<<"                        "<<tempItem.name<<" was added to the menu."<<endl;
            break;

        }
        case 2:
        {
            showLocalMenu(localMenu);
            string deleteID;
            cout<<"Ok. Enter the ID to delete.";
            cin>>deleteID;

            try
            {
                if (stoi(deleteID)<0 || stoi(deleteID) >= localMenu.size())
                {
                    cout<<"Please try again and enter a valid integer."<<endl;
                    break;
                }
            }
            catch(exception &err)
            {
                cout << "Please try again and enter a valid integer."<<endl;
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
            cout<< " Incorrect menu ID.. retry!" << endl;
            break;
        }

    }
}

#endif
