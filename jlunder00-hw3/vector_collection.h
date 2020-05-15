//----------------------------------------------------------------------
// Author: Jason Lunder
// Course: CPSC 223, Spring 2020
// Assign: 3
// File:   vector_collection.h
//
// Description :Implementation of the template vector_collection
// This template uses a vector of pairs which are of generalized types
// K and V, using type templates. This means that the user can create
// vectors of key value pairs of any combination of types accepted by 
// std:pair<K,V>.
//----------------------------------------------------------------------

#ifndef VECTOR_COLLECTION_H
#define VECTOR_COLLECTION_H

#include <vector>
#include <algorithm>            
#include "collection.h"


template<typename K, typename V>
class VectorCollection : public Collection<K,V>
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
  std::vector<std::pair<K,V>> kv_list;
};


// add a new key-value pair into the collection 
template <typename K, typename V>
void VectorCollection<K,V>::add(const K& a_key, const V& a_val)
{
  kv_list.push_back(std::pair<K, V>(a_key, a_val));
}

// remove a key-value pair from the collection
template <typename K, typename V>
void VectorCollection<K,V>::remove(const K& a_key)
{
  //Using an iterator here means there is only one loop call, whereas
  //using kv_list.size() and a traditional for loop would require a
  //loop call in the defentition of size(), even if vector_collection.h
  //size() uses a call to vector.size(), the implementation of that would
  //have to use a loop.
  for(typename std::vector<std::pair<K,V>>::iterator it = kv_list.begin(); it < kv_list.end(); ++it)
  {
    if(it->first == a_key)
    {
      //swapping the found item with the back item and popping the
      //last item does not mantain order but increases efficiency
      //to mantain order, kv_list.erase() would need to be used, but
      //the implementation of erase is less efficient.
      std::swap(*it, kv_list.back());
      kv_list.pop_back();
      return;
    }
  }
}

// find and return the value associated with the key
template <typename K, typename V>
bool VectorCollection<K,V>::find(const K& search_key, V& the_val) const
{
  for(std::pair<K,V> p : kv_list)
  {
    if(p.first == search_key)
    {
      the_val = p.second;
      return true;
    }
  }
  return false;
}

// find and return the values with keys >= to k1 and <= to k2 
template <typename K, typename V>
void VectorCollection<K,V>::find(const K& k1, const K& k2, std::vector<V>& vals) const
{
  for(std::pair<K,V> p : kv_list)
  {
    if(p.first >= k1 && p.first <= k2)
      vals.push_back(p.second);
  }
}
  
// return all of the keys in the collection 
template <typename K, typename V>
void VectorCollection<K,V>::keys(std::vector<K>& all_keys) const
{
  for(std::pair<K,V> p : kv_list)
    all_keys.push_back(p.first);
}

// return all of the keys in ascending (sorted) order
template <typename K, typename V>
void VectorCollection<K,V>::sort(std::vector<K>& all_keys_sorted) const
{
  keys(all_keys_sorted);
  std::sort(all_keys_sorted.begin(), all_keys_sorted.end());
}

// return the number of key-value pairs in the collection
template <typename K, typename V>
int VectorCollection<K,V>::size() const
{
  int size = 0;
  for(std::pair<K,V> p : kv_list)
    ++size;
  return size;
}


#endif
