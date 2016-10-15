// Written by: Benjamin Cooper - 11/30/2015

#include "passserver.h"

PassServer::PassServer(size_t size):data(size)
{
  
};

PassServer::~PassServer()
{
  
};

bool PassServer::load(const char *filename)
{
  //copy old load but add encrypt
   {
      data.clear();
      int counter=0;
      ifstream file;
      file.open(filename);
      pair<string,string> kv;
      while(file >> kv.first)
      {
       file >> kv.second;
       kv.second = encrypt(kv.second);
       if(data.insert(kv))
       {
        // cout << kv.first << " inserted."
       }
       else
       {
         cout << "Error: Duplicate key '" << kv.first << "', duplicate key ignored" << endl;
       }
     }
     file.close();
  };
};

bool PassServer::addUser(std::pair<string, string> &kv)
{
  pair<string, string> newkv(kv.first,encrypt(kv.second));
  return data.insert(newkv);
};

bool PassServer::addUser(std::pair<string, string> &&kv)
{
  pair<string, string> newkv(kv.first,encrypt(kv.second));
  return data.insert(newkv);
};

bool PassServer::removeUser(const string & k)
{
  return data.remove(k);
};

bool PassServer::changePassword(const pair<string,string> &p, const string & newpassword)
{
  pair<string,string> newp(p.first,encrypt(p.second));
  if(p.second == newpassword)
    return false;
  if(data.match(newp))
  {
  	data.remove(newp.first);
	newp.second = newpassword;
	addUser(newp);
	return true;
  };
  return false;
};

bool PassServer::find(const string & user)
{
  return data.contains(user);
};

void PassServer::dump()
{
  data.dump();
};

size_t PassServer::size()
{
  return data.GetSize();
};

bool PassServer::write_to_file(const char *filename)
{
  return data.write_to_file(filename);
};

string PassServer::encrypt(const string & str)
{
  char salt[] = "$1$########";
  char crypto[35];
  strcpy ( crypto, crypt(str.c_str(), salt));
  memmove(crypto+0,crypto+12,22);
  crypto[22]=0;
  return crypto;
};
