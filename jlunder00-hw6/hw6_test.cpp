
#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "linked_list_collection.h"

using namespace std;


// Test 1
TEST(BasicListTest, CorrectSize) {
  LinkedListCollection<string,double> c;
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
  LinkedListCollection<string,double> c;
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
  LinkedListCollection<string,int> c;
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
  ASSERT_EQ(false, c.find("c", v));  
}

// Test 4
TEST(BasicListTest, SimpleRange) {
  LinkedListCollection<int,string> c;
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
  LinkedListCollection<string,int> c;
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

TEST(SortCasesTest, SelectionSort)
{
  LinkedListCollection<string,int> c;
  c.add("a", 10);
  c.add("e", 50);
  c.add("c", 30);
  c.add("b", 20);
  c.add("d", 40);

  c.selection_sort();

  vector<string> sorted_ks;  
  c.keys(sorted_ks);  
  ASSERT_EQ(5, sorted_ks.size());
  for (int i = 0; i < int(sorted_ks.size()) -1; ++i)
    ASSERT_LE(sorted_ks[i], sorted_ks[i+1]);
}

TEST(SortCasesTest, InsertionSort)
{
  LinkedListCollection<string,int> c;
  c.add("a", 10);
  c.add("e", 50);
  c.add("c", 30);
  c.add("b", 20);
  c.add("d", 40);

  c.insertion_sort();

  vector<string> sorted_ks;  
  c.keys(sorted_ks);  
  ASSERT_EQ(5, sorted_ks.size());
  for (int i = 0; i < int(sorted_ks.size()) -1; ++i)
    ASSERT_LE(sorted_ks[i], sorted_ks[i+1]);
}

TEST(SortCasesTest, SelectionSortDescAndSorted)
{
  LinkedListCollection<string,int> c;
  c.add("a", 10);
  c.add("b", 50);
  c.add("c", 30);
  c.add("d", 20);
  c.add("e", 40);

  c.selection_sort();

  vector<string> sorted_ks;  
  c.keys(sorted_ks);  
  ASSERT_EQ(5, sorted_ks.size());
  for (int i = 0; i < int(sorted_ks.size()) -1; ++i)
    ASSERT_LE(sorted_ks[i], sorted_ks[i+1]);
  
  LinkedListCollection<string,int> d;
  d.add("e", 10);
  d.add("d", 50);
  d.add("c", 30);
  d.add("b", 20);
  d.add("a", 40);

  d.selection_sort();

  vector<string> sorted_ks2;  
  d.keys(sorted_ks2);  
  ASSERT_EQ(5, sorted_ks2.size());
  for (int i = 0; i < int(sorted_ks2.size()) -1; ++i)
    ASSERT_LE(sorted_ks2[i], sorted_ks2[i+1]);
}



TEST(SortCasesTest, InsertionSortDescAndSorted)
{
  LinkedListCollection<string,int> c;
  c.add("a", 10);
  c.add("b", 50);
  c.add("c", 30);
  c.add("d", 20);
  c.add("e", 40);

  c.insertion_sort();

  vector<string> sorted_ks;  
  c.keys(sorted_ks);  
  ASSERT_EQ(5, sorted_ks.size());
  for (int i = 0; i < int(sorted_ks.size()) -1; ++i)
    ASSERT_LE(sorted_ks[i], sorted_ks[i+1]);
  
  LinkedListCollection<string,int> d;
  d.add("e", 10);
  d.add("d", 50);
  d.add("c", 30);
  d.add("b", 20);
  d.add("a", 40);

  d.insertion_sort();

  vector<string> sorted_ks2;  
  d.keys(sorted_ks2);  
  ASSERT_EQ(5, sorted_ks2.size());
  for (int i = 0; i < int(sorted_ks2.size()) -1; ++i)
    ASSERT_LE(sorted_ks2[i], sorted_ks2[i+1]);
}


TEST(SortCasesTest, SelectionSortZero)
{
  LinkedListCollection<string,int> c;
  c.selection_sort();
  vector<string> sorted_ks;  
  c.keys(sorted_ks);  
  for (int i = 0; i < int(sorted_ks.size()) -1; ++i)
    ASSERT_LE(sorted_ks[i], sorted_ks[i+1]);
}

TEST(SortCasesTest, InsertionSortZero)
{
  LinkedListCollection<string,int> c;
  c.insertion_sort();

  vector<string> sorted_ks;  
  c.keys(sorted_ks);  
  for (int i = 0; i < int(sorted_ks.size()) -1; ++i)
    ASSERT_LE(sorted_ks[i], sorted_ks[i+1]);
}

//Test to see if the list remains sorter after

//Test to see if the list remains sorter after
//removing an item and sorting again
TEST(BasicListTest, SortedAfterRemove)
{
  LinkedListCollection<int, int> c;
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

//Test Keys function
TEST(BasicListTest, SimpleKeys)
{
  LinkedListCollection<int, int> c;
  c.add(3, 30);
  c.add(1, 10);
  c.add(2, 20);
  c.add(4, 40);
  c.add(5, 50);
  
  vector<int> keys;
  c.keys(keys);
  ASSERT_EQ(5, keys.size());
  ASSERT_EQ(c.size(), keys.size());

}

//Test Copy Constructor
TEST(BasicListTest, CopyConstructor)
{
  LinkedListCollection<string, int> c;
  c.add("a", 10);
  c.add("e", 50);
  c.add("c", 30);
  c.add("b", 20);
  c.add("d", 40);
  
  LinkedListCollection<string, int> b(c);

  ASSERT_EQ(5, b.size());
  ASSERT_EQ(5, c.size());
  c.add("f", 34);
  ASSERT_LT(b.size(), c.size());

  
}

//Test operator=
//Additionally test the case where the user
//sets an object equal to itself and verify
//that it does not change
TEST(BasicListTest, AssignmentOperator)
{
  LinkedListCollection<string, int> c;
  LinkedListCollection<string, int> b;
  c.add("a", 13);
  c.add("b", 14);
  ASSERT_EQ(2, c.size());
  ASSERT_EQ(0, b.size());
  b = c;
  ASSERT_EQ(2, b.size());

  LinkedListCollection<int, int> a;
  a.add(0, 0);
  a.add(0, 1);
  a.add(0, 2);
  a.add(0, 3);
  a.add(0, 4);
  ASSERT_EQ(5, a.size());
  a = a;
  ASSERT_EQ(5, a.size());
}

//Test remove function when removing the last element in the list
//when removing an item not contained in the list,
//and removing when the list is length 0
TEST(BasicListTest, RemoveEdgeCases)
{
  LinkedListCollection<string, int> c;
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

//Testing the edge cases of range, calling
//the range find function when the list is empty
TEST(BasicListTest, RangeEdgeCases)
{
  LinkedListCollection<int, int> c;
  
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

// TODO: ... additional tests ...

int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

