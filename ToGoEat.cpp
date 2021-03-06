//Programmer:Jiefeng Yang
//Programmer's ID:1791121

#define _CRT_SECURE_NO_WARNINGS

#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

#include <cmath>
#include <cstdlib>

#include "PriorityQueue.h"
#include "DynamicArray.h"
#include "Queue.h"

#include "Order.h"
#include "Manager.h"

struct ServiceEvent
{
    int serverNum;
    int serviceEndTime;
};

struct ServerInfo
{
    Order order;
    bool status;
};

//for comparing ServiceEvent in PriorityQueue template
bool operator<(const ServiceEvent& a, const ServiceEvent& b)
{
    //switch to lo-to-hi priority
    return b.serviceEndTime < a.serviceEndTime;
}

const int W1 = 23;   //cout width. W1 for title
const string CONFIG_FILE_NAME = "simulation.txt";

//void outputProgrammerInfo();
bool loadSimulationConfig(string fileName, simulationConfig& config);
void outputTitle(simulationConfig config);

bool shouldEndSimulation(int time, const Queue<Order>& waitLine, const simulationConfig& config,
                         const DynamicArray<ServerInfo>& servers);
void outputServiceEndingTime(const PriorityQueue<ServiceEvent>& eventQueue);
void outputSummary(int time, const Queue<Order>& waitLine, const simulationConfig& config,
                   const DynamicArray<ServerInfo>& servers);


string pauseForUserEnter();
int askMode();

int main()
{
    simulationConfig config;  //simulation config data
    if (!loadSimulationConfig(CONFIG_FILE_NAME, config))
    {
        cout << "Error loading file: " << CONFIG_FILE_NAME <<
             ". Please check and rerun the program." << endl;
        return 1;
    }
    outputTitle(config);

    Queue<Order> waitLine;
    PriorityQueue<ServiceEvent> eventQueue;
    DynamicArray<ServerInfo> servers;

    //Modes
    int mode = 0; //1 - Customer, 2 - Manager
    mode = askMode();
    cin.ignore();
    cout << endl;

    //loadMenu
    loadMenu(MENU);
    Manager manager(true, config);


    //Manager side
    if (mode == 2)
    {
        manager.managerLoop(config);
        mode = 1;
    }

    if (mode == 1)
    {
        loadMenu(MENU);
        cout<<"You are now the customer!"<<endl;
        int orderCount = 0;
        double dailyRevenue = 0;
        for (int time = 0;; time++)
        {
            //handle all services scheduled
            while (!eventQueue.empty() && eventQueue.top().serviceEndTime <= time)
            {
                servers[eventQueue.top().serverNum].status = false;
                eventQueue.pop();
            }

            //handle new arrivals
            string temp = pauseForUserEnter();
            //user type order
            if ((waitLine.size() < config.maxLenWaitQue) && (temp == "M" || temp == "m"))
            {
                Order tempOrder;
                bool ret = tempOrder.makeOrder(MENU);
                if (ret)
                {
                    waitLine.push(tempOrder);
                }

                orderCount++;
                dailyRevenue += tempOrder.getTotalPayment();
            }

            // for idle servers, move Order from wait queue and begin service for each server
            for (int i = 0; i < config.chefNumber; i++)
            {
                if (!servers[i].status && !waitLine.empty())
                {
                    servers[i].order = waitLine.front();
                    servers[i].status = true;

                    //ServiceTime for this order
                    int serviceTime = servers[i].order.getServiceTime();

                    waitLine.pop();

                    ServiceEvent temp;
                    temp.serviceEndTime = time + serviceTime;
                    temp.serverNum = i;
                    eventQueue.push(temp);
                }
            }

            outputSummary(time, waitLine, config, servers);
            outputServiceEndingTime(eventQueue);

            if (shouldEndSimulation(time, waitLine, config, servers))
                break;

        }

        config.totalRevenue += dailyRevenue; // calculate new total revenue
        manager.updateConfigSimulation(config);

        //output the total numer of the order and total amount of money the restaurant made.

        cout << "Busy day! Today, "<<config.restaurantName<<" took " << orderCount << " orders."<<endl<<config.restaurantName<<" made "
             << fixed << setprecision(2) << dailyRevenue <<"$!"<< endl << "Total revenue: " << config.totalRevenue <<".";
        cout << endl << endl << "Done!" << endl;

    }

    return 0;
}




