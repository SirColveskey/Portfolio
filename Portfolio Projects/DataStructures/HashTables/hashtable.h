// Written by: Benjamin Cooper - 11/30/2015

#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <vector>
#include <iostream>
//#include <stdio>
#include <list>
#include <fstream>
#include <algorithm>
#include <string>
#include <functional>
#include <memory>

//using namespace cop4530;
using namespace std;
// max_prime is used by the helpful functions provided
// to you.
static const unsigned int max_prime = 1301081;
// the default_capacity is used if the initial capacity 
// of the underlying vector of the hash table is zero. 
static const unsigned int default_capacity = 11;
namespace cop4530{
template <typename K, typename V>
class HashTable
{
public:
  HashTable(size_t size = 101);
  ~HashTable();
  bool contains(const K & k);
  bool match(const std::pair<K,V> &kv) const;
  bool insert(const std::pair<K,V> & kv);
  bool insert(std::pair<K,V> && kv);
  bool remove(const K & k);
  void clear();
  bool load(const char *filename);
  void dump();
  bool write_to_file(const char *filename);
  int GetSize() const;

private:
  void makeEmpty();
  void rehash();
  size_t myhash(const K &k) const;
  unsigned long prime_below(unsigned long);
  void setPrimes(vector<unsigned long>&);

  vector<list<pair<K,V>>> data;
  int theSize;
};

#include "hashtable.hpp"
};
#endif
