// TreeTest class that provides the test functionality to the binary search tree test program
//
// Ville Heikkilä

#include "treetest.hh"
#include "randomvalue.hh"
#include "timer.hh"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>

TreeTest::TreeTest() :
    trees_{}
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

        TestData testData;
        testData.testName = test.name_;
        testData.bst = test.bst_;
        generator.getTestValues(n, test.insert_, test.delete_,
                                testData.insertKeys1, testData.insertKeys2,
                                testData.searchKeys1, testData.searchKeys2,
                                testData.searchKeys3, testData.searchKeysAll,
                                testData.deleteKeys1, testData.deleteKeys2);
        for (auto value : testData.insertKeys1)
        {
            testData.insertData1.push_back(std::to_string(value));
        }
        for (auto value : testData.insertKeys2)
        {
            testData.insertData2.push_back(std::to_string(value));
        }

        // Run the current test for each container in tuple trees_.
        runTest_for_each(trees_, tests, testData);
    }
    return tests;
}
