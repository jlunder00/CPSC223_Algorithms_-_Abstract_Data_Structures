
//----------------------------------------------------------------------
// Author: ...
// Course: CPSC 223, Spring 2020
// Assign: 8
// File:   hash_table_collection.h
// A hash table implementation of the collection class
// Stores kev value pairs (K,V) in a table using a hash function to find
// Indexes for searching, storing and removing. Uses a linked list
// at every index to account for collisions.
//----------------------------------------------------------------------

 
#ifndef HASH_TABLE_COLLECTION_H
#define HASH_TABLE_COLLECTION_H

#include <vector>
#include <algorithm>
#include <functional>
#include "collection.h"


template<typename K, typename V>
class HashTableCollection : public Collection<K,V>
{
public:

  // create an empty hash table with default number of buckets
  HashTableCollection();

  // hash table copy constructor
  HashTableCollection (const HashTableCollection <K,V>& rhs);

  // hash table assignment operator
  HashTableCollection <K,V>& operator=(const HashTableCollection <K ,V >& rhs);

  // delete a linked list
  ~HashTableCollection();
  
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

  // helper to empty entire hash table
  void make_empty()
  {
    int i = 0;
    while(collection_size>0)
    {
      Node* tmp = hash_table[i];
      Node* head = hash_table[i];
      while(tmp)
      {	
        tmp = head->next;
        delete head;
        head = tmp;
        --collection_size;
      }
      ++i;
    }
  }

  // helper to resize and rehash the hash table
  void resize_and_rehash()
  {


    int newTable_capacity = table_capacity*2;
    Node** tempTable = new Node*[newTable_capacity];
    
    std::hash<K> hash_function;
    for(int i = 0; i < newTable_capacity; ++i)
      tempTable[i] = nullptr;
    for(int i = 0; i < table_capacity; ++i)
    {
      Node* oldTmp;
      while(hash_table[i])
      {
        oldTmp = hash_table[i];
	K key = oldTmp->key;
	V val = oldTmp->value;
	size_t tableValue = hash_function(key);
	size_t index = tableValue % newTable_capacity;
	Node* tmp = new Node;
	tmp->next = tempTable[index];
	tempTable[index] = tmp;
	tmp->key = key;
	tmp->value = val;
        hash_table[i] = oldTmp->next;
	delete oldTmp;
      }
    }
    table_capacity = newTable_capacity;
    delete hash_table;
    hash_table = tempTable;


  }
  
  // linked list node structure
  struct Node {
    K key;
    V value;
    Node* next;
  };
  
  // number of k-v pairs in the collection
  int collection_size;

  // number of hash table buckets (default is 16)
  int table_capacity;

  // hash table array load factor (set at 75% for resizing)
  double load_factor_threshold;

  // hash table array
  Node** hash_table;
   
};


// TODO: implement the above functions here ...

// create an empty hash table with default number of buckets
template<typename K, typename V>
HashTableCollection<K,V>::HashTableCollection()
{
  collection_size = 0;
  table_capacity = 16;
  load_factor_threshold = 0.75;
  hash_table = new Node*[table_capacity];
  for(int i = 0; i < table_capacity; ++i)
    hash_table[i] = nullptr;
}

// hash table copy constructor
template<typename K, typename V>
HashTableCollection<K,V>::HashTableCollection (const HashTableCollection <K,V>& rhs)
{
  collection_size = rhs.collection_size;
  table_capacity = rhs.table_capacity;
  load_factor_threshold = rhs.load_factor_threshold;
  hash_table = new Node*[table_capacity];
  for(int i = 0; i < table_capacity; ++i)
    hash_table[i] = nullptr;
  for(int i = 0; i < table_capacity; ++i)
  {
    Node* rhsTmp = rhs.hash_table[i];
    Node* lhsTmp = hash_table[i];
    if(rhsTmp)
    {
      Node* tmp = new Node;
      tmp->key = rhsTmp->key;
      tmp->value = rhsTmp->value;
      tmp->next = nullptr;
      hash_table[i] = tmp;
      lhsTmp = tmp;
      rhsTmp = rhsTmp->next;
    }
    while(rhsTmp)
    {
      Node* tmp = new Node;
      tmp->key = rhsTmp->key;
      tmp->value = rhsTmp->value;
      tmp->next = nullptr;
      lhsTmp->next = tmp;
      lhsTmp = lhsTmp->next;
      rhsTmp = rhsTmp->next;
    }
  }
}

