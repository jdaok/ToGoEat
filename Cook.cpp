//Programmer:Jiefeng Yang
//Programmer's ID:1791121

#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

#include <cmath>
#include <cstdlib>
#include <ctime> // for clock( ), clock_t, time, and CLOCKS_PER_SEC

#include "PriorityQueue.h"
#include "DynamicArray.h"
#include "Queue.h"

struct simulationConfig
{
    int chefNumber; //the number of chefs
    int timeAtNewArrStop; //the clock time at which new arrivals stop, in minutes(> 0, whole number)

    //TODO maybe don't need those
    double aveCustArrivalRate; //the average arrival rate of customers, per minute (greater than 0.0, floating point)
    int maxLenWaitQue; //the maximum length of the wait queue(1 or more, whole number)
    int minSerTimeInterval; //the minimum service time interval, in minutes(1 or more, whole number)
    int maxSerTimeInterval; //the maximum service time interval, in minutes(>= minimum service time interval, whole number)
    
};

//ToDo will change to Order
struct Customer
{
    char id;
    int arrivalTime;
};

struct ServiceEvent
{
    int serverNum;
    int serviceEndTime;
};

struct ServerInfo
{
    Customer customer;  //TODO Order order
    bool status;
};

//for comparing ServiceEvent in PriorityQueue template
bool operator<(const ServiceEvent& a, const ServiceEvent& b)
{
    //swith to lo-to-hi priority 
    return b.serviceEndTime < a.serviceEndTime;
}

const int W1 = 23;   //cout width. W1 for title 
const string CONFIG_FILE_NAME = "simulation.txt";

//void outputProgrammerInfo();
bool loadSimulationConfig(string fileName, simulationConfig& config);
void outputTitle(simulationConfig config);
int getRandomNumberOfArrivals(double);
int getServiceTime(const int, const int);

char genrateCustomerID();
bool shouldEndSimulation(int time, const Queue<Customer>& waitLine, const simulationConfig& config,
    const DynamicArray<ServerInfo>& servers);
void outputServiceEndingTime(const PriorityQueue<ServiceEvent>& eventQueue);
void outputSummary(int time, const Queue<Customer>& waitLine, const simulationConfig& config,
    const DynamicArray<ServerInfo>& servers);


void pauseForUserEnter();


int main()
{
    //for rand() only call once. using static_cast to fix the warning that data type conversion may lose data. 
    srand(static_cast<unsigned int>(time(0))); rand();
    //outputProgrammerInfo();

    simulationConfig config;  //simulation config data
    if (!loadSimulationConfig(CONFIG_FILE_NAME, config))
    {
        cout << "Load the config file Error:" << CONFIG_FILE_NAME <<
            ". Please check and rerun the program" << endl;
        return 1;
    }
    outputTitle(config);

    Queue<Customer> waitLine;   //TODO Queue<Order> waitLine
    PriorityQueue<ServiceEvent> eventQueue;
    DynamicArray<ServerInfo> servers;



    for (int time = 0;; time++)
    {
        //handle all services scheduled
        while (!eventQueue.empty() && eventQueue.top().serviceEndTime == time)
        {
            servers[eventQueue.top().serverNum].status = false;
            eventQueue.pop();
        }
        //handle new arrivals
        //pause for the user to press ENTER
        pauseForUserEnter();
        
        //Todo notice user to chose the food and make order
        /*if (time < config.timeAtNewArrStop)
        {
            int arrivalNum = getRandomNumberOfArrivals(config.aveCustArrivalRate);
            for (int i = 0; i < arrivalNum; i++)
            {
                if (waitLine.size() < config.maxLenWaitQue)
                {
                    Customer temp;
                    temp.arrivalTime = time;
                    temp.id = genrateCustomerID();
                    waitLine.push(temp);
                }
            }
        }*/

        // for idle servers, move customer from wait queue and begin service for each server
        for (int i = 0; i < config.chefNumber; i++)
        {
            if (!servers[i].status && !waitLine.empty())
            {
                //TODO here is the order
                servers[i].customer = waitLine.front();  
                servers[i].status = true;
                waitLine.pop();

                ServiceEvent temp;
                //getServiceTime become the order prepare time 
                temp.serviceEndTime = time + getServiceTime(config.minSerTimeInterval,
                    config.maxSerTimeInterval);
                temp.serverNum = i;
                eventQueue.push(temp);
            }
        }

        outputSummary(time, waitLine, config, servers);
        //TODO maybe don't need this
        outputServiceEndingTime(eventQueue);

        if (shouldEndSimulation(time, waitLine, config, servers))
            break;

    }

    //TODO output the total numer of the order and total amount of money the restaurant made.

    cout << endl << "Done!" << endl;

    return 0;
}

//*****************
//Function name: getRandomNumberOfArrivals
//Purpose: get Random Number Of Arrivals
//averageArrivalRate: average Arrival Rate
//Returns: Random Number Of Arrivals
//Return type: int
//*****************
int getRandomNumberOfArrivals(double averageArrivalRate)
{
    int arrivals = 0;
    double probOfnArrivals = exp(-averageArrivalRate);
    for (double randomValue = (double)rand() / RAND_MAX;
        (randomValue -= probOfnArrivals) > 0.0;
        probOfnArrivals *= averageArrivalRate / static_cast<double>(++arrivals));
    return arrivals;
}