//*****************
//Function name: loadSimulationConfig
//Purpose: process Simulation Config file
//fileName: Config file name
//config: config data(input & output)
//Returns: True-succed False-fail
//Return type: bool
//*****************
bool loadSimulationConfig(string fileName, simulationConfig& config)
{
    bool ret = true;
    char buf[1000];

    ifstream fin;
    fin.open(fileName);
    if (!fin.good())
    {
        cout << "Error opening simulation.txt." << endl;
        return false;
    }

    bool setName = false;

    if (fin.good())
    {

        string line;
        getline(fin, line);
        strcpy(buf, line.c_str());
        if (buf[0] == 0)  // prompt to set name if first line is empty
        {
            setName = true;
        }
        else{config.restaurantName = buf;}

        getline(fin, line);
        strcpy(buf, line.c_str());
        config.chefNumber = stoi(buf);
        if (config.chefNumber < 1)
        {
            cout << "Config Error: the number of servers need to be 1 or more." << endl;
            ret = false;
        }

        getline(fin, line);
        strcpy(buf, line.c_str());
        config.maxLenWaitQue = stoi(buf);
        if (config.maxLenWaitQue < 1)
        {
            cout << "Config Error: the maximum length of the wait queue need to be 1 or more." << endl;
            ret = false;
        }

        getline(fin, line);
        strcpy(buf, line.c_str());
        config.timeAtNewArrStop = stoi(buf);
        if (config.timeAtNewArrStop < 0)
        {
            cout << "Config Error: the clock time at which new arrivals stop, in minutes needs to > 0" << endl;
            ret = false;
        }

        getline(fin, line);
        strcpy(buf, line.c_str());
        config.totalRevenue = stod(buf);
        if (config.timeAtNewArrStop < 0)
        {
            cout << "Config Error: the total revenue should be positive." << endl;
            ret = false;
        }

        if (setName) // set name if it needs to be set by passing false parameter
        {
            Manager manager(false, config);
        }


        fin.close(); // done with the file

    }
    return ret;
}


//*****************
//Function name: outputTitle
//Purpose: output Title
//config: config data
//Returns: None
//Return type: void
//*****************
void outputTitle(simulationConfig config)
{
    cout << "******** Welcome to "<< config.restaurantName <<"! ********" << endl;
    cout << setw(W1) << left << "Chefs at work:" << config.chefNumber << endl;
    cout << setw(W1) << left << "Closing time: " << setw(3) << config.timeAtNewArrStop << endl;
    cout << setw(W1) << left << "Order Waitlist size: " << config.maxLenWaitQue << endl;
    cout << setw(W1) << left << "Total revenue: " << config.totalRevenue << endl << endl;
}



bool shouldEndSimulation(int time, const Queue<Order>& waitLine, const simulationConfig& config,
                         const DynamicArray<ServerInfo>& servers)
{
    string kesh;
    bool end = false;
    if (waitLine.empty() && time >= config.timeAtNewArrStop)
    {
        for (int i = 0; i < config.chefNumber; i++)
        {
            if (servers[i].status)
                break;
            if (i == config.chefNumber - 1)
                end = true;
        }
    }

    return end;
}

void outputSummary(int time, const Queue<Order>& waitLine, const simulationConfig& config,
                   const DynamicArray<ServerInfo>& servers)
{
    cout << left << setw(6) << "Time:" << time << right << endl;
    string title1 = "chef  ", title2 = "now serving", title3 = "customer name   ", title4 = "wait queue";
    int title1Len = title1.length(), title2Len = title2.length(), title3Len = title3.length()
                    , title4Len = title4.length();
    int row2Wide = title2Len + 2, row3Wide = title3Len + 2, row4Wide = title4Len + 2;;

    string splitSign(title1Len + title2Len + title3Len + 2 + title4Len + 2, '-');
    cout << splitSign << endl;

    cout << title1 << setw(row2Wide) << title2 << setw(row3Wide) << title3 << setw(row4Wide) << title4
         << endl;
    cout << string(title1Len, '-') << setw(row2Wide) << string(title2Len, '-')
         << setw(row3Wide) << string(title3Len, '-') << setw(row4Wide) << string(title4Len, '-') << endl;

    for (int i = 0; i < config.chefNumber; i++)
    {
        cout << left << setw(title1Len+2) << i;
        if (servers[i].status)
        {
            cout.width(row2Wide);
            cout << servers[i].order.getID();
            cout.width(row3Wide);
            cout << servers[i].order.getCustomerName();
            if (i == 0 && !waitLine.empty())
            {
                cout << setw(row4Wide);
                Queue<Order> temp = waitLine;
                while (temp.size() != 0)
                {
                    cout << temp.front().getID();
                    temp.pop();
                }
            }
        }

        cout << endl << endl;
    }

}

void outputServiceEndingTime(const PriorityQueue<ServiceEvent>& eventQueue)
{
    cout << "chef   | time for end-of-service" << endl;
    cout << "------ + -----------------------" << endl;
    for (PriorityQueue<ServiceEvent> temp = eventQueue; !temp.empty(); temp.pop())
    {
        cout.width(7);
        cout << temp.top().serverNum << setw(4) << "|";
        cout.width(6);
        cout << temp.top().serviceEndTime << endl;
    }

    if (!eventQueue.empty())
        cout << endl << "Next end-of-service event at "
             << eventQueue.top().serviceEndTime << ". " << endl << endl;
    else
        cout << endl << "No scheduled end-of-service events at this time" << endl << endl;
}



//*****************
//Function name: pauseForUserEnter
//Purpose: pause the program and wait for user enter
//Returns: M - make a order. I - ignore
//Return type: void
//*****************
string pauseForUserEnter()
{
    string input;
    while (true)
    {
        cout << "Press M to make a order. Press I to ignore ...";
        getline(cin,input);
        if (input == "M" || input == "m" || input == "I" || input == "i")
            break;
        else
            cout << "Wrong input, please type M or I" << endl;
    }

    return input;
}



int askMode() //Ask for Customer or Manager
{
    string buf = "";
    int buffer = 0, returnValue = 0;
    bool valid = false;

    while (valid == false)
    {
        cout << endl;
        cout << "Customer or manager? [1 = Customer, 2 = Manager]" << endl;
        cin >> buf;
        buffer = atoi(buf.c_str());

        switch (buffer)
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
