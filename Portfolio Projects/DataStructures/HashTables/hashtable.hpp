// Written by: Benjamin Cooper - 11/30/2015

// returns largest prime number <= n or zero if input is too large
// This is likely to be more efficient than prime_above(), because
// it only needs a vector of size n
template <typename K, typename V>
HashTable<K, V>::HashTable(size_t size)
{
  if(prime_below(size)==0)
  {
  cout << "101";
  data.resize(101);
  }
  else
  {
  data.resize(prime_below(size));
  cout << prime_below(size);
  }
  theSize = 0;
};

template <typename K, typename V>
HashTable<K, V>::~HashTable()
{
  clear();
  theSize = 0;
};

template <typename K, typename V>
bool HashTable<K, V>::contains(const K & k)
{
  if(data[myhash(k)].empty()) //this may cause problems with soft delete
  	return false;
  const list<pair<K,V>> & whichList = data[myhash(k)];
  auto itr = whichList.begin();
  while(itr != whichList.end())
  {
  	if(itr->first == k)
		return true;
	itr++;
  }
  return false; //needs to look into the list to see if k specifically exists
};

template <typename K, typename V>
bool HashTable<K, V>::match(const std::pair<K, V> &kv) const
{
  K val = kv.first;
  int i = myhash(val);
  const list<pair<K,V>> & whichList = data[i];

return find( whichList.begin(), whichList.end(), kv ) != whichList.end();
};

template <typename K, typename V>
bool HashTable<K, V>::insert(const std::pair<K, V> &kv)
{
  if(match(kv))
  	return false;
  data[myhash(kv.first)].push_back(kv);
  theSize++;
  if(theSize >= data.size())
   rehash();
  return true;
};

template <typename K, typename V>
bool HashTable<K, V>::insert(std::pair<K,V> && kv)
{//evaluate new algorithm for move
  if(match(kv))
  	return false;
while(myhash(kv.first)<data.size())
{
	rehash();
};
  data[myhash(kv.first)].push_back(kv);
  theSize++;
  return true;
};

template <typename K, typename V>
bool HashTable<K, V>::remove(const K & k)
{
  if(data[myhash(k)].empty())
  	return false;
  auto & whichList = data[myhash(k)];
  auto itr = whichList.begin();
  while(itr != whichList.end())
  {
	if(itr->first == k)
	{
	  whichList.erase(itr);
	  --theSize;
	  return true;
	}
  }
  return false;
};

template <typename K, typename V>
void HashTable<K, V>::clear()
{
  makeEmpty();
};

template <typename K, typename V>
bool HashTable<K,V>::load(const char *filename)
{
  clear();
  data.resize(101);
  theSize = 101;
  int counter=0;
  ifstream file;
  file.open(filename);
  pair<K,V> kv;
  while(file >> kv.first)
  {
    counter++;
    file >> kv.second;
    insert(kv);
    if(counter >= data.size())
    	rehash();
  }
  file.close();
};//possible conflict with nonstring?

template <typename K, typename V>
void HashTable<K,V>::dump()
{
  for(int i=0; i<data.size(); i++)
  {
  	auto itr = data[i].begin();
	cout << "v[" << i << "]: ";
	if(!data[i].empty())
	{
	while( itr != data[i].end() )
	{
		cout << itr->first << " " << itr->second;
		itr++;
		if(itr != data[i].end())
		  cout << " ; ";
	};
	};
	cout << endl;
  }
};

template <typename K, typename V>
bool HashTable<K,V>::write_to_file(const char *filename)
{
  ofstream file;
  file.open(filename);
  for(int i=0; i<data.size(); i++)
  {
    if(!data[i].empty())
    {
    for( auto itr = data[i].begin(); itr != data[i].end(); itr++ )
    {
      file << itr->first << " " << itr->second << endl;
    }
    }
  }  
  //file << "this is a test!";
  file.close();
};//wip

template <typename K, typename V>
void HashTable<K,V>::makeEmpty()
{
  data.clear();
  theSize=0;
};

template <typename K, typename V>
void HashTable<K,V>::rehash()
{
  vector<list<pair<K,V>>> oldData = data; 
  
  data.resize( prime_below( 2 * data.size() ) );
  for(int j = 0; j < data.size(); j++)
  	data[ j ].clear();
  
  theSize = 0;
  for(int i = 0; i < oldData.size(); i++)
  {
    auto itr = oldData[ i ].begin();
    while( itr != oldData[ i ].end() )
    	insert( *itr++ );
  }
};

template <typename K, typename V>
size_t HashTable<K,V>::myhash(const K &k) const //added const****
{
//if(data.size() == 0)
  //return 0;
  hash<K> has;
  int hashVal = has( k );
  hashVal %= data.size();
  if( hashVal < 0 )
  	hashVal += data.size();

  return hashVal;
};

template <typename K, typename V>
unsigned long HashTable<K, V>::prime_below (unsigned long n)
{
  if (n > max_prime)
    {
      std::cerr << "** input too large for prime_below()\n";
      return 0;
    }
  if (n == max_prime)
    {
      return max_prime;
    }
  if (n <= 1)
    {
		std::cerr << "** input too small \n";
      return 0;
    }

  // now: 2 <= n < max_prime
  std::vector <unsigned long> v (n+1);
  setPrimes(v);
  while (n > 2)
    {
      if (v[n] == 1)
	return n;
      --n;
    }

  return 2;
}

//Sets all prime number indexes to 1. Called by method prime_below(n) 
template <typename K, typename V>
void HashTable<K, V>::setPrimes(std::vector<unsigned long>& vprimes)
{
  int i = 0;
  int j = 0;

  vprimes[0] = 0;
  vprimes[1] = 0;
  int n = vprimes.capacity();

  for (i = 2; i < n; ++i)
    vprimes[i] = 1;

  for( i = 2; i*i < n; ++i)
    {
      if (vprimes[i] == 1)
        for(j = i + i ; j < n; j += i)
          vprimes[j] = 0;
    }
}

template <typename K, typename V>
int HashTable<K, V>::GetSize() const
{
  return theSize;
}