int getServiceTime(const int min, const int max)
{
    return min + (rand() % max);
}


/*void outputProgrammerInfo()
{
    cout << "Programmer: Jiefeng Yang\n";
    cout << "Programmer's ID: 1791121\n";
    cout << "File: " << __FILE__ << endl;
    cout << endl;
}*/

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

    ifstream fin;
    fin.open(fileName);
    if (fin.good())
    {
        string line;
        getline(fin, line);
        config.chefNumber = atoi(line.c_str());
        if (config.chefNumber < 1)
        {
            cout << "Config Error:the number of servers need to be 1 or more." << endl;
            ret = false;
        }

        getline(fin, line);
        config.aveCustArrivalRate = atof(line.c_str());
        if (config.aveCustArrivalRate < 0.0)
        {
            cout << "Config Error:the average arrival rate of customers/per minute need to greater than 0.0."
                << endl;
            ret = false;
        }

        getline(fin, line);
        config.maxLenWaitQue = atoi(line.c_str());
        if (config.maxLenWaitQue < 1)
        {
            cout << "Config Error:the maximum length of the wait queue need to be 1 or more." << endl;
            ret = false;
        }

        getline(fin, line);
        config.minSerTimeInterval = atoi(line.c_str());
        if (config.minSerTimeInterval < 1)
        {
            cout << "Config Error:the minimum service time interval in minutes need to be 1 or more, whole number." << endl;
            ret = false;
        }

        getline(fin, line);
        config.maxSerTimeInterval = atoi(line.c_str());
        if (config.maxSerTimeInterval < config.minSerTimeInterval)
        {
            cout << "Config Error:the maximum service time interval need to >= minimum service time interval" << endl;
            ret = false;
        }

        getline(fin, line);
        config.timeAtNewArrStop = atoi(line.c_str());
        if (config.timeAtNewArrStop < 0)
        {
            cout << "Config Error:the clock time at which new arrivals stop, in minutes needs to > 0" << endl;
            ret = false;
        }

        fin.close(); // done with the file
        return ret;
    }
    else
    {
        cout << "Error, can not read the config file:" << fileName << endl;
        return false;
    }
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
    cout << "********Welcome to the ToGoEat********" << endl;
    cout << setw(W1) << left << "number of chef:" << config.chefNumber << endl;
    cout << setw(W1) << left << "customer arrival rate:" << config.aveCustArrivalRate
        << right << setw(16) << "per minute, for" << setw(3) << config.timeAtNewArrStop << setw(8) << "minutes" << endl;
    cout << setw(W1) << left << "maximum queue length:" << config.maxLenWaitQue << endl;
    cout << setw(W1) << left << "minimum service time:" << config.minSerTimeInterval << right << setw(8)
        << "minutes" << endl;
    cout << setw(W1) << left << "maximum service time:" << config.maxSerTimeInterval << right << setw(8)
        << "minutes" << endl << endl;
}



//TODO don't need this. Just get the cusomter name from the order
//*****************
//Function name: genrateCustomerID
//Purpose: genrate Customer ID
//Returns: Customer ID
//Return type: char
//*****************
char genrateCustomerID()
{
    static int number = 0;
    int index = number % 26; //reuse the 26 letter A-Z

    char ID = 'A' + index;
    number++;

    return ID;
}



bool shouldEndSimulation(int time, const Queue<Customer>& waitLine, const simulationConfig& config,
    const DynamicArray<ServerInfo>& servers)
{
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

void outputSummary(int time, const Queue<Customer>& waitLine, const simulationConfig& config,
    const DynamicArray<ServerInfo>& servers)
{
    cout << left << setw(6) << "Time:" << time << right << endl;
    string title1 = "chef  ", title2 = "now serving", title3 = "wait queue";
    int title1Len = title1.length(), title2Len = title2.length(), title3Len = title3.length();
    int row2Wide = title2Len + 2, row3Wide = title3Len + 2;

    string splitSign(title1Len + title2Len + title3Len + 2, '-');
    cout << splitSign << endl;

    cout << title1 << setw(row2Wide) << title2 << setw(row3Wide) << title3 << endl;
    cout << string(title1Len, '-') << setw(row2Wide) << string(title2Len, '-')
        << setw(row3Wide) << string(title3Len, '-') << endl;

    for (int i = 0; i < config.chefNumber; i++)
    {
        cout << setw(3) << i;
        if (servers[i].status)
        {
            cout.width(10);
            cout << servers[i].customer.id;
            if (i == 0 && !waitLine.empty())
            {
                cout << setw(9);
                Queue<Customer> temp = waitLine;
                while (temp.size() != 0)
                {
                    cout << temp.front().id;
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
        cout.width(4);
        cout << temp.top().serverNum << setw(4) << "|";
        cout.width(6);
        cout << temp.top().serviceEndTime << endl;
    }

    if (!eventQueue.empty())
        cout << endl << "Next end-of-service event in "
        << eventQueue.top().serviceEndTime << " minutes" << endl << endl;
    else
        cout << endl << "No scheduled end-of-service events at this time" << endl << endl;
}



//*****************
//Function name: pauseForUserEnter
//Purpose: pause the program and wait for user enter
//Returns: None
//Return type: void
//*****************
void pauseForUserEnter()
{
    cout << "Press ENTER to make a order..." << endl;
    while (getchar() != '\n');
    cout << endl;
}




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


