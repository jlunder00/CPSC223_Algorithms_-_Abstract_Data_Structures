//----------------------------------------------------------------------
// Author: Jason Lunder
// Course: CPSC 223, Spring 2020
// Assign: 5
// File:   binsearch_collection.h
//
// implementation of binary search vector collection
//----------------------------------------------------------------------

#ifndef BINSEARCH_COLLECTION_H
#define BINSEARCH_COLLECTION_H

#include <vector>
#include <algorithm>            
#include "collection.h"


template<typename K, typename V>
class BinSearchCollection : public Collection<K,V>
{
public:

  // add a new key-value pair into the collection 
  void add(const K& a_key, const V& a_val);

  // remove a key-value pair from the collectiona
  void remove(const K& a_key);

  // find and return the value associated with the key
  bool find(const K& search_key, V& the_val) const;

  // find and return the values with keys >= to k1 and <= to k2 
  void find(const K& k1, const K& k2, std::vector<V>& vals) const;
  
  // return all of the keys in the collection 
  void keys(std::vector<K>& all_keys) const;

  // return all of the keys in ascending (sorted) order
  void sort(std::vector<K>& all_keys_sorted) const;

  // return the number of key-value pairs in the collection
  int size() const;

private:

  // helper function for binary search
  bool binsearch(const K& key, int& index) const;

  // vector storage
  std::vector<std::pair<K,V>> kv_list;

};


// TODO: Implement functions here ...
// Returns true and the index if the given key is in the collection
// Returns false and the index of where the key-value pair should be
// in order to maintain sorted order
template<typename K, typename V>
bool BinSearchCollection<K,V>::binsearch(const K& key, int& index) const
{
  int size = kv_list.size();
  if(size == 0)
  {
    index = 0;
    return false;
  }
  int bottom = 0;
  int top = size-1;
  int mid;
  K theKey;
  while(top >= bottom)
  {
    mid = (top+bottom)/2;
    theKey = kv_list[mid].first;
    if(theKey == key)
    {
      index = mid;
      return true;
    }else if(theKey < key)
      bottom = mid+1;
    else
      top = mid-1;
  }
  index = (theKey < key) ? mid+1 : mid;
  return false;
}


// return the number of key-value pairs in the collection
template<typename K, typename V>
int BinSearchCollection<K,V>::size() const
{
  return kv_list.size();
}

// add a new key-value pair into the collection 
template<typename K, typename V>
void BinSearchCollection<K,V>::add(const K& a_key, const V& a_val)
{
  std::pair<K,V> p(a_key, a_val);
  int index;
  binsearch(a_key, index);
  kv_list.insert(kv_list.begin()+index, p);
}

// find and return the value associated with the key
template<typename K, typename V>
void BinSearchCollection<K,V>::remove(const K& a_key)
{
  int index;
  if(binsearch(a_key, index))
    kv_list.erase(kv_list.begin()+index);
}

// remove a key-value pair from the collectiona
template<typename K, typename V>
bool BinSearchCollection<K,V>::find(const K& search_key, V& the_val) const
{
  int index;
  if(binsearch(search_key, index))
  {
    the_val = kv_list[index].second;
    return true;
  }
  return false;
}


// find and return the values with keys >= to k1 and <= to k2 
template<typename K, typename V>
void BinSearchCollection<K,V>::find(const K& k1, const K& k2, std::vector<V>& vals) const
{
  int cur;
  bool exists = binsearch(k1, cur);
  while(kv_list[cur].first <= k2)
  {
    vals.push_back(kv_list[cur].second);
    ++cur;
  }
}

// return all of the keys in the collection 
template<typename K, typename V>
void BinSearchCollection<K,V>::keys(std::vector<K>& all_keys) const
{
  for(int i = 0; i < kv_list.size(); ++i)
    all_keys.push_back(kv_list[i].first);
}

// return all of the keys in ascending (sorted) order
template<typename K, typename V>
void BinSearchCollection<K,V>::sort(std::vector<K>& all_keys_sorted) const
{
  //already sorted through binary search adding
  keys(all_keys_sorted);
}




#endif
