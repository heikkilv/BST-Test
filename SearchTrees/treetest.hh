// TreeTest class that provides the test functionality to the binary search tree test program
//
// Ville Heikkilä

#ifndef TREETEST_HH
#define TREETEST_HH

#include "randomvalue.hh"
#include "treetesthelper.hh"
#include <map>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

// Test parameters
//  name_: the test name
//  bst_: whether the standard BST will be included in the testing
//  insert_: how the order of the numbers inserted in the first phase is chosen
//  delete:: how the order of the numbers deleted in the first deletion phase is chosen
struct Test
{
    std::string name_;
    bool bst_;
    RandomType insert_;
    RandomType delete_;
};

// The prepared test parameters
const std::vector<Test> TEST_LIST
{
    { "A", false, RandomType::ordered, RandomType::ordered },
//    { "B", true, RandomType::nearlyOrdered, RandomType::uniform },
//    { "C", true, RandomType::uniform, RandomType::ordered },
//    { "D", false, RandomType::ordered, RandomType::uniform },
//    { "E", true, RandomType::nearlyOrdered, RandomType::ordered },
    { "F", true, RandomType::uniform, RandomType::uniform }
};

class TreeTest
{
public:
    TreeTest();

    // Runs the tests with the given value of n
    std::vector<TestTime> test(int n);

private:
    std::tuple<rbt_tree, avl_tree, aa_tree, bst_tree, map_tree> trees_;
};

#endif // TREETEST_HH
