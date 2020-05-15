//----------------------------------------------------------------------
// Author: Jason lunder
// Course: CPSC 223, Spring 2020
// Assign: 9
// File:   hw9_test.cpp
//
// This program tests an binary search tree
// implementation of the collections class.
// It does so by testing the various different
// functions that must be implemented in any
// implementation of colllection. This includes
// Add, remove, find, range, and sort.
// Also tested are various cases of these functions and
// some functionality specific to binary search trees.
//----------------------------------------------------------------------


#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "bst_collection.h"

using namespace std;


// Test 1
TEST(BasicListTest, CorrectSize) {
  BSTCollection<string,double> c;
  ASSERT_EQ(0, c.size());
  c.add("b", 10.0);
  ASSERT_EQ(1, c.size());
  c.add("a", 20.0);
  ASSERT_EQ(2, c.size());
  c.add("c", 20.0);
  ASSERT_EQ(3, c.size());

}

// Test 2
TEST(BasicListTest, SimpleFind) {
  BSTCollection<string,double> c;
  double v;
  ASSERT_EQ(false, c.find("b", v));
  c.add("b", 10.0);
  ASSERT_EQ(true, c.find("b", v));
  ASSERT_EQ(10.0, v);
  ASSERT_EQ(false, c.find("a", v));
  c.add("a", 20.0);
  ASSERT_EQ(true, c.find("a", v));
  ASSERT_EQ(20.0, v);
}

// Test 3
TEST(BasicListTest, SimpleRemoveElems) {
  BSTCollection<string,int> c;
  c.add("b", 10);
  c.add("a", 20);
  c.add("d", 30);
  c.add("c", 30);
  ASSERT_EQ(4, c.size());
  int v;
  c.remove("a");
  ASSERT_EQ(3, c.size());
  ASSERT_EQ(false, c.find("a", v));
  vector<string> keys;
  c.keys(keys);
  ASSERT_EQ(keys.size(), 3);
  c.remove("b");
  ASSERT_EQ(2, c.size());
  ASSERT_EQ(false, c.find("b", v));  
  c.remove("c");
  ASSERT_EQ(1, c.size());
  ASSERT_EQ(false, c.find("c", v));  
  c.remove("d");
  ASSERT_EQ(0, c.size());
  ASSERT_EQ(false, c.find("d", v));  
}

// Test 4
TEST(BasicListTest, SimpleRange) {
  BSTCollection<int,string> c;
  c.add(50, "e");
  c.add(10, "a");
  c.add(30, "c");
  c.add(40, "d");
  c.add(60, "f");
  c.add(20, "b");
  vector<string> vs;
  c.find(20, 40, vs);
  ASSERT_EQ(3, vs.size());
  // note that the following "find" is a C++ built-in function
  ASSERT_EQ(vs.end(), find(vs.begin(), vs.end(), "a"));
  ASSERT_NE(vs.end(), find(vs.begin(), vs.end(), "b"));
  ASSERT_NE(vs.end(), find(vs.begin(), vs.end(), "c"));
  ASSERT_NE(vs.end(), find(vs.begin(), vs.end(), "d"));
  ASSERT_EQ(vs.end(), find(vs.begin(), vs.end(), "e"));  
  ASSERT_EQ(vs.end(), find(vs.begin(), vs.end(), "f"));  
}

// Test 5
TEST(BasicListTest, SimpleSort) {
  BSTCollection<string,int> c;
  c.add("a", 10);
  c.add("e", 50);
  c.add("c", 30);
  c.add("b", 20);
  c.add("d", 40);
  vector<string> sorted_ks;
  c.sort(sorted_ks);
  ASSERT_EQ(5, sorted_ks.size());
  // check if in sorted order
  for (int i = 0; i < int(sorted_ks.size()) -1; ++i)
    ASSERT_LE(sorted_ks[i], sorted_ks[i+1]);
}


// TODO: ... additional tests ...
TEST(NotTrashTests, RemoveFromMiddleOfChain)
{
  BSTCollection<string,double> c;
  double v;
  c.add("f", 10);
  c.add("c", 30);
  c.add("d", 30);
  c.add("k", 20);
  c.add("g", 10);
  c.add("h", 10);
  c.add("a", 10);
  c.add("i", 10);
  c.add("b", 20);
  c.add("j", 10);
  c.add("e", 10);
  ASSERT_EQ(11, c.size());
  c.remove("c");
  ASSERT_EQ(false, c.find("c", v));
  ASSERT_EQ(true, c.find("b", v));
  ASSERT_EQ(true, c.find("k", v));
  ASSERT_EQ(10, c.size());
}

TEST(NotTrashTests, RemoveFromBeginningOfChain)
{
  BSTCollection<string,double> c;
  double v;
  c.add("a", 10);
  c.add("b", 20);
  c.add("c", 30);
  c.add("d", 30);
  c.add("e", 10);
  c.add("f", 10);
  c.add("g", 10);
  c.add("h", 10);
  c.add("i", 10);
  c.add("j", 10);
  c.add("k", 20);
  ASSERT_EQ(11, c.size());
  c.remove("k");
  ASSERT_EQ(false, c.find("k", v));
  ASSERT_EQ(true, c.find("b", v));
  ASSERT_EQ(true, c.find("c", v));
  ASSERT_EQ(10, c.size());
}

