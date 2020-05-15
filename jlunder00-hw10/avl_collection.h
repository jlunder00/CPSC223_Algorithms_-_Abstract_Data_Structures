
//----------------------------------------------------------------------
// Author: Jason Lunder
// Course: CPSC 223, Spring 2020
// Assign: 10
// File:   avl_collection.h
// This is a AVL implementation of the collection class
// It uses a Binary search tree structure and keeps it balanced
//----------------------------------------------------------------------


#ifndef AVL_COLLECTION_H
#define AVL_COLLECTION_H

#include <vector>
#include <algorithm>
#include <string>               // for testing
#include "collection.h"


template<typename K, typename V>
class AVLCollection : public Collection<K,V>
{
public:

  // create an empty tree
  AVLCollection();
  
  // tree copy constructor
  AVLCollection(const AVLCollection<K,V>& rhs);

  // tree assignment operator
  AVLCollection<K,V>& operator=(const AVLCollection<K,V>& rhs);

  // delete a tree
  ~AVLCollection();
  
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
  
  // avl tree node structure
  struct Node {
    K key;
    V value;
    int height;
    Node* left;
    Node* right;
  };

  // helper to empty entire tree
  void make_empty(Node* subtree_root);
  
  // helper to build sorted list of keys (used by keys and sort)
  void inorder(const Node* subtree_root, std::vector<K>& keys) const;

  // helper to recursively find range of values
  void range_search(const Node* subtree_root, const K& k1, const K& k2,
                    std::vector<V>& vals) const;

  // recursively (deep) copy ancestors of src to dst
  void preorder_copy(const Node* subtree_root_src, Node* subtree_root_dst);

  // helper function to remove a node recursively
  Node* remove(const K& key, Node* subtree_root);

  // recursive add helper
  Node* add(Node* subtree_root, const K& a_key, const V& a_val);
  
  // rotate right helper
  Node* rotate_right(Node* k2);

  // rotate left helper
  Node* rotate_left(Node* k2);

  // rebalance the subtree rooted at subtree_root
  Node* rebalance(Node* subtree_root);
  
  // number of k-v pairs in the collection
  int tree_size; 

  // root node of tree
  Node* root;

  // for testing only: "pretty" prints a tree with node heights
  void print_tree(std::string indent, Node* subtree_root) const;
};


// TODO: implement the above functions here ...

// create an empty tree
template<typename K, typename V>
AVLCollection<K,V>::AVLCollection()
{
  root = nullptr;
  tree_size = 0;
}
  
// bst copy constructor
template<typename K, typename V>
AVLCollection<K,V>::AVLCollection(const AVLCollection <K,V>& rhs)
{
  root = nullptr;
  tree_size = 0;
  if(rhs.tree_size > 0)
  {
    Node* tmpRoot = new Node;
    tmpRoot->key = rhs.root->key;
    tmpRoot->value = rhs.root->value;
    tmpRoot->height = rhs.root->height;
    root = tmpRoot;
    root->left = nullptr;
    root->right = nullptr;
    *this = rhs;
  }
}

// bst assignment operator
template<typename K, typename V>
AVLCollection<K,V>& AVLCollection<K,V>::operator=(const AVLCollection <K ,V >& rhs)
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
  root->height = rhs.root->height;
  preorder_copy(rhs.root, root);
  tree_size = rhs.tree_size;
  return *this; 
}

template<typename K, typename V>
AVLCollection<K,V>::~AVLCollection()
{
  make_empty(root);
}
// NOTE: some examples given below ...


// return the height of the tree
template<typename K, typename V> 
int AVLCollection<K,V>::height() const
{
  if (!root)
    return 0;
  return root->height;
}


// rotate right helper
template<typename K, typename V>
typename AVLCollection<K,V>::Node*
AVLCollection<K,V>::rotate_right(Node* k2)
{
  Node* k1 = k2->left;
  k2->left = k1->right;
  k1->right = k2;
  Node* lptr = k2->left;
  Node* rptr = k2->right;
  int leftHeight = (lptr) ? lptr->height:0;
  int rightHeight = (rptr) ? rptr->height:0;
  k2->height = 1 + ((leftHeight<rightHeight) ? rightHeight : leftHeight);
  return k1;
}

