#ifndef MANAGER_H
#define MANAGER_H
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <map>
#include <cstring>
#include <iomanip>

#include "Restaurant.h"
using namespace std;

// prototypes

void managerSetup();
int manager();
void loadMenu();
void showMenu(vector<item> menu);

void managerSetup()
{

    string input;


    cout<<"Create your first restaurant!"<<endl<<"Give your restaurant a name:  ";
    cin >> input;
    restaurant.name = input;
    cout<<endl<<"Great! Loading menu for "<<restaurant.name<<"... "<<endl;

    loadMenu();
    cout<<"Loaded "<<menu.size()<<" items onto the menu."<<endl;

}



int manager()
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
        cin.ignore();
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
            item tempItem;
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


            tempItem.idNumber = menu.size();

            if (!restaurant.deletedIDs.empty()){ // if theres a whole in the ID's from removing, use it instead of creating a new ID
                tempItem.idNumber = restaurant.deletedIDs.top();
                restaurant.deletedIDs.pop();
            }

            menu.push_back(tempItem); // add the item to the menu

            showMenu(menu);

            fstream menustr;                             // sync the c++ menu with the text file by adding a line
            menustr.open("menu.txt", fstream::app);
            menustr<<tempItem.idNumber<<"\t"<<tempItem.name<<"\t"<<tempItem.price<<"\t"<<tempItem.avgPrepTime<<"\t"<<endl;
            menustr.close();

            cout<<"                                  "<<tempItem.name<<" was added."<<endl;
            break;

        }
        case 2:
        {
            string line, deleteID;
            cout<<"Ok. Enter the ID to delete.";
            cin>>deleteID;

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

                const string searchID(token = strtok(buf, tab));
                if(searchID!=deleteID)
                    outfile<<line<<endl;
            }
            outfile.close();
            file.close();
            remove("menu.txt");
            rename("newMenu.txt","menu.txt");

            restaurant.deletedIDs.push(stoi(deleteID));     // save the deleted ID

            menu.clear();                   // refresh the c++ menu to sync
            loadMenu();
            break;
        }
        case 3:    // show menu
        {
            showMenu(menu);
            break;
        }
        default:
            cout<< " Incorrect menu ID.. retry!";
            break;
        }
    }
}

void loadMenu()
{
    string input;
    ifstream fin;
    char* token;
    char buf[1000];
    const char* const tab = "\t";

    // Create restuarant


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
        const string ID(token = strtok(buf, tab));


        if (ID.find('-') != string::npos) continue; // skip first line which has a dash in it

        const string name((token = strtok(0, tab)) ? token : "");
        const string price((token = strtok(0, tab)) ? token : "");
        const string avgPrepTime((token = strtok(0, tab)) ? token : "");

        // add item to restaurant menu map
        item tempItem;
        tempItem.idNumber = stoi(ID);

        tempItem.name = name;
        tempItem.price = stod(price);
        tempItem.avgPrepTime = stoi(avgPrepTime);
        menu.push_back(tempItem);
    }

    fin.close();
    showMenu(menu);
}


void showMenu(const vector<item> menu)
{
    const int width2 = 12;

    cout << right<<setw(width2) << "ID# " <<
         setw(width2) << "name" <<
         setw(width2) << "price" << endl;

    cout << right<<setw(width2) << "----" <<
         setw(width2) << "----" <<
         setw(width2) << "-----" << endl;

    for (int i = 0; i < menu.size(); i++)
    {
        cout << right<<setw(width2) << menu[i].idNumber <<
             setw(width2) << menu[i].name <<
             setw(width2) << menu[i].price << endl;
    }
}






#endif

