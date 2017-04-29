#include "treetest.hh"
#include "randomvalue.hh"
#include "timer.hh"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>

namespace {

const bool VERBOSE{ false };

}

void printTestHeader()
{
    std::cout << std::setw(5) << std::left << "tree"
              << std::setw(7) << std::left << "  n"
              << std::setw(5) << std::left << "test"
              << std::setw(7) << std::right << "h1"
              << std::setw(7) << std::right << "h2"
              << std::setw(7) << std::right << "h3"
              << std::setw(7) << std::right << "it1"
              << std::setw(7) << std::right << "st1a"
              << std::setw(7) << std::right << "st1b"
              << std::setw(7) << std::right << "dt1"
              << std::setw(7) << std::right << "st2a"
              << std::setw(7) << std::right << "st2b"
              << std::setw(7) << std::right << "it2"
              << std::setw(7) << std::right << "st3a"
              << std::setw(7) << std::right << "st3b"
              << std::setw(7) << std::right << "dt2"
              << std::setw(7) << std::right << "total"
              << std::endl;

    for (int i{ 0 }; i < 115; ++i)
    {
        std::cout << "-";
    }
    std::cout << std::endl;
}

void printTestTime(const TestTime& test)
{
    std::cout << std::setw(5) << std::left << (test.tree_ + ":")
              << std::setw(9) << std::left << (std::to_string(test.n_) + ":")
              << std::setw(3) << std::left << (test.test_ + ":")
              << std::setw(7) << std::right << test.height1_
              << std::setw(7) << std::right << test.height2_
              << std::setw(7) << std::right << test.height3_
              << std::setw(7) << std::right << test.insert1_
              << std::setw(7) << std::right << test.search1a_
              << std::setw(7) << std::right << test.search1b_
              << std::setw(7) << std::right << test.delete1_
              << std::setw(7) << std::right << test.search2a_
              << std::setw(7) << std::right << test.search2b_
              << std::setw(7) << std::right << test.insert2_
              << std::setw(7) << std::right << test.search3a_
              << std::setw(7) << std::right << test.search3b_
              << std::setw(7) << std::right << test.delete2_
              << std::setw(7) << std::right << test.total_
              << std::endl;
}

std::vector<TestTime> takeAverages(const std::vector<TestTime>& testTimes)
{
    std::vector<TestTime> averageTimes;
    for (auto test : testTimes)
    {
        bool found{ false };
        auto iter{ averageTimes.begin() };
        while (not found and iter != averageTimes.end())
        {
            if (test.tree_ == iter->tree_ and
                test.test_ == iter->test_ and
                test.n_ == iter->n_)
            {
                found = true;
            }
            ++iter;
        }

        if (found)
        {
            continue;
        }

        TestTime newTest;
        newTest.tree_ = test.tree_;
        newTest.test_ = test.test_;
        newTest.n_ = test.n_;
        newTest.height1_ = 0;
        newTest.height2_ = 0;
        newTest.height3_ = 0;
        newTest.insert1_ = 0;
        newTest.insert2_ = 0;
        newTest.delete1_ = 0;
        newTest.delete2_ = 0;
        newTest.search1a_ = 0;
        newTest.search1b_ = 0;
        newTest.search2a_ = 0;
        newTest.search2b_ = 0;
        newTest.search3a_ = 0;
        newTest.search3b_ = 0;
        newTest.total_ = 0;

        int count{ 0 };
        for (unsigned int i{ 0 }; i < testTimes.size(); ++i)
        {
            if (testTimes[i].tree_ == newTest.tree_ and
                testTimes[i].test_ == newTest.test_ and
                testTimes[i].n_ == newTest.n_)
            {
                ++count;
                newTest.height1_ += testTimes[i].height1_;
                newTest.height2_ += testTimes[i].height2_;
                newTest.height3_ += testTimes[i].height3_;
                newTest.insert1_ += testTimes[i].insert1_;
                newTest.insert2_ += testTimes[i].insert2_;
                newTest.delete1_ += testTimes[i].delete1_;
                newTest.delete2_ += testTimes[i].delete2_;
                newTest.search1a_ += testTimes[i].search1a_;
                newTest.search1b_ += testTimes[i].search1b_;
                newTest.search2a_ += testTimes[i].search2a_;
                newTest.search2b_ += testTimes[i].search2b_;
                newTest.search3a_ += testTimes[i].search3a_;
                newTest.search3b_ += testTimes[i].search3b_;
                newTest.total_ += testTimes[i].total_;
            }
        }

        if (count > 0)
        {
            newTest.height1_ /= count;
            newTest.height2_ /= count;
            newTest.height3_ /= count;
            newTest.insert1_ /= count;
            newTest.insert2_ /= count;
            newTest.delete1_ /= count;
            newTest.delete2_ /= count;
            newTest.search1a_ /= count;
            newTest.search1b_ /= count;
            newTest.search2a_ /= count;
            newTest.search2b_ /= count;
            newTest.search3a_ /= count;
            newTest.search3b_ /= count;
            newTest.total_ /= count;
        }

        averageTimes.push_back(newTest);
    }

    return averageTimes;
}

