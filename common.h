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

vector<MenuItem> MENU;

//Menu Functions
//todo
bool loadMenu(vector<MenuItem>& menu)
{

    //if suscces
    return true;

    //todo
    //else
    //return false;
}
void showMenu(const vector<MenuItem>& menu)
{

}



#endif /* common */