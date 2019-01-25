// Helper function for TreeTest class
//
// Ville Heikkilä

#ifndef TREETESTHELPER_HH
#define TREETESTHELPER_HH

#include "aatree.hh"
#include "avltree.hh"
#include "binarysearchtree.hh"
#include "redblacktree.hh"
#include <map>
#include <string>
#include <vector>

const bool VERBOSE = false;

using key_type = int;
using data_type = std::string;
using bst_tree = BinarySearchTree<TreeNode<key_type, data_type>>;
using rbt_tree = RedBlackTree<RedBlackNode<key_type, data_type>>;
using avl_tree = AVLTree<AVLNode<key_type, data_type>>;
using aa_tree = AATree<AANode<key_type, data_type>>;
using map_tree = std::map<key_type, data_type>;

// A struct for storing the test results
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

struct TestData
{
    std::string testName;
    bool bst;
    std::vector<key_type> insertKeys1;
    std::vector<key_type> insertKeys2;
    std::vector<key_type> searchKeys1;
    std::vector<key_type> searchKeys2;
    std::vector<key_type> searchKeys3;
    std::vector<key_type> searchKeysAll;
    std::vector<key_type> deleteKeys1;
    std::vector<key_type> deleteKeys2;
    std::vector<data_type> insertData1;
    std::vector<data_type> insertData2;
};

struct ContainerDescription
{
    std::string name_;
    std::string identifier_;
    bool balanced_;
};

// Prints out the header line for the test results
void printTestHeader();
// Prints out the test results
void printTestTime(const TestTime& test);

// Calculates and returns the average results for similar tree, test type, and n
std::vector<TestTime> takeAverages(const std::vector<TestTime>& testTimes);

template<typename Container>
ContainerDescription getDescription();

template<typename Container>
int getHeight(const Container& container);

template<typename Container, typename Key, typename Value>
int insertValues(Container& container, const std::vector<Key>& keys,
                 const std::vector<Value>& values);

template<typename Container, typename Key>
int searchValues(Container& container, const std::vector<Key>& keys);

template<typename Container, typename Key>
int deleteValues(Container& container, const std::vector<Key>& keys);

template<typename Container>
TestTime runTest(Container& container, const TestData& testData);

template<typename TupleType>
void runTest_for_each(TupleType&&,
                      std::integral_constant<size_t, std::tuple_size<typename std::remove_reference<TupleType>::type >::value>,
                      std::vector<TestTime>&, const TestData&);

template<std::size_t I, typename TupleType,
         typename = typename std::enable_if<I != std::tuple_size<typename std::remove_reference<TupleType>::type>::value>::type >
void runTest_for_each(TupleType&& t, std::integral_constant<size_t, I>,
                      std::vector<TestTime>& tests, const TestData& testData);

template<typename TupleType>
void runTest_for_each(TupleType&& t, std::vector<TestTime>& tests, const TestData& testData);

#include "treetest_template.cpp"

#endif // TREETESTHELPER_HH