// hash table assignment operator
template<typename K, typename V>
HashTableCollection <K,V>& HashTableCollection<K,V>::operator=(const HashTableCollection <K ,V >& rhs)
{
  if(this == &rhs)
    return *this;
  HashTableCollection<K,V> temp(rhs);
  std::swap(hash_table, temp.hash_table);
  std::swap(load_factor_threshold, temp.load_factor_threshold);
  std::swap(table_capacity, temp.table_capacity);
  std::swap(collection_size, temp.collection_size);
  return *this;
}

// delete a linked list
template<typename K, typename V>
HashTableCollection<K,V>::~HashTableCollection()
{
  if(hash_table)
  {
    make_empty();
    delete hash_table;
  }
}
  
// add a new key-value pair into the collection 
template<typename K, typename V>
void HashTableCollection<K,V>::add(const K& a_key, const V& a_val)
{
  if(((double)collection_size)/((double)table_capacity) >= load_factor_threshold)
    resize_and_rehash();

  std::hash<K> hash_function;
  size_t value = hash_function(a_key);
  size_t index = value % table_capacity;

  Node* tmp = new Node;
  tmp->next = hash_table[index];
  hash_table[index] = tmp;
  tmp->key = a_key;
  tmp->value = a_val;
  ++collection_size;
}

// remove a key-value pair from the collectiona
template<typename K, typename V>
void HashTableCollection<K,V>::remove(const K& a_key)
{
  std::hash<K> hash_function;
  size_t value = hash_function(a_key);
  size_t index = value % table_capacity;
  Node* tmp = hash_table[index];
  Node* prev = tmp;
  while(tmp && tmp->key != a_key)
  {
    prev = tmp;
    tmp = tmp->next;
  }
  if(tmp)
  {
    --collection_size;
    if(tmp == hash_table[index])
      hash_table[index] = tmp->next;
    else
      prev->next = tmp->next;
    delete tmp;
  }
}

// find and return the value associated with the key
template<typename K, typename V>
bool HashTableCollection<K,V>::find(const K& search_key, V& the_val) const
{
  std::hash<K> hash_function;
  size_t value = hash_function(search_key);
  size_t index = value % table_capacity;
  Node* tmp = hash_table[index];
  while(tmp && tmp->key != search_key)
    tmp = tmp->next;
  if(tmp)
    the_val = tmp->value;
  return tmp;
}

// find and return the values with keys >= to k1 and <= to k2 
template<typename K, typename V>
void HashTableCollection<K,V>::find(const K& k1, const K& k2, std::vector<V>& vals) const
{
  K key;
  Node* tmp;
  for(int i = 0; i < table_capacity; ++i)
  {
    tmp = hash_table[i];
    while(tmp)
    {
      key = tmp->key;
      if(key >= k1 && key <= k2)
        vals.push_back(tmp->value);
      tmp = tmp->next;
    }
  }
}
  
// return all of the keys in the collection 
template<typename K, typename V>
void HashTableCollection<K,V>::keys(std::vector<K>& all_keys) const
{
  for(int i = 0; i < table_capacity; ++i)
  {
    Node* tmp = hash_table[i];
    while(tmp)
    {
      all_keys.push_back(tmp->key);
      tmp = tmp->next;
    }
  }
}

// return all of the keys in ascending (sorted) order
template<typename K, typename V>
void HashTableCollection<K,V>::sort(std::vector<K>& all_keys_sorted) const
{
  keys(all_keys_sorted);
  std::sort(all_keys_sorted.begin(), all_keys_sorted.end());
}

// return the number of key-value pairs in the collection
template<typename K, typename V>
int HashTableCollection<K,V>::size() const
{
/*  for(int i = 0; i < table_capacity; ++i)
  {
    std::cout<<"List "<<i<<" : ";
    Node* tmp = hash_table[i];
    while(tmp)
    {
      std::cout<<tmp->key<<", ";
      tmp = tmp->next;
    }
    std::cout<<std::endl;
  }*/
  return collection_size;
}


#endif
