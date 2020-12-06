//
//  Created by Max Raffield on 12/3/20.
//

#ifndef Order_h
#define Order_h

#include <iostream>
#include <string>
#include <cstdlib>
#include <map>
#include <queue>
#include <vector>
#include <cstring>

#include "common.h"


using namespace std;

class Order
{
    string customerName;
    int orderID;
    double totalPayment;
    queue<MenuItem> items;

public:
    //string customerName;
    //int orderID;
    int status; //1 = Ordering, 2 = Cooking, 3 = Finished
    //queue<MenuItem> items;
    //double totalPayment;

    Order(); //Default Constructor
    void createOrderItems(vector<MenuItem> menu); //Creates Random Orders
    //Let user type the order
    bool makeOrder(const vector<MenuItem>& menu);

    int generateID();

    //Item Functions
    void addItem(int, vector<MenuItem> menu);
    void deleteItems();
    void getTotal();
    int getServiceTime();

    //Status Functions
    void setStatus(int);
    string reportStatus();
    void getSummary();
    void printOrder();

    //Paying Functions
    bool pay();

    int getID() const
    {
        return orderID;
    }
    string getCustomerName()
    {
        return customerName;
    }
    double getTotalPayment()
    {
        return totalPayment;
    }

};

Order::Order() //Default Constructor
{

    orderID = generateID();
    status = 1;
    totalPayment = 0;
    for (unsigned int i = 0; i < items.size(); i++)
    {
        items.pop();
    }
}

void Order::printOrder()
{
    queue<MenuItem> itemsCopy = items;
    while (itemsCopy.empty() == false)
    {
        cout << itemsCopy.front().name << "      " << fixed << setprecision(2) << itemsCopy.front().price <<"$" << endl;
        itemsCopy.pop();
    }

    getTotal();

    cout << "----- Total $: " << totalPayment << endl;
}

int Order::generateID() //Generates Random ID
{
    srand((unsigned)time(NULL));
    int ID = rand() % 899999 + 100000;
    return ID;
}

//let user type the order
bool Order::makeOrder(const vector<MenuItem>& menu)
{
    //Create New Order
    //Order newOrder;

    cout << endl; //Ask Name
    cout << "Okay, what is your name?  " << endl;
    string nameInput;
    getline(cin, nameInput);
    customerName = nameInput;

    cout << "Hi, " << customerName<<"! Here's the menu:" << endl<< endl;
    showMenu(menu);

    string buf;
    int selection;

    bool next = false;
    do
    {
        cout<<endl<<"Select an option:"<<endl;
        cout<<"[1] Add Item to Order"<<endl;
        cout<<"[2] Clear all Items"<<endl;
        cout<<"[3] Print Order"<<endl;
        cout<<"[4] Finish"<<endl;
        cout<<"[5] Cancel      ";

        cin >> buf;
        cin.ignore();

        try
        {
            selection = stoi(buf);
        }
        catch(exception &err)
        {
            string temp = err.what();
            selection = 6; // error handling => selection = default switch
        }
        cout<<endl;

        switch (selection)
        {
        case 1:
            int itemID;
            showMenu(menu);
            cout <<endl<< "Okay, what ID?    ";
            cin >> buf;
            cin.ignore(1000, 10);

            try
            {
                itemID = stoi(buf.c_str());
                if (itemID < 0 || itemID > (int)menu.size())
                    cout << "wrong item ID" << endl;
                else
                    addItem(itemID, menu);
            }
            catch (exception& err)
            {
                string temp = err.what();
                cout << endl;
				cout << "Please enter a valid input." << endl;
                break;
            }
            break;

        case 2:
            if (items.empty())
            {
                cout<<"Your cart is empty!" <<endl;
            }
            else cout << "Ok, all items were removed from cart." << endl;
            deleteItems();
            break;
        case 3:
            cout << endl;
            if (items.empty())
            {
                cout<<"Your cart is empty!" <<endl;
                break;
            }
            cout << "Your order: ------- " << endl;
            printOrder();
            break;
        case 4:
            //finish the order
            if (menu.empty()) {cout<<"Your cart is empty!" <<endl;
            break;}
            next = true;
            break;
        case 5:
            next = true;
            break;
        default:
            cout << "Please enter a valid option." << endl;
            cin.ignore(1000, 10);
            break;
        }

    }
    while (!next);

    //customer finishes the order
    if (selection == 4)
    {
        bool ret = pay();
        if (!ret)
        {
            deleteItems();
        }
        return ret;
    }
    else if (selection == 5)  // customer cancels the order
    {
        deleteItems();
        return false;
    }
    else
    {
        return false;
    }
}

