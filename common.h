#ifndef common_h
#define common_h

struct MenuItem
{
    string name;
    int idNumber;
    //int type;        // 0 = food. 1 = drink. food takes longer
    double price;        // ex. 1.50$
    int avgPrepTime;  // ex. 15 minutes
    bool finished = false;

    MenuItem& operator=(const MenuItem& original) //assignment operator
    {
        if (this != &original) // of it's not a self copy...
        {
            name = original.name;
            idNumber = original.idNumber;
            price = original.price;
            avgPrepTime = original.avgPrepTime;
            finished = original.finished;
        }

        return *this; // return a self reference
    };
};

vector<MenuItem> MENU;

//Menu Functions
//todo
bool loadMenu(vector<MenuItem>& menu)
{
  //Clear Menu
  menu.clear();
  
  ifstream fin;
  fin.open("menu.txt");
  if(!fin.good())
  {
    cout << "Menu does not exist." << endl;
    return false;
  }
    
  int itemID = 0;
  char* token;
  char buf[1000];
  const char* const tab = "\t";
  while(fin.good())
  {
      string line;
      getline(fin, line);
      strcpy(buf, line.c_str());
      if (buf[0] == 0) continue; // skip blank lines
      //parse the line
      const string name(token = strtok(buf, tab));
      if (name.find('-') != string::npos) continue; // skip first line which has a dash in it
      const string price((token = strtok(0, tab)) ? token : "");
      const string avgPrepTime((token = strtok(0, tab)) ? token : "");
      const string maxAmt((token = strtok(0, tab)) ? token : "");
      MenuItem tempItem;
      tempItem.name = name;
      tempItem.idNumber = itemID;
      itemID++;
      tempItem.price = stod(price);
      tempItem.avgPrepTime = stoi(avgPrepTime);
      menu.push_back(tempItem);
  }
  return true;
}

void showMenu(const vector<MenuItem> &menu)
{
    const int width2 = 12;

    cout << right << setw(width2) << "ID# " <<
        setw(width2) << "name" <<
        setw(width2) << "price" << endl;

    cout << right << setw(width2) << "----" <<
        setw(width2) << "----" <<
        setw(width2) << "-----" << endl;

    for (int i = 0; i < menu.size(); i++)
    {
        cout << right << setw(width2) << menu[i].idNumber <<
            setw(width2) << menu[i].name <<
            setw(width2) << menu[i].price << endl;
    }
}

#endif /* common */