TEST(NotTrashTests, RemoveFromEndOfChain)
{
  BSTCollection<string,double> c;
  double v;
  c.add("d", 30);
  c.add("f", 10);
  c.add("g", 10);
  c.add("k", 20);
  c.add("e", 10);
  c.add("b", 20);
  c.add("j", 10);
  c.add("h", 10);
  c.add("a", 10);
  c.add("i", 10);
  c.add("c", 30);
  ASSERT_EQ(11, c.size());
  c.remove("b");
  ASSERT_EQ(false, c.find("b", v));
  ASSERT_EQ(true, c.find("c", v));
  ASSERT_EQ(true, c.find("k", v));
  ASSERT_EQ(10, c.size());
}

TEST(NotTrashTests, TestREEEEEEhash)
{
  BSTCollection<string,double> c;
  double v;
  c.add("l", 10);
  c.add("y", 30);
  c.add("g", 10);
  c.add("v", 20);
  c.add("e", 10);
  c.add("ab", 10);
  c.add("n", 30);
  c.add("m", 20);
  c.add("t", 10);
  c.add("x", 20);
  c.add("s", 10);
  c.add("a", 10);
  c.add("q", 10);
  c.add("af", 10);
  c.add("ag", 20);
  c.add("w", 10);
  c.add("u", 10);
  c.add("f", 10);
  c.add("j", 10);
  c.add("r", 10);
  c.add("p", 10);
  c.add("b", 20);
  c.add("aa", 10);
  c.add("o", 30);
  c.add("ac", 10);
  c.add("z", 30);
  c.add("c", 30);
  c.add("k", 20);
  c.add("h", 10);
  c.add("d", 30);
  c.add("i", 10);
  c.add("ad", 10);
  c.add("ae", 10);
  ASSERT_EQ(33, c.size());
}

TEST(NotTrashTests, CpyCon)
{ 
  BSTCollection<string,int> c;
  c.add("w", 10);
  c.add("u", 10);
  c.add("ac", 10);
  c.add("f", 10);
  c.add("j", 10);
  c.add("ad", 10);
  BSTCollection<string, int> d(c);

  ASSERT_EQ(d.size(), c.size());
}

TEST(NotTrashTests, AssignmentOp)
{ 
  BSTCollection<string,int> c;
  c.add("w", 10);
  c.add("u", 10);
  c.add("ac", 10);
  c.add("f", 10);
  c.add("j", 10);
  BSTCollection<string,int> d;
  d = c;
  
  ASSERT_EQ(d.size(), c.size());
}

TEST(NotTrashTests, AssignmentOpNotEmpty)
{ 
  BSTCollection<string,int> c;
  c.add("w", 10);
  c.add("u", 10);
  c.add("ac", 10);
  c.add("f", 10);
  c.add("j", 10);
  c.add("aa", 10);
  c.add("ad", 10);
  BSTCollection<string,int> d;
  d.add("as", 1341);
  d = c;
  ASSERT_EQ(d.size(), c.size());
}  

TEST(NotTrashTests, keys)
{
  BSTCollection<string,int> c;
  c.add("b", 10);
  c.add("a", 20);
  c.add("d", 30);
  c.add("c", 30);
  ASSERT_EQ(4, c.size());
  vector<string> k;
  c.keys(k);
  ASSERT_EQ(4, c.size());
  ASSERT_EQ(c.size(), k.size());
}

TEST(NotTrashTests, keysWRehash)
{
  BSTCollection<string,int> c;
  c.add("l", 10);
  c.add("y", 30);
  c.add("g", 10);
  c.add("v", 20);
  c.add("e", 10);
  c.add("ab", 10);
  c.add("n", 30);
  c.add("m", 20);
  c.add("t", 10);
  c.add("x", 20);
  c.add("s", 10);
  c.add("a", 10);
  c.add("q", 10);
  c.add("af", 10);
  c.add("ag", 20);
  c.add("w", 10);
  c.add("u", 10);
  c.add("f", 10);
  c.add("j", 10);
  c.add("r", 10);
  c.add("p", 10);
  c.add("b", 20);
  c.add("aa", 10);
  c.add("o", 30);
  c.add("ac", 10);
  c.add("z", 30);
  c.add("c", 30);
  c.add("k", 20);
  c.add("h", 10);
  c.add("d", 30);
  c.add("i", 10);
  c.add("ad", 10);
  c.add("ae", 10);
  vector<string> k;
  c.keys(k);
  ASSERT_EQ(c.size(), k.size());
}
// Test ?
TEST(NotTrashTests, RemoveMoreElems) {
  BSTCollection<string,int> c;
  c.add("b", 10);
  c.add("a", 20);
  c.add("d", 30);
  c.add("c", 30);
  ASSERT_EQ(4, c.size());
  int v;
  c.remove("a");
  ASSERT_EQ(3, c.size());
  ASSERT_EQ(false, c.find("a", v));
  c.remove("b");
  ASSERT_EQ(2, c.size());
  ASSERT_EQ(false, c.find("b", v));  
  c.remove("c");
  ASSERT_EQ(1, c.size());
  ASSERT_EQ(false, c.find("c", v));  
  c.remove("d");
  ASSERT_EQ(0, c.size());
  ASSERT_EQ(false, c.find("d", v));
  c.remove("a");  
  ASSERT_EQ(false, c.find("a", v));
  c.add("abcdefg", 20);
  ASSERT_EQ(true, c.find("abcdefg", v));
  c.remove("abcdefg");
  ASSERT_EQ(false, c.find("abcdefg", v));
}

