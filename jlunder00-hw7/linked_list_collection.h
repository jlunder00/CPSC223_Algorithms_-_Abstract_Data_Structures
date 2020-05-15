//----------------------------------------------------------------------
// Author:
// Course: CPSC 223, Spring 2020
// Assign: 7
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

  // in place sorting 
  void selection_sort();
  void insertion_sort();
  void merge_sort();
  void quick_sort();
  
private:
  
  
  // linked list node structure
  struct Node {
    K key;
    V value;
    Node* next;
  };
  Node* head;
  Node* tail;
  int length;

  // helper to delete linked list (optional)
  // void make_empty();

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

  // helper functions for merge and quick sort
  Node* merge_sort(Node* left, int len);
  Node* merge(Node* left, Node* right);
  Node* quick_sort(Node* start, int len);
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
  while(tmp)
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
  while(tmp)
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
  while(tmp)
  {
    if(tmp->key == search_key)
    {
      the_val = tmp->value;
      return true;
    }
    tmp = tmp->next;
  }
  return false;
}

// find and return the values with keys >= to k1 and <= to k2 
template <typename K, typename V>
void LinkedListCollection<K,V>::find(const K& k1, const K& k2, std::vector<V>& vals) const
{
  Node* tmp = head;
  while(tmp)
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
  while(tmp)
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

// TODO: Implement the two "in place" sorting algorithms below
//Sort the linked list in place with the selection sort algorithm
template<typename K, typename V>
void LinkedListCollection<K,V>::selection_sort()
{
  //dont sort if length is 1 or 0
  if(!head || tail == head)
    return;
  Node* tmp = head;
  Node* smallest = head;
  Node* first = head;
  Node* prev = head;
  Node* firstPrev = head;
 
  //loop until the sorted region reaches the second to last node
  while(first->next)
  {
    tmp = first;
    smallest = first;
    prev = first;
    while(tmp->next)
    {
      //find the smallest node in the unsorted region and
      //store pointers to it and the node before it
      if(tmp->next->key < smallest->key)
      {
        smallest = tmp->next;
        prev = tmp;
      }
      tmp = tmp->next;
    }
    //dont swap if they are the same node, as it is already in sorted order
    if(smallest != first)
    {
      prev->next = first;
      if(head == first)
        head = smallest;
      else
      	firstPrev->next = smallest;
      tmp = smallest->next;
      smallest->next = first->next;
      first->next = tmp;
    }

    //Increment nodes tracking the first item in the unsorted region
    firstPrev = smallest;
    first = firstPrev->next;
  }
}

//In place insertion sort
template<typename K, typename V>
void LinkedListCollection<K,V>::insertion_sort()
{
  //dont run if the list is empty or has only 1 item
  if(!head || tail == head)
    return;

  //pointers to keep track of the nodes on the boundary of the sorted and unsorted lists
  //Also pointers to nodes for iterating through the list to find the correct spot
  Node* lastSorted = head;
  Node* firstUnsorted = head;
  Node* tmp = head;
  Node* prev = head;
  
  //Loop until the end of the sorted region is one behind the last node, sorting
  //that node on the last loop
  while(lastSorted->next)
  {
    firstUnsorted = lastSorted->next;
    tmp = head;
    prev = head;
    while(tmp != firstUnsorted)
    {
      if(firstUnsorted->key < tmp->key)
        break;
      
      //keep track of the node to place the next node behind and the node behind that one
      prev = tmp;
      tmp = tmp->next;
    }
   
    //If it is already in the correct position
    if(tmp == firstUnsorted)
    {
      lastSorted = firstUnsorted;
      continue;
    }
    lastSorted->next = firstUnsorted->next;
    firstUnsorted->next = tmp;
    
    //Either set the head to point to the inserting node
    //or set the node behind to point to the inserting node
    if(tmp == head)
      head = firstUnsorted;
    else
      prev->next = firstUnsorted;
  }
  //fix the tail
  tail = lastSorted;
}

// TODO: Add Selection and Insertion Sorts here (from HW6)


// TODO: Implement the following for HW7

template<typename K, typename V>
void LinkedListCollection<K,V>::merge_sort()
{
  head = merge_sort(head, length);
  if(tail)
  {
    while(tail->next)
      tail = tail->next;
  }
}

template<typename K, typename V>
typename LinkedListCollection<K,V>::Node*
LinkedListCollection<K,V>::merge_sort(Node* left, int len)
{
  if(len > 1)
  {
    int iterator = (len-1)/2;
    int mid = len/2;
    Node* tmp = left;
    Node* prev = tmp;
    for(int i = 0; i < iterator; ++i)
      prev = prev->next;
    tmp = prev->next;
    prev->next = nullptr;
    left = merge_sort(left, len-mid);
    tmp = merge_sort(tmp, mid);
    left = merge(left, tmp);
  }
  return left;
}

template<typename K, typename V>
typename LinkedListCollection<K,V>::Node*
LinkedListCollection<K,V>::merge(Node* left, Node* right)
{
  Node* tracer = nullptr;
  Node* first1 = left;
  Node* first2 = right;

  if(first1 && first2)
  {
    if(first1->key < first2->key)
    {
      left = first1;
      first1 = first1->next;
    }
    else
    {
      left = first2;
      first2 = first2->next;
    }
    tracer = left;
  }
  while(first1 && first2)
  {
    if(first1->key < first2->key)
    {
      tracer->next = first1;
      first1 = first1->next;
    }
    else
    {
      tracer->next = first2;
      first2 = first2->next;
    }
    tracer=tracer->next;
  }
  tracer->next = (first1) ? first1 : first2;
  return left;
}


template<typename K, typename V>
void LinkedListCollection<K,V>::quick_sort()
{
  head = quick_sort(head, length);
  if(tail)
  {
    while(tail->next)
      tail = tail->next;
  }
}

template<typename K, typename V>
typename LinkedListCollection<K,V>::Node*
LinkedListCollection<K,V>::quick_sort(Node* start, int len)
{
  if(len > 2)
  {
    Node* pivot = start;
    K& key = pivot->key;
    Node* left = nullptr;
    Node* ltrace = nullptr;
    Node* right = nullptr;
    Node* rtrace = nullptr;
    Node* tmp = start->next;
    pivot->next = nullptr;
    int l = 0;
    while(tmp)
    {
      if(tmp->key < key)
      {
        if(!left)
        {
	  left = tmp;
          ltrace = left;
	}else
  	{
	  ltrace->next = tmp;
	  ltrace = tmp;
	}
	++l;
      }else
      {
        if(!right)
	{
	  right = tmp;
          rtrace = right;
	}else
	{
	  rtrace->next = tmp;
	  rtrace = tmp;
	}
      }
      tmp = tmp->next;
    }
    if(ltrace)
    	ltrace->next = nullptr;
    if(rtrace)
    	rtrace->next = nullptr;

    if(l > 1)
    	start = quick_sort(left, l);
    else
        start = left;
    int r = len-l-1;
    if(r > 1)
	right = quick_sort(right, r);
    
    if(ltrace)
    {
      while(ltrace->next)
        ltrace = ltrace->next;
      ltrace->next = pivot;
    }
    else
      start = pivot;
    pivot->next = right;
  }
  else if(len == 2)
  {
    Node* tmp = start->next;
    if(tmp->key < start->key)
    {
      tmp->next = start;
      start->next = nullptr;
      start = tmp;
    }
  }
  return start;
}


#endif
