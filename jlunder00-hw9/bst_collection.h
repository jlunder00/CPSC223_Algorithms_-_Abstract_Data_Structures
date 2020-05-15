
//----------------------------------------------------------------------
// Author: Jason Lunder
// Course: CPSC 223, Spring 2020
// Assign: 9
// File:   bst_collection.h
// An implementation of the collection class
// using a binary search tree. This uses Nodes like
// a linked list with pointers to 2 other nodes, 
// a left and a right node. The tree is organized using these
// pointers according to the value of the key at each node.
// This implements all the functions of the Collection class
// as well as some additional helper functions for this purpose
// and one for functionality unique to the BST, the height function.
//----------------------------------------------------------------------



#ifndef BST_COLLECTION_H
#define BST_COLLECTION_H

#include <vector>
#include <algorithm>           
#include "collection.h"


template<typename K, typename V>
class BSTCollection : public Collection<K,V>
{
public:

  // create an empty tree
  BSTCollection();
  
  // bst copy constructor
  BSTCollection(const BSTCollection <K,V>& rhs);

  // bst assignment operator
  BSTCollection<K,V>& operator=(const BSTCollection <K ,V >& rhs);

  // delete the bst
  ~BSTCollection();
  
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

  // return the height of the tree
  int height() const;
  
private:

  // tree node structure
  struct Node {
    K key;
    V value;
    Node* left;
    Node* right;
  };

  // helper to empty entire tree
  void make_empty(Node* subtree_root);
  
  // helper to calc tree height (can use std::max)
  int height(const Node* subtree_root) const;

  // helper to build sorted list of keys (used by keys and sort)
  void inorder(const Node* subtree_root, std::vector<K>& keys) const;

  // helper to recursively find range of keys
  void range_search(const Node* subtree_root, const K& k1, const K& k2,
                    std::vector<V>& vals) const;

  // recursively (deep) copy ancestors of src to dst
  void preorder_copy(const Node* subtree_root_src, Node* subtree_root_dst);
	
  // helper function to remove a node recursively
  Node* remove(const K& key, Node* subtree_root);
  
  void print(Node* subRoot);
  // number of k-v pairs in the collection
  int collection_size; 

  // tree root
  Node* root;
   
};

// create an empty tree
template<typename K, typename V>
BSTCollection<K,V>::BSTCollection()
{
  root = nullptr;
  collection_size = 0;
}
  
// bst copy constructor
template<typename K, typename V>
BSTCollection<K,V>::BSTCollection(const BSTCollection <K,V>& rhs)
{
  root = nullptr;
  collection_size = 0;
  if(rhs.collection_size > 0)
  {
    Node* tmpRoot = new Node;
    tmpRoot->key = rhs.root->key;
    tmpRoot->value = rhs.root->value;
    root = tmpRoot;
    root->left = nullptr;
    root->right = nullptr;
    *this = rhs;
  }
}

// bst assignment operator
template<typename K, typename V>
BSTCollection<K,V>& BSTCollection<K,V>::operator=(const BSTCollection <K ,V >& rhs)
{
  if(root == rhs.root)
    return *this;
  if(root)
  {
    make_empty(root->left);
    make_empty(root->right);
  }
  else
  {
    Node* tmp = new Node;
    root = tmp;
    root->left = nullptr;
    root->right = nullptr;
  }
  root->key = rhs.root->key;
  root->value = rhs.root->value;
  preorder_copy(rhs.root, root);
  collection_size = rhs.collection_size;
  return *this; 
}

// delete the bst
template<typename K, typename V>
BSTCollection<K,V>::~BSTCollection()
{
  make_empty(root);
}
  
// add a new key-value pair into the collection 
template<typename K, typename V>
void BSTCollection<K,V>::add(const K& a_key, const V& a_val)
{
  Node* tmp = root;
  Node* prev = nullptr;
  Node* newNode = new Node;
  newNode->right = nullptr;
  newNode->left = nullptr;
  newNode->key = a_key;
  newNode->value = a_val;
  while(tmp)
  {
    prev = tmp;
    if(a_key < tmp->key)
      tmp = tmp->left;
    else
      tmp = tmp->right;
  }
  if(!prev)
    root = newNode;
  else if(a_key < prev->key)
    prev->left = newNode;
  else
    prev->right = newNode;
  ++collection_size;
}

// remove a key-value pair from the collectiona
template<typename K, typename V>
void BSTCollection<K,V>::remove(const K& a_key)
{
  root = remove(a_key, root);
}

// find and return the value associated with the key
template<typename K, typename V>
bool BSTCollection<K,V>::find(const K& search_key, V& the_val) const
{
  Node* tmp = root;
  while(tmp && tmp->key != search_key)
  {
    if(tmp->key > search_key)
      tmp = tmp->left;
    else
      tmp = tmp->right;
  }
  if(tmp)
    the_val = tmp->value;
  return tmp;
    
}

