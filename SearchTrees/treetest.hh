#ifndef TREETEST_HH
#define TREETEST_HH

#include "aatree.hh"
#include "binarysearchtree.hh"
#include "avltree.hh"
#include "randomvalue.hh"
#include "redblacktree.hh"
#include <string>
#include <vector>

struct Test
{
    std::string name_;
    bool bst_;
    RandomType insert_;
    RandomType delete_;
};

struct TestTime
{
    std::string tree_;
    std::string test_;
    int n_;
    int height1_;
    int height2_;
    int height3_;
    int insert1_;
    int insert2_;
    int delete1_;
    int delete2_;
    int search1a_;
    int search1b_;
    int search2a_;
    int search2b_;
    int search3a_;
    int search3b_;
    int total_;
};

const std::vector<Test> TEST_LIST
{
    { "A", false, RandomType::ordered, RandomType::ordered },
    { "B", true, RandomType::nearlyOrdered, RandomType::uniform },
    { "C", true, RandomType::uniform, RandomType::ordered },
    { "D", false, RandomType::ordered, RandomType::uniform },
    { "E", true, RandomType::nearlyOrdered, RandomType::ordered },
    { "F", true, RandomType::uniform, RandomType::uniform }
};

void printTestHeader();
void printTestTime(const TestTime& test);

std::vector<TestTime> takeAverages(const std::vector<TestTime>& testTimes);

class TreeTest
{
public:
    TreeTest();

    std::vector<TestTime> test(int n);

private:
    BinarySearchTree bstTree_;
    RedBlackTree rbTree_;
    AVLTree avlTree_;
    AATree aaTree_;

    int insertBST(const std::vector<int>& values);
    int insertRB(const std::vector<int>& values);
    int insertAVL(const std::vector<int>& values);
    int insertAA(const std::vector<int>& values);

    int searchBST(const std::vector<int>& values) const;
    int searchRB(const std::vector<int>& values) const;
    int searchAVL(const std::vector<int>& values) const;
    int searchAA(const std::vector<int>& values) const;

    int deleteBST(const std::vector<int>& values);
    int deleteRB(const std::vector<int>& values);
    int deleteAVL(const std::vector<int>& values);
    int deleteAA(const std::vector<int>& values);
};

#endif // TREETEST_HH
