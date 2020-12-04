#ifndef common_h
#define common_h

struct MenuItem
{
    string name;
    int type;        // 0 = food. 1 = drink. food takes longer
    double price;        // ex. 1.50$
    int avgPrepTime;  // ex. 15 minutes
    bool finished = false;
};

vector<MenuItem> menu;



#endif /* common */