#ifndef MANAGER_H
#define MANAGER_H

#include <iostream>
#include <fstream>
#include <cstdlib>

#include <string>
#include <ios>
#include <cstring>

#include "Restaurant.h"
#include "common.h"

using namespace std;
class Manager
{
    vector<MenuItem> localMenu;
public:
    Manager(bool, simulationConfig&);
    int managerLoop(simulationConfig&);
    void uploadMenuTXT();
    void updateConfigSimulation(simulationConfig&);
};

Manager::Manager(bool hasName, simulationConfig& config) //Default Constructor
{
    if (!hasName)
    {
        string input;

        cout<<"Give your restaurant a name:  ";
        getline(cin, input);
        config.restaurantName = input;
        cout<<"The restaurant name was set to " << input<<"." <<endl<<endl;

        fstream file("simulation.txt", ios::in | ios::out); // write name to simulation.txt
        file << config.restaurantName << endl<< config.chefNumber << endl<< config.maxLenWaitQue << endl<< config.timeAtNewArrStop<<endl;
        file << fixed << setprecision(2) << config.totalRevenue;

        file.close();
    }

    localMenu = MENU;
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


void Manager::updateConfigSimulation(simulationConfig& config) // upload vector menu to textfile
{
    fstream file("simulation.txt", ios::in | ios::out); // write name to simulation.txt
    file << config.restaurantName << endl<< config.chefNumber << endl<< config.maxLenWaitQue << endl << config.timeAtNewArrStop << endl;
    file << fixed << setprecision(2) << config.totalRevenue;
    file.close();
}

int Manager::managerLoop(simulationConfig& config)
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
        cout<<"[3] View Current Menu"<<endl;
        cout<<"[4] Hire new chef      ";

        cin >> buf2;
        cin.ignore();

        try
        {
            selection = stoi(buf2);
        }
        catch(exception &err)
        {
            string temp = err.what();
            selection = 5; // error handling => selection = default switch
        }
        cout<<endl;

        switch (selection)
        {
        case 0:                     // break
        {
            uploadMenuTXT();
            MENU = localMenu;
            cout<<"Okay, your menu was updated successfully. Exiting..."<<endl<<endl;
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
                string temp = err.what();
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
                string temp = err.what();
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
                if (stoi(deleteID)<0 || stoi(deleteID) >= (int)localMenu.size())
                {
                    cout<<"Please try again and enter a valid integer."<<endl;
                    break;
                }
            }
            catch(exception &err)
            {
                string temp = err.what();
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
        case 4:    // hire new chef
        {
            if(config.totalRevenue < 100)
            {
                cout<<"You don't have enough money to hire a new chef! :("<<endl<<"Come back when you have 100$.";
                break;
            }
            else
            {
                cout<<"Your total balance is " << fixed << setprecision(2) << config.totalRevenue <<"$."<<endl<<"A new chef will be 100$. Would you like to purchase?"<<endl;
                cout<<"[0] Purchase"<<endl;
                cout<<"[1] Cancel    ";

                cin >> buf2;
                cin.ignore();

                try
                {
                    selection = stoi(buf2);
                }
                catch(exception &err)
                {
                    string temp = err.what();
                    selection = 2; // error handling => selection = default switch
                }

                switch (selection)
                {
                case 0:                     // break
                {
                    config.totalRevenue -= 100.00;
                    config.chefNumber++;
                    cout<<"Purchased chef for 100$. Your new total balance: ";
                    cout << fixed << setprecision(2) << config.totalRevenue<<"$. "<<endl;
                    updateConfigSimulation(config);
                    break;
                }
                case 1:                     // add item
                {
                    cout<<"Ok, canceled purchase."<<endl;
                    break;
                }
                default:
                    cout<< " Incorrect menu ID.. retry!" << endl;
                    break;
                }
            }



            break;
        }
        default:
            cout<< " Incorrect menu ID.. retry!" << endl;
            break;
        }

    }

    return 0;
}

#endif