TEST(NotTrashTests, CopyRemove)
{
  BSTCollection<string, int> c;
  c.add("e", 9416);
  c.add("f", 3641);
  c.add("h", 3671);
  c.add("d", 5342674);
  c.add("k", 31438);
  c.add("a", 35413);
  c.add("g", 341432);
  c.add("c", 3371);
  c.add("j", 134149);
  c.add("i",19433);
  c.add("b", 675);
  c.add("l", 38);
  BSTCollection<string, int> d = c;
  ASSERT_EQ(12, d.size());
  ASSERT_EQ(12, c.size());
  d.remove("b");
  ASSERT_EQ(11, d.size());
  ASSERT_EQ(12, c.size());
  d.remove("c");
  ASSERT_EQ(10, d.size());
  ASSERT_EQ(12, c.size());
  d.remove("h");
  ASSERT_EQ(9, d.size());
  ASSERT_EQ(12, c.size());
}

TEST(NotTrashTests, LongHeightTest) {
  BSTCollection<int, int> c;
  c.add(65, 755335);
  c.add(20, 28641);
  c.add(10, 56431315);
  c.add(90, 56431);
  c.add(60, 153453); 
  c.add(25, 2156461);
  c.add(50, 469980);
  c.add(15, 957910);
  c.add(35, 563751);
  c.add(80, 687); 
  c.add(5, 245);
  c.add(55, 41531);
  c.add(0, 245);
  c.add(40, 4141230);
  c.add(85, 45277498); 
  c.add(45, 41441586);
  c.add(30, 41114004);
  c.add(75, 112400);
  c.add(70, 10014);
  c.add(95, 1031); 
  ASSERT_EQ(20, c.size());
  ASSERT_EQ(8, c.height());
}

TEST(TestsFromBinSearchCollection, SortedAfterRemove)
{ 
  BSTCollection<string, int> c;
  c.add("f", 3641);
  c.add("h", 3671);
  c.add("d", 5342674);
  c.add("k", 31438);
  c.add("a", 35413);
  c.add("g", 341432);
  c.add("c", 3371);
  c.add("j", 134149);
  
  vector<string> sorted_ks;
  c.sort(sorted_ks);
  for (int i = 0; i < int(sorted_ks.size()) -1; ++i)
    ASSERT_LE(sorted_ks[i], sorted_ks[i+1]);
  vector<string> sorted_ks2;
  c.sort(sorted_ks2); 
  for (int i = 0; i < int(sorted_ks2.size()) -1; ++i)
    ASSERT_LE(sorted_ks2[i], sorted_ks2[i+1]);
}

 
TEST(TestsFromBinSearchCollection, RemoveEdgeCases)
{
  BSTCollection<string, int> c;
  c.add("a", 12);
  c.add("c", 123);
  c.remove("b");
  ASSERT_EQ(2, c.size());
  c.remove("a");
  ASSERT_EQ(1, c.size());
  c.remove("c");
  ASSERT_EQ(0, c.size());
  c.remove("a");
  ASSERT_EQ(0, c.size());
}

TEST(TestsFromLinkedListCollection, RangeEdgeCases)
{
  BSTCollection<int, int> c;
  
  vector<int> vs;
  c.find(0, 2500, vs);
  ASSERT_EQ(0, vs.size());
  c.add(3, 231);
  c.add(5, 50);
  c.add(2, 2134);
  c.add(4, 123);
  c.add(1, 12);
  vector<int> ks;
  c.find(0, 2500, ks);
  ASSERT_EQ(5, ks.size());
}

TEST(TestsFromLinkedListCollection, AssignmentOperator)
{
  BSTCollection<string, int> c;
  BSTCollection<string, int> b;
  c.add("a", 13);
  c.add("b", 14);
  ASSERT_EQ(2, c.size());
  ASSERT_EQ(0, b.size());
  b = c;
  ASSERT_EQ(2, b.size());

  BSTCollection<int, int> a;
  a.add(0, 0);
  a.add(0, 1);
  a.add(0, 2);
  a.add(0, 3);
  a.add(0, 4);
  ASSERT_EQ(5, a.size());
  a = a;
  ASSERT_EQ(5, a.size());
}

int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