TreeTest::TreeTest() :
    bstTree_{},
    rbTree_{},
    avlTree_{},
    aaTree_{}
{
}

std::vector<TestTime> TreeTest::test(int n)
{
    RandomValue generator{ 10*n };
    std::vector<TestTime> tests;

    for (auto test : TEST_LIST)
    {
        std::cout << std::setw(9) << std::left << ("Test: " + test.name_ + ":")
                  << "Generating data" << std::endl;

        std::vector<int> insertValues1;
        std::vector<int> insertValues2;
        std::vector<int> searchValues1;
        std::vector<int> searchValues2;
        std::vector<int> searchValues3;
        std::vector<int> searchValuesAll;
        std::vector<int> deleteValues1;
        std::vector<int> deleteValues2;
        generator.getTestValues(n, test.insert_, test.delete_,
                                insertValues1, insertValues2,
                                searchValues1, searchValues2,
                                searchValues3, searchValuesAll,
                                deleteValues1, deleteValues2);

        TestTime newTest;
        newTest.test_ = test.name_;
        newTest.n_ = n;

        // Handle the test for Red Black Tree
        std::cout << std::setw(9) << " " << "Red Black Tree" << std::endl;
        rbTree_.clear();
        newTest.tree_ = "RBT";
        newTest.insert1_ = insertRB(insertValues1);
        newTest.height1_ = rbTree_.height();
        newTest.search1a_ = searchRB(searchValues1);
        newTest.search1b_ = searchRB(searchValuesAll);
        newTest.delete1_ = deleteRB(deleteValues1);
        newTest.height2_ = rbTree_.height();
        newTest.search2a_ = searchRB(searchValues2);
        newTest.search2b_ = searchRB(searchValuesAll);
        newTest.insert2_ = insertRB(insertValues2);
        newTest.height3_ = rbTree_.height();
        newTest.search3a_ = searchRB(searchValues3);
        newTest.search3b_ = searchRB(searchValuesAll);
        newTest.delete2_ = deleteRB(deleteValues2);
        newTest.total_ = newTest.insert1_ + newTest.insert2_ +
                         newTest.delete1_ + newTest.delete2_ +
                         newTest.search1a_ + newTest.search2a_ + newTest.search3a_ +
                         newTest.search1b_ + newTest.search2b_ + newTest.search3b_;
        tests.push_back(newTest);

        // Handle the test for AVL Tree
        std::cout << std::setw(9) << " " << "AVL Tree" << std::endl;
        avlTree_.clear();
        newTest.tree_ = "AVL";
        newTest.insert1_ = insertAVL(insertValues1);
        newTest.height1_ = avlTree_.height();
        newTest.search1a_ = searchAVL(searchValues1);
        newTest.search1b_ = searchAVL(searchValuesAll);
        newTest.delete1_ = deleteAVL(deleteValues1);
        newTest.height2_ = avlTree_.height();
        newTest.search2a_ = searchAVL(searchValues2);
        newTest.search2b_ = searchAVL(searchValuesAll);
        newTest.insert2_ = insertAVL(insertValues2);
        newTest.height3_ = avlTree_.height();
        newTest.search3a_ = searchAVL(searchValues3);
        newTest.search3b_ = searchAVL(searchValuesAll);
        newTest.delete2_ = deleteAVL(deleteValues2);
        newTest.total_ = newTest.insert1_ + newTest.insert2_ +
                         newTest.delete1_ + newTest.delete2_ +
                         newTest.search1a_ + newTest.search2a_ + newTest.search3a_ +
                         newTest.search1b_ + newTest.search2b_ + newTest.search3b_;
        tests.push_back(newTest);

        // Handle the test for AA Tree
        std::cout << std::setw(9) << " " << "AA Tree" << std::endl;
        aaTree_.clear();
        newTest.tree_ = "AA";
        newTest.insert1_ = insertAA(insertValues1);
        newTest.height1_ = aaTree_.height();
        newTest.search1a_ = searchAA(searchValues1);
        newTest.search1b_ = searchAA(searchValuesAll);
        newTest.delete1_ = deleteAA(deleteValues1);
        newTest.height2_ = aaTree_.height();
        newTest.search2a_ = searchAA(searchValues2);
        newTest.search2b_ = searchAA(searchValuesAll);
        newTest.insert2_ = insertAA(insertValues2);
        newTest.height3_ = aaTree_.height();
        newTest.search3a_ = searchAA(searchValues3);
        newTest.search3b_ = searchAA(searchValuesAll);
        newTest.delete2_ = deleteAA(deleteValues2);
        newTest.total_ = newTest.insert1_ + newTest.insert2_ +
                         newTest.delete1_ + newTest.delete2_ +
                         newTest.search1a_ + newTest.search2a_ + newTest.search3a_ +
                         newTest.search1b_ + newTest.search2b_ + newTest.search3b_;
        tests.push_back(newTest);

        if (not test.bst_)
        {
            continue;
        }

        // Handle the test for BST Tree
        std::cout << std::setw(9) << " " << "Binary Search Tree" << std::endl;
        bstTree_.clear();
        newTest.tree_ = "BST";
        newTest.insert1_ = insertBST(insertValues1);
        newTest.height1_ = bstTree_.height();
        newTest.search1a_ = searchBST(searchValues1);
        newTest.search1b_ = searchBST(searchValuesAll);
        newTest.delete1_ = deleteBST(deleteValues1);
        newTest.height2_ = bstTree_.height();
        newTest.search2a_ = searchBST(searchValues2);
        newTest.search2b_ = searchBST(searchValuesAll);
        newTest.insert2_ = insertBST(insertValues2);
        newTest.height3_ = bstTree_.height();
        newTest.search3a_ = searchBST(searchValues3);
        newTest.search3b_ = searchBST(searchValuesAll);
        newTest.delete2_ = deleteBST(deleteValues2);
        newTest.total_ = newTest.insert1_ + newTest.insert2_ +
                         newTest.delete1_ + newTest.delete2_ +
                         newTest.search1a_ + newTest.search2a_ + newTest.search3a_ +
                         newTest.search1b_ + newTest.search2b_ + newTest.search3b_;
        tests.push_back(newTest);
    }

    return tests;
}