// rotate left helper
template<typename K, typename V>
typename AVLCollection<K,V>::Node*
AVLCollection<K,V>::rotate_left(Node* k2)
{
  Node* k1 = k2->right;
  k2->right = k1->left;
  k1->left = k2;
  Node* lptr = k2->left;
  Node* rptr = k2->right;
  int leftHeight = (lptr) ? lptr->height:0;
  int rightHeight = (rptr) ? rptr->height:0;
  k2->height = 1 + ((leftHeight<rightHeight) ? rightHeight : leftHeight);
  return k1;
}

template<typename K, typename V>
void AVLCollection<K,V>::add(const K& a_key, const V& a_val)
{
  // to build in the height and rebalance, this must be a recursive
  // function!
  root = add(root, a_key, a_val);
//  print_tree("", root); // for debugging
}

// recursive add helper
template <typename K, typename V>
typename AVLCollection<K,V>::Node*
AVLCollection<K,V>::add(Node* subtree_root, const K& a_key, const V& a_val)
{ 
  if(!subtree_root)
  {
    Node* tmp = new Node;
    tmp->key = a_key;
    tmp->value = a_val;
    tmp->height = 1;
    tmp->left = nullptr;
    tmp->right = nullptr;
    ++tree_size;
    return tmp;
  }
  if(subtree_root->key > a_key)
    subtree_root->left = add(subtree_root->left, a_key, a_val);
  else
    subtree_root->right = add(subtree_root->right, a_key, a_val);
  return rebalance(subtree_root);
}

// rebalance the subtree rooted at subtree_root
template<typename K, typename V>
typename AVLCollection<K,V>::Node*
AVLCollection<K,V>::rebalance(Node* subtree_root)
{
  Node* lptr = subtree_root->left;
  Node* rptr = subtree_root->right;
  int leftHeight = (lptr) ? lptr->height : 0;
  int rightHeight = (rptr) ? rptr->height : 0;
  subtree_root->height = 1 + ((leftHeight<rightHeight) ? rightHeight:leftHeight);
  int balance = leftHeight-rightHeight;
  if(balance == -2)
  {
    Node* problem = subtree_root->right;
    lptr = problem->left;
    rptr = problem->right;

    leftHeight = (lptr) ? lptr->height : 0;
    rightHeight = (rptr) ? rptr->height : 0;

    balance = leftHeight-rightHeight;

    if(balance > 0)
    {
      problem = rotate_right(problem);
      subtree_root->right = problem;
    }
    
    subtree_root = rotate_left(subtree_root);
    lptr = subtree_root->left;
    rptr = subtree_root->right;
    leftHeight = (lptr) ? lptr->height : 0;
    rightHeight = (rptr) ? rptr->height : 0;
    subtree_root->height = 1 + ((leftHeight<rightHeight) ? rightHeight:leftHeight);
  }
  else if(balance == 2)
  {
    Node* problem = subtree_root->left;
    lptr = problem->left;
    rptr = problem->right;

    leftHeight = (lptr) ? lptr->height : 0;
    rightHeight = (rptr) ? rptr->height : 0;

    balance = leftHeight-rightHeight;

    if(balance < 0)
    {
      problem = rotate_left(problem);
      subtree_root->left = problem;
    }

    subtree_root = rotate_right(subtree_root);
    lptr = subtree_root->left;
    rptr = subtree_root->right;
    leftHeight = (lptr) ? lptr->height : 0;
    rightHeight = (rptr) ? rptr->height : 0;
    subtree_root->height = 1 + ((leftHeight<rightHeight) ? rightHeight:leftHeight);
  }

  return subtree_root;
}

template <typename K, typename V>
void AVLCollection<K,V>::remove(const K& a_key)
{
  root = remove(a_key, root);
  //print_tree("", root); // for debugging
}