bool Order::pay()
{
    //show the items and their price, the tax(sum of items price*defalut tax rate), total price
    //let user type to pay
    string buf;
    int input = 0;

    while (true)
    {
        getTotal();
        cout << "The total is: " << fixed << setprecision(2) << totalPayment <<"."<< endl;
        cout << "[1] Pay" << endl << "[2] Cancel" << endl;

        cin >> buf;
        cin.ignore();

        try
        {
            input = stoi(buf);
        }
        catch(exception &err)
        {
            string temp = err.what();
            input = 3; // error handling => retry
        }

        cout<<endl;

        if (input == 1)
        {
            if (totalPayment == 0)
            {
                cout << endl;
                cout << "Total is 0... canceling order." << endl;
                cout<<endl<<endl;
                return false;
            }
            else
            {
                cout << endl;
                cout << "Thank you!" << endl;
                cout << "RECEIPT: ----------" << endl;
                printOrder();
                cout<<endl<<endl;
                return true;
            }
            break;
        }
        else if (input == 2)
        {
            cout << endl;
            cout << "Okay, your order was cancelled." << endl;
            cout<<endl;
            return false;
        }
        else
        {
            cout << "Invalid input. Please re-enter." << endl;
        }
    }

}

void Order::addItem(int idNum, vector<MenuItem> menu) //Adds Item to Order
{

    MenuItem tempItem;
    for (auto& it : menu)
    {
        if (it.idNumber == idNum)
        {

            tempItem.name = it.name;
            tempItem.idNumber = it.idNumber;
            tempItem.price = it.price;
            tempItem.avgPrepTime = it.avgPrepTime;
            //tempItem.amount = amount;
            //items.insert(pair<MenuItem, int>(tempItem, amount));
            items.push(tempItem);

            cout<<"                  "<<it.name<<" was added to your order."<<endl;
            break;
        }
    }
}

void Order::deleteItems()
{
    for (unsigned int i = 0; i < items.size(); i++)
    {
        items.pop();
    }
}

int Order::getServiceTime()
{
    int returnValue = 0;
    queue<MenuItem> copyQueue;
    copyQueue = items;
    for (unsigned int i = 0; i < items.size(); i++)
    {
        returnValue += copyQueue.front().avgPrepTime;
        copyQueue.pop();
    }
    return returnValue;
}

void Order::getTotal()
{
    totalPayment = 0;
    queue<MenuItem> copyQueue;
    copyQueue = items;
    for (unsigned int i = 0; i < items.size(); i++)
    {
        this->totalPayment += copyQueue.front().price;
        copyQueue.pop();
    }
    this->totalPayment = this->totalPayment + (this->totalPayment * TAX);
    //cout << this->totalPayment << endl;
    //return totalPayment;
}

void Order::setStatus(int setValue) //Set Value of Status
{
    status = setValue;
}

string Order::reportStatus() //Returns Order Status
{
    string returnValue = "";
    switch (this->status)
    {
    case 1:
        returnValue = "Status: Currently Ordering";
        break;
    case 2:
        returnValue = "Status: Cooking";
        break;
    case 3:
        returnValue = "Status: Order Finished";
        break;
    default:
        returnValue = "No Status";
    }
    return returnValue;
}


#endif /* Order_h */