int TreeTest::insertBST(const std::vector<int>& values)
{
    Timer timer;
    for (auto value : values)
    {
        bstTree_.insertNode(new TreeNode(value));
    }
    double duration{ timer.elapsed() };

    if (VERBOSE)
    {
        std::cout << "Inserted " << values.size() << " to Binary Search Tree" << std::endl;
        std::cout << "Time duration: " << duration << " ms" << std::endl;
        std::cout << "Binary Search Tree contains " << bstTree_.nodes() << " nodes. ";
        std::cout << "Tree height is " << bstTree_.height() << std::endl;
        std::cout << std::endl;
    }

    return static_cast<int>(duration);
}

int TreeTest::insertRB(const std::vector<int>& values)
{
    Timer timer;
    for (auto value : values)
    {
        rbTree_.insertNode(new RedBlackNode(value));
    }
    double duration{ timer.elapsed() };

    if (VERBOSE)
    {
        std::cout << "Inserted " << values.size() << " to Red Black Tree" << std::endl;
        std::cout << "Time duration: " << duration << " ms" << std::endl;
        std::cout << "Red Black Tree contains " << rbTree_.nodes() << " nodes. ";
        std::cout << "Tree height is " << rbTree_.height() << std::endl;
        std::cout << std::endl;
    }

    return static_cast<int>(duration);
}

int TreeTest::insertAVL(const std::vector<int>& values)
{
    Timer timer;
    for (auto value : values)
    {
        avlTree_.insertNode(new AVLNode(value));
    }
    double duration{ timer.elapsed() };

    if (VERBOSE)
    {
        std::cout << "Inserted " << values.size() << " to AVL Tree" << std::endl;
        std::cout << "Time duration: " << duration << " ms" << std::endl;
        std::cout << "AVL Tree contains " << avlTree_.nodes() << " nodes. ";
        std::cout << "Tree height is " << avlTree_.height() << std::endl;
        std::cout << std::endl;
    }

    return static_cast<int>(duration);
}

int TreeTest::insertAA(const std::vector<int>& values)
{
    Timer timer;
    for (auto value : values)
    {
        aaTree_.insertNode(new AANode(value));
    }
    double duration{ timer.elapsed() };

    if (VERBOSE)
    {
        std::cout << "Inserted " << values.size() << " to AA Tree" << std::endl;
        std::cout << "Time duration: " << duration << " ms" << std::endl;
        std::cout << "AA Tree contains " << aaTree_.nodes() << " nodes. ";
        std::cout << "Tree height is " << aaTree_.height() << std::endl;
        std::cout << std::endl;
    }

    return static_cast<int>(duration);
}

