// Written by: Benjamin Cooper - 11/30/2015

#include <iostream>
#include <string>
#include "passserver.h"

//using namespace cop4530;
using namespace std;

void Menu();
void Evaluate(string in, PassServer & serv);
int main()
{ int get;
  string input;
  cout << "Enter preferred hash table capacity: ";
  cin >> get;
  PassServer Server(get);
  Menu();
  cin >> input;
  while(input != "x")
  {
    Evaluate(input, Server);
    Menu();
    cin >> input;
  }
};

void Menu()
{
  cout << "\n\n";
  cout << "l - Load From File" << endl;
  cout << "a - Add User" << endl;
  cout << "r - Remove User" << endl;
  cout << "c - Change User Password" << endl;
  cout << "f - Find User" << endl;
  cout << "d - Dump HashTable" << endl;
  cout << "s - HashTable Size" << endl;
  cout << "w - Write to Password File" << endl;
  cout << "x - Exit program" << endl;
  cout << "\nEnter choice : ";
};

void Evaluate(string in, PassServer & serv)
{
  string input;
  pair<string,string> check;
  bool flag=false;
  if(in == "l")
  {
    cout << "Enter password file name to load from: ";
    cin >> input;
    if(serv.load(input.c_str()))
    {
      cout << endl << "Users loaded from " << input << ".\n";
    }
    else
    {
      cout << "Error: Cannot open file " << input << ".\n";
    }
  }
  else if(in == "a")
  {
   cout << "Enter username: ";
   cin >> check.first;
   cout << "Enter password: ";
   cin >> check.second;
   if(serv.addUser(check))
   {
     cout << endl << "User " << check.first << " added.";
   }
   else
   {
     cout << endl << "*****Error: User already exists. Could not add user." << endl;
   }
  }
  else if(in == "r")
  {
   cout << "Enter username: ";
   cin >> input;
   serv.removeUser(input);
  }
  else if(in == "c")
  {
   cout << "Enter username: ";
   cin >> check.first;
   cout << "Enter password: ";
   cin >> check.second;
   cout << endl;
   cout << "Enter new password: ";
   cin >> input;
   if(serv.changePassword(check, input))
    cout << endl << "Password changed for user " << check.first << endl;
   else
    cout << endl << "*****Error: Could not change user password" << endl;
  }
  else if(in == "f")
  {
   cout << "Enter username: ";
   cin >> input;
   if(serv.find(input))
    cout << "User '" << input << "' found." << endl;
   else
    cout << "User '" << input << "' not found." << endl;
  }
  else if(in == "d")
  {
   serv.dump();
   cout << endl;
  }
  else if(in == "s")
  {
   cout << "Size of hashtable: ";
   cout << serv.size() << endl;
  }
  else if(in == "w")
  {
   cout << "Enter password file name to write to: ";
   cin >> input;
   if(serv.write_to_file(input.c_str()))
   {}
   else
     cout << "Error: Unable to write to file." << endl;
  }
  else if(in == "x")
  {
    
  }
  else
  {
    cout << "*****Error: Invalid entry.  Try again. \n";
  };
};