// find and return the values with keys >= to k1 and <= to k2 
template<typename K, typename V>
void BSTCollection<K,V>::find(const K& k1, const K& k2, std::vector<V>& vals) const
{
  range_search(root, k1, k2, vals);
}
  
// return all of the keys in the collection 
template<typename K, typename V>
void BSTCollection<K,V>::keys(std::vector<K>& all_keys) const
{
  inorder(root, all_keys);
}

// return all of the keys in ascending (sorted) order
template<typename K, typename V>
void BSTCollection<K,V>::sort(std::vector<K>& all_keys_sorted) const
{
  inorder(root, all_keys_sorted);
}

// return the number of key-value pairs in the collection
template<typename K, typename V>
int BSTCollection<K,V>::size() const
{
  return collection_size;
}

// return the height of the tree
template<typename K, typename V>
int BSTCollection<K,V>::height() const
{
  return height(root);
}
  

// helper to empty entire tree
template<typename K, typename V>
void BSTCollection<K,V>::make_empty(Node* subtree_root)
{
  if(subtree_root)
  {
    if(subtree_root->left)
      make_empty(subtree_root->left);
    if(subtree_root->right)
      make_empty(subtree_root->right);
    if(subtree_root->left && subtree_root->right)
    {
      delete subtree_root;
      return;
    }
  }
}
  
// helper to calc tree height (can use std::max)
template<typename K, typename V>
int BSTCollection<K,V>::height(const Node* subtree_root) const
{
  if(!subtree_root)
    return 0;
  else
  {
    int left = height(subtree_root->left);
    int right = height(subtree_root->right);
    int max = std::max(left, right);
    return ++max;
  }
}

// helper to build sorted list of keys (used by keys and sort)
template<typename K, typename V>
void BSTCollection<K,V>::inorder(const Node* subtree_root, std::vector<K>& keys) const
{
  if(subtree_root)
  {
    inorder(subtree_root->left, keys);
    keys.push_back(subtree_root->key);
    inorder(subtree_root->right, keys);
  }
}

// helper to recursively find range of keys
template<typename K, typename V>
void BSTCollection<K,V>::range_search(const Node* subtree_root, const K& k1, const K& k2, std::vector<V>& vals) const
{
  if(subtree_root)
  {
    K key = subtree_root->key;
    if(k1 < key)
      range_search(subtree_root->left, k1, k2, vals);
    if(key <= k2 && key >= k1)
      vals.push_back(subtree_root->value);
    if(k2 > key)
      range_search(subtree_root->right, k1, k2, vals);
  }
  return;
}

// recursively (deep) copy ancestors of src to dst
template<typename K, typename V>
void BSTCollection<K,V>::preorder_copy(const Node* subtree_root_src, Node* subtree_root_dst)
{
  Node* leftSrc = subtree_root_src->left;
  Node* rightSrc = subtree_root_src->right;
  if(leftSrc)
  {
    Node* tmp = new Node;
    tmp->key = leftSrc->key;
    tmp->value = leftSrc->value;
    subtree_root_dst->left = tmp;
    preorder_copy(leftSrc, tmp);
  }
  else
    subtree_root_dst->left = nullptr;
  if(subtree_root_src->right)
  {
    Node* tmp = new Node;
    tmp->key = rightSrc->key;
    tmp->value = rightSrc->value;
    subtree_root_dst->right = tmp;
    preorder_copy(rightSrc, tmp);
  }
  else
    subtree_root_dst->right = nullptr;
}
	
// helper function to remove a node recursively
template<typename K, typename V>
typename BSTCollection<K,V>::Node*
BSTCollection<K,V>::remove(const K& key, Node* subtree_root)
{
  if(subtree_root)
  {
    if(key<subtree_root->key)
    {
      subtree_root->left = remove(key, subtree_root->left);
    }
    else if(key>subtree_root->key)
    {
      subtree_root->right = remove(key, subtree_root->right);
    }
    else
    {
      Node* rightSide = subtree_root->right;
      Node* leftSide = subtree_root->left;
      if(!leftSide) 
      {
        delete subtree_root;
	--collection_size;
        return rightSide;
      }
      else if(!rightSide)
      { 
        delete subtree_root;
	--collection_size;
        return leftSide;
      }
      else
      {
	Node* tmp = subtree_root->right;
	while(tmp->left)
	  tmp = tmp->left;
        subtree_root->key = tmp->key;
	subtree_root->value = tmp->value;
	subtree_root->right = remove(tmp->key, subtree_root->right);
	return subtree_root;
      }
    }
  }
  return subtree_root;
}
        
      
  
#endif
