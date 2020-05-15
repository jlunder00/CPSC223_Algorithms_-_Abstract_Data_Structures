//----------------------------------------------------------------------
// Author:
// Course: CPSC 223, Spring 2020
// Assign: 4
// File:   linked_list_collection.h
//
// TODO: Description here
//----------------------------------------------------------------------

#ifndef LINKED_LIST_COLLECTION_H
#define LINKED_LIST_COLLECTION_H

#include <vector>
#include <algorithm>            
#include "collection.h"


template<typename K, typename V>
class LinkedListCollection : public Collection<K,V>
{
public:

  // constructor to initialize empty linked list
  LinkedListCollection();

  // copy constructor
  LinkedListCollection(const LinkedListCollection<K,V>& rhs);

  // assignment operator
  LinkedListCollection<K,V>& operator=(const LinkedListCollection<K,V>& rhs);
  
  // destructor to delete a linked list
  ~LinkedListCollection();
  
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
  struct Node {
    K key;
    V value;
    Node* next;
  };
  Node* head;
  Node* tail;
  int length;

  void make_empty()
  {
    Node* tmp = head;
    while(length > 0)
    {
      tmp = head->next;
      delete head;
      head = tmp;
      --length;
    }
  }
  // Optional: declare a void make_empty() helper function

};


// TODO: Implement member functions here
// 
// NOTE: Within the sort function, you can use the keys() function to
//       build up the all_keys_sorted vector, then call std::sort over
//       the all_keys_sorted list as in HW3


// constructor to initialize empty linked list
template <typename K, typename V>
LinkedListCollection<K,V>::LinkedListCollection()
{
  head = nullptr;
  tail = nullptr;
  length = 0;
}

// copy constructor
template <typename K, typename V>
LinkedListCollection<K,V>::LinkedListCollection(const LinkedListCollection<K,V>& rhs)
{
  head = nullptr;
  tail = nullptr;
  length = 0;
  Node* tmp = rhs.head;
  while(tmp->next != nullptr)
  {
    add(tmp->key, tmp->value);
    tmp = tmp->next;
  }
}

// assignment operator
template <typename K, typename V>
LinkedListCollection<K,V>& LinkedListCollection<K,V>::operator=(const LinkedListCollection<K,V>& rhs)
{
  if(head == rhs.head)
    return *this;
  make_empty();
  Node* tmp = rhs.head;
  while(tmp->next != nullptr)
  {
    add(tmp->key, tmp->value);
    tmp = tmp->next;
  } 
  return *this;
}
  
// destructor to delete a linked list
template <typename K, typename V>
LinkedListCollection<K,V>::~LinkedListCollection()
{
  make_empty();
}
  
// add a new key-value pair into the collection 
template <typename K, typename V>
void LinkedListCollection<K,V>::add(const K& a_key, const V& a_val)
{
  Node* tmp = new Node;
  tmp->key = a_key;
  tmp->value = a_val;
  tmp->next = nullptr;
  if(length == 0)
    head = tmp;
  else
    tail->next = tmp;
  tail = tmp;
  ++length;
}

// remove a key-value pair from the collectiona
template <typename K, typename V>
void LinkedListCollection<K,V>::remove(const K& a_key)
{
 if(length == 0)
    return; 
  Node* tmp = head;
  if(tmp->key == a_key)
  { 
    tmp = head->next;
    delete head;
    head = tmp;
    --length;
    return;
  }
  Node* prev = tmp;
  while(tmp)
  {
    if(tmp->key == a_key)
      break;
    prev = tmp;
    tmp = tmp->next;
  }
  if(!tmp)
    return;
  if(tmp == tail)
    tail = prev;
  prev->next = tmp->next;
  delete tmp;
  --length; 
}

// find and return the value associated with the key
template <typename K, typename V>
bool LinkedListCollection<K,V>::find(const K& search_key, V& the_val) const
{
  if(length == 0)
    return false;
  Node* tmp = head;
  while(tmp->key != search_key && tmp->next != nullptr)
    tmp = tmp->next;
  if(tmp->key == search_key)
  {
    the_val = tmp->value;
    return true;
  }
  else
    return false;
}

// find and return the values with keys >= to k1 and <= to k2 
template <typename K, typename V>
void LinkedListCollection<K,V>::find(const K& k1, const K& k2, std::vector<V>& vals) const
{
  Node* tmp = head;
  while(tmp != nullptr)
  {
    if(tmp->key >= k1 && tmp->key <= k2)
      vals.push_back(tmp->value);
    tmp = tmp->next;
  }
}

// return all of the keys in the collection 
template <typename K, typename V>
void LinkedListCollection<K,V>::keys(std::vector<K>& all_keys) const
{
  Node* tmp = head;
  while(tmp != nullptr)
  {
    all_keys.push_back(tmp->key);
    tmp = tmp->next;
  }
}

// return all of the keys in ascending (sorted) order
template <typename K, typename V>
void LinkedListCollection<K,V>::sort(std::vector<K>& all_keys_sorted) const
{
  keys(all_keys_sorted);
  std::sort(all_keys_sorted.begin(), all_keys_sorted.end());
}

// return the number of key-value pairs in the collection
template <typename K, typename V>
int LinkedListCollection<K,V>::size() const
{
  return length;
}


#endif
