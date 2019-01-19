//
// test_bst.cpp
// CSE 100 Project 1
//
// A BST tester using Catch unit testing framework.
//
// ATTENTION: This is not an exchaustive test suite and
// passing all tests does not guarantee full score on the
// project. You may want to add your own test cases by
// following the examples given.
// 
// Last modified by Arman Massoudian on 01/18/2019
//

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <algorithm>
#include <vector>
#include <string>

#include "../src/BST.hpp"

using namespace std;

/**
 * Tests inserting elements from a vector into a BST.
 *
 * Parameters:
 *     bst - the BST to insert elements into
 *     v - vector whose elements are to be inserted
 *     expected_height - the expected height of the BST after inserting elements
 */
template <typename T>
void test_bst(BST<T> &bst, vector<T> v, unsigned int expected_height) {
    INFO("Inserting elements into BST");

    for (T i : v) REQUIRE(bst.insert(i));
    for (T i : v) CHECK(*(bst.find(i)) == i);

    CHECK(bst.height() == expected_height);

    INFO("Testing inorder traversal with BSTIterator");

    sort(v.begin(), v.end());
    auto it = bst.begin();
    auto end = bst.end();

    for (T i : v) {
        REQUIRE(*(it++) == i);
    }
    for (T i : v) {
        REQUIRE(*(bst.find(i)) == i);
    }

    while(it != bst.end())
	*(it++);
    REQUIRE(it == end);
}

TEST_CASE("Building BST with integers") {
    BST<int> bst;

    SECTION("adding one element to BST") {
        test_bst<int>(bst, vector<int>{1}, 1);
        REQUIRE_FALSE(bst.insert(1));
        REQUIRE(bst.find(0) == bst.end());
    }

    SECTION("adding elements in random order") {
        test_bst<int>(bst, vector<int>{10, 5, 15, 7, -2, 12}, 3);
        REQUIRE_FALSE(bst.insert(-2));
	bst.inorder();
    }
}

TEST_CASE("Building BST with strings") {
    BST<string> bst;

    SECTION("adding elements in random order") {
        test_bst(bst, vector<string>{"c", "a", "d", "b", "e", "f"}, 4);

        WARN("Calling BST::inorder(), ensure output is in ascending order");
	bst.inorder();
    }
}

TEST_CASE("Building BST with doubles") {
	BST<double> bst;

	SECTION("adding doubles randomly") {
	    test_bst<double>(bst, vector<double>{1.454, 1.643, 1.29, 4.5, 3.2, 32}, 4);
	    bst.inorder();
    }
}

TEST_CASE("EMPTY BST") {
	BST<int> bst;

	SECTION("no elements added") {
	    test_bst<int>(bst, vector<int>{}, 0);
	    bst.inorder();
   }
}

TEST_CASE("INORDER DEGENERATE TREE") {
	BST<int> bst;

        SECTION("TESTING DEGEN TREE"){
           test_bst<int>(bst, vector<int>{1, 2, 3, 7, 11, 12, 17}, 7);
           REQUIRE_FALSE(bst.insert(1));
           REQUIRE_FALSE(bst.insert(2));
           REQUIRE_FALSE(bst.insert(3));
           REQUIRE_FALSE(bst.insert(7));
           REQUIRE_FALSE(bst.insert(11));
           REQUIRE_FALSE(bst.insert(12));
           REQUIRE_FALSE(bst.insert(17));
	bst.inorder();
	}
}
	
