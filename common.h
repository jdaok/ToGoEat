#ifndef common_h
#define common_h
struct MenuItem
{
    string name;
    int idNumber;
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
  //Clear Menu
  menu.clear()
  
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
      item tempItem;
      tempItem.name = name;
      tempItem.idNumber = itemID;
      itemID++;
      tempItem.price = stod(price);
      tempItem.avgPrepTime = stoi(avgPrepTime);
      menu.push_back(tempItem);
  }
  return true;
}

void showMenu(const vector<MenuItem>& menu)
{
  bool next = loadMenu(menu);
  
  if(next)
  {
    cout << "Name:\t" << "ID:\t" << "Price:\t" << endl;
    for(auto& it: menu)
    {
      cout << it.name << "\t" << it.idNumber << "\t" << it.price << endl;
    }
  }
}

#endif /* common */