// helper function to remove a node recursively
template <typename K, typename V>
typename AVLCollection<K,V>::Node*
AVLCollection<K,V>::remove(const K& key, Node* subtree_root)
{
  if(subtree_root)
  {
    if(key<subtree_root->key)
    {
      subtree_root->left = remove(key, subtree_root->left);
      subtree_root = rebalance(subtree_root);
    }
    else if(key>subtree_root->key)
    {
      subtree_root->right = remove(key, subtree_root->right);
      subtree_root = rebalance(subtree_root);
    }
    else
    {
      Node* rightSide = subtree_root->right;
      Node* leftSide = subtree_root->left;
      if(!leftSide) 
      {
        delete subtree_root;
	--tree_size;
        return rightSide;
      }
      else if(!rightSide)
      { 
        delete subtree_root;
	--tree_size;
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
        subtree_root = rebalance(subtree_root);
	return subtree_root;
      }
    }
  }
  return subtree_root;
}

// for testing only: "pretty" prints a tree with node heights
template<typename K, typename V>
void AVLCollection<K,V>::print_tree(std::string indent, Node* subtree_root) const
{
  if (subtree_root)
  {
    std::cout << indent << subtree_root->key <<" (h="<< subtree_root->height << ")" << std::endl;
    print_tree(indent + "  ", subtree_root->left);
    print_tree(indent + "  ", subtree_root->right);
  }
  else
    std::cout << indent << K() <<" (h="<< "0" << ")" << std::endl;
}

// helper to empty entire tree
template <typename K, typename V>
void AVLCollection<K,V>::make_empty(Node* subtree_root)
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
  
// helper to build sorted list of keys (used by keys and sort)
template <typename K, typename V>
void AVLCollection<K,V>::inorder(const Node* subtree_root, std::vector<K>& keys) const
{
  if(subtree_root)
  {
    inorder(subtree_root->left, keys);
    keys.push_back(subtree_root->key);
    inorder(subtree_root->right, keys);
  }
}

// helper to recursively find range of values
template <typename K, typename V>
void AVLCollection<K,V>::range_search(const Node* subtree_root, const K& k1, const K& k2, std::vector<V>& vals) const
{
  if(subtree_root)
  {
    K key = subtree_root->key;
    if(key <= k2 && key >= k1)
    {
      range_search(subtree_root->left, k1, k2, vals);
      vals.push_back(subtree_root->value);
      range_search(subtree_root->right, k1, k2, vals);
    }
    else
    {
      if(k2 < key)
        range_search(subtree_root->left, k1, k2, vals);
      else
        range_search(subtree_root->right, k1, k2, vals);
    }
  }
  return;
}

// recursively (deep) copy ancestors of src to dst
template <typename K, typename V>
void AVLCollection<K,V>::preorder_copy(const Node* subtree_root_src, Node* subtree_root_dst)
{
  Node* leftSrc = subtree_root_src->left;
  Node* rightSrc = subtree_root_src->right;
  if(leftSrc)
  {
    Node* tmp = new Node;
    tmp->key = leftSrc->key;
    tmp->value = leftSrc->value;
    tmp->height = leftSrc->height;
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
    tmp->height = rightSrc->height;
    subtree_root_dst->right = tmp;
    preorder_copy(rightSrc, tmp);
  }
  else
    subtree_root_dst->right = nullptr;
}

// find and return the value associated with the key
template <typename K, typename V>
bool AVLCollection<K,V>::find(const K& search_key, V& the_val) const
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
template <typename K, typename V>
void AVLCollection<K,V>::find(const K& k1, const K& k2, std::vector<V>& vals) const
{
//  std::cout<<"print start:"<<std::endl<<std::endl;
//  print_tree(i"", root); // for debugging
  range_search(root, k1, k2, vals);
}
  
// return all of the keys in the collection 
template <typename K, typename V>
void AVLCollection<K,V>::keys(std::vector<K>& all_keys) const
{
  inorder(root, all_keys);
}

// return all of the keys in ascending (sorted) order
template <typename K, typename V>
void AVLCollection<K,V>::sort(std::vector<K>& all_keys_sorted) const
{
  inorder(root, all_keys_sorted);
}

// return the number of key-value pairs in the collection
template <typename K, typename V>
int AVLCollection<K,V>::size() const
{
  return tree_size;
}


#endif
