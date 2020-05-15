//----------------------------------------------------------------------
// Author: Jason Lunder
// Course: CPSC 223, Spring 2020
// Assign: 8
// File:   hw8_test.cpp
//
// TODO: Tests Hash Table implementaiton of collection
//----------------------------------------------------------------------


#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "hash_table_collection.h"

using namespace std;


// Test 1
TEST(BasicListTest, CorrectSize) {
  HashTableCollection<string,double> c;
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
  HashTableCollection<string,double> c;
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
  HashTableCollection<string,int> c;
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
}

TEST(NotTrashTests, RemoveFromMiddleOfChain)
{
  HashTableCollection<string,double> c;
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
  c.remove("c");
  ASSERT_EQ(false, c.find("c", v));
  ASSERT_EQ(true, c.find("b", v));
  ASSERT_EQ(true, c.find("k", v));
  ASSERT_EQ(10, c.size());
}

TEST(NotTrashTests, RemoveFromBeginningOfChain)
{
  HashTableCollection<string,double> c;
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
  HashTableCollection<string,double> c;
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
  c.remove("b");
  ASSERT_EQ(false, c.find("b", v));
  ASSERT_EQ(true, c.find("c", v));
  ASSERT_EQ(true, c.find("k", v));
  ASSERT_EQ(10, c.size());
}

TEST(NotTrashTests, TestREEEEEEhash)
{
  HashTableCollection<string,double> c;
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
  c.add("l", 10);
  ASSERT_EQ(12, c.size());
  c.add("m", 20);
  ASSERT_EQ(13, c.size());
  c.add("n", 30);
  ASSERT_EQ(14, c.size());
  c.add("o", 30);
  c.add("p", 10);
  c.add("q", 10);
  c.add("r", 10);
  c.add("s", 10);
  c.add("t", 10);
  c.add("u", 10);
  c.add("v", 20);
  c.add("w", 10);
  c.add("x", 20);
  c.add("y", 30);
  c.add("z", 30);
  c.add("aa", 10);
  c.add("ab", 10);
  c.add("ac", 10);
  c.add("ad", 10);
  c.add("ae", 10);
  c.add("af", 10);
  c.add("ag", 20);
  ASSERT_EQ(33, c.size());
}

TEST(NotTrashTests, CpyCon)
{ 
  HashTableCollection<string,int> c;
  c.add("w", 10);
  c.add("x", 20);
  c.add("y", 30);
  c.add("z", 30);
  c.add("aa", 10);
  c.add("ab", 10);
  c.add("ac", 10);
  c.add("ad", 10);
  HashTableCollection<string, int> d(c);

  ASSERT_EQ(d.size(), c.size());
}

TEST(NotTrashTests, AssignmentOp)
{ 
  HashTableCollection<string,int> c;
  c.add("w", 10);
  c.add("x", 20);
  c.add("y", 30);
  c.add("z", 30);
  c.add("aa", 10);
  c.add("ab", 10);
  c.add("ac", 10);
  c.add("ad", 10);
  HashTableCollection<string,int> d;
  d = c;
  
  ASSERT_EQ(d.size(), c.size());
}

TEST(NotTrashTests, AssignmentOpNotEmpty)
{ 
  HashTableCollection<string,int> c;
  c.add("w", 10);
  c.add("x", 20);
  c.add("y", 30);
  c.add("z", 30);
  c.add("aa", 10);
  c.add("ab", 10);
  c.add("ac", 10);
  c.add("ad", 10);
  HashTableCollection<string,int> d;
  d.add("as", 1341);
  d = c;
  ASSERT_EQ(d.size(), c.size());
}  

TEST(NotTrashTests, keys)
{
  HashTableCollection<string,int> c;
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
  HashTableCollection<string,int> c;
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
  c.add("l", 10);
  c.add("m", 20);
  c.add("n", 30);
  c.add("o", 30);
  c.add("p", 10);
  c.add("q", 10);
  c.add("r", 10);
  c.add("s", 10);
  c.add("t", 10);
  c.add("u", 10);
  c.add("v", 20);
  c.add("w", 10);
  c.add("x", 20);
  c.add("y", 30);
  c.add("z", 30);
  c.add("aa", 10);
  c.add("ab", 10);
  c.add("ac", 10);
  c.add("ad", 10);
  vector<string> k;
  c.keys(k);
  ASSERT_EQ(c.size(), k.size());
}
// Test ?
TEST(NotTrashTests, RemoveMoreElems) {
  HashTableCollection<string,int> c;
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
  HashTableCollection<string, int> c;
  c.add("a", 35413);
  c.add("b", 675);
  c.add("c", 3371);
  c.add("d", 5342674);
  c.add("e", 9416);
  c.add("f", 3641);
  c.add("g", 341432);
  c.add("h", 3671);
  c.add("i",19433);
  c.add("j", 134149);
  c.add("k", 31438);
  c.add("l", 38);
  HashTableCollection<string, int> d = c;
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

// Test 4
TEST(BasicListTest, SimpleRange) {
  HashTableCollection<int,string> c;
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
  HashTableCollection<string,int> c;
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

TEST(TestsFromBinSearchCollection, SortedAfterRemove)
{ 
  HashTableCollection<int, int> c;
  c.add(3, 30);
  c.add(1, 10);
  c.add(2, 20);
  c.add(4, 40);
  c.add(5, 50);
  
  vector<int> sorted_ks;
  c.sort(sorted_ks);
  for (int i = 0; i < int(sorted_ks.size()) -1; ++i)
    ASSERT_LE(sorted_ks[i], sorted_ks[i+1]);
  vector<int> sorted_ks2;
  c.sort(sorted_ks2); 
  for (int i = 0; i < int(sorted_ks2.size()) -1; ++i)
    ASSERT_LE(sorted_ks2[i], sorted_ks2[i+1]);
}

 
TEST(TestsFromBinSearchCollection, RemoveEdgeCases)
{
  HashTableCollection<string, int> c;
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
  HashTableCollection<int, int> c;
  
  vector<int> vs;
  c.find(0, 2500, vs);
  ASSERT_EQ(0, vs.size());
  c.add(1, 12);
  c.add(2, 2134);
  c.add(3, 231);
  c.add(4, 123);
  vector<int> ks;
  c.find(0, 2500, ks);
  ASSERT_EQ(4, ks.size());
}

TEST(TestsFromLinkedListCollection, AssignmentOperator)
{
  HashTableCollection<string, int> c;
  HashTableCollection<string, int> b;
  c.add("a", 13);
  c.add("b", 14);
  ASSERT_EQ(2, c.size());
  ASSERT_EQ(0, b.size());
  b = c;
  ASSERT_EQ(2, b.size());

  HashTableCollection<int, int> a;
  a.add(0, 0);
  a.add(0, 1);
  a.add(0, 2);
  a.add(0, 3);
  a.add(0, 4);
  ASSERT_EQ(5, a.size());
  a = a;
  ASSERT_EQ(5, a.size());
}
// TODO: ... additional tests ...

int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