int TreeTest::searchBST(const std::vector<int>& values) const
{
    Timer timer;
    for (auto value : values)
    {
        bstTree_.search(value);
    }
    double duration{ timer.elapsed() };

    if (VERBOSE)
    {
        std::cout << "Searched " << values.size() << " values from Binary Search Tree" << std::endl;
        std::cout << "Time duration: " << duration << " ms" << std::endl;
        std::cout << std::endl;
    }

    return static_cast<int>(duration);
}

int TreeTest::searchRB(const std::vector<int>& values) const
{
    Timer timer;
    for (auto value : values)
    {
        rbTree_.search(value);
    }
    double duration{ timer.elapsed() };

    if (VERBOSE)
    {
        std::cout << "Searched " << values.size() << " values from Red Black Tree" << std::endl;
        std::cout << "Time duration: " << duration << " ms" << std::endl;
        std::cout << std::endl;
    }

    return static_cast<int>(duration);
}

int TreeTest::searchAVL(const std::vector<int>& values) const
{
    Timer timer;
    for (auto value : values)
    {
        avlTree_.search(value);
    }
    double duration{ timer.elapsed() };

    if (VERBOSE)
    {
        std::cout << "Searched " << values.size() << " values from AVL Tree" << std::endl;
        std::cout << "Time duration: " << duration << " ms" << std::endl;
        std::cout << std::endl;
    }

    return static_cast<int>(duration);
}

int TreeTest::searchAA(const std::vector<int>& values) const
{
    Timer timer;
    for (auto value : values)
    {
        aaTree_.search(value);
    }
    double duration{ timer.elapsed() };

    if (VERBOSE)
    {
        std::cout << "Searched " << values.size() << " values from AA Tree" << std::endl;
        std::cout << "Time duration: " << duration << " ms" << std::endl;
        std::cout << std::endl;
    }

    return static_cast<int>(duration);
}

int TreeTest::deleteBST(const std::vector<int>& values)
{
    Timer timer;
    for (auto value : values)
    {
        bstTree_.deleteNode(bstTree_.search(value));
    }
    double duration{ timer.elapsed() };

    if (VERBOSE)
    {
        std::cout << "Deleted " << values.size() << " from Binary Search Tree" << std::endl;
        std::cout << "Time duration: " << duration << " ms" << std::endl;
        std::cout << "Binary Search Tree contains " << bstTree_.nodes() << " nodes. ";
        std::cout << "Tree height is " << bstTree_.height() << std::endl;
        std::cout << std::endl;
    }

    return static_cast<int>(duration);
}

int TreeTest::deleteRB(const std::vector<int>& values)
{
    Timer timer;
    for (auto value : values)
    {
        rbTree_.deleteNode(rbTree_.search(value));
    }
    double duration{ timer.elapsed() };

    if (VERBOSE)
    {
        std::cout << "Deleted " << values.size() << " from Red Black Tree" << std::endl;
        std::cout << "Time duration: " << duration << " ms" << std::endl;
        std::cout << "Red Black Tree contains " << rbTree_.nodes() << " nodes. ";
        std::cout << "Tree height is " << rbTree_.height() << std::endl;
        std::cout << std::endl;
    }

    return static_cast<int>(duration);
}

int TreeTest::deleteAVL(const std::vector<int>& values)
{
    Timer timer;
    for (auto value : values)
    {
        avlTree_.deleteNode(avlTree_.search(value));
    }
    double duration{ timer.elapsed() };

    if (VERBOSE)
    {
        std::cout << "Deleted " << values.size() << " from AVL Tree" << std::endl;
        std::cout << "Time duration: " << duration << " ms" << std::endl;
        std::cout << "AVL Tree contains " << avlTree_.nodes() << " nodes. ";
        std::cout << "Tree height is " << avlTree_.height() << std::endl;
        std::cout << std::endl;
    }

    return static_cast<int>(duration);
}

int TreeTest::deleteAA(const std::vector<int>& values)
{
    Timer timer;
    for (auto value : values)
    {
        aaTree_.deleteNode(aaTree_.search(value));
    }
    double duration{ timer.elapsed() };

    if (VERBOSE)
    {
        std::cout << "Deleted " << values.size() << " from AA Tree" << std::endl;
        std::cout << "Time duration: " << duration << " ms" << std::endl;
        std::cout << "AA Tree contains " << aaTree_.nodes() << " nodes. ";
        std::cout << "Tree height is " << aaTree_.height() << std::endl;
        std::cout << std::endl;
    }

    return static_cast<int>(duration);
}
