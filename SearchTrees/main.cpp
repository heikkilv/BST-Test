// The main program for the binary search tree test
//
// Usage of the program: SearchTrees START_VALUE INTERVAL ITERATIONS REPEATS
//   where START_VALUE = the start value of n in the tests
//         INTERVAL    = the value by which n is increased in each iterations
//         ITERATIONS  = how many iterations are run
//         REPEATS     = how many times the test are repeated
//
//   example: SearchTrees 10000 5000 3 2
//     will run the tests twice with the values of n = 10000, 15000 and 20000
//
// Ville Heikkilä

#include "treetest.hh"
#include <iostream>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 5)
    {
        std::cout << "Usage: " << argv[0]
                  << " START_VALUE INTERVAL ITERATIONS REPEATS"
                  << std::endl;
        return EXIT_FAILURE;
    }

    int startValue{ atoi(argv[1]) };
    int interval{ atoi(argv[2]) };
    int iterations{ atoi(argv[3]) };
    int repeats{ atoi(argv[4]) };

    std::vector<int> testValues;
    for (int i{ 0 }; i < iterations; ++i)
    {
        testValues.push_back(startValue + i * interval);
    }

    TreeTest trees;
    std::vector<TestTime> testTimes;
    for (int i{ 0 }; i < repeats; ++i)
    {
        for (auto n : testValues)
        {
            std::cout << "Running tests with " << n << std::endl;
            auto newTests{ trees.test(n) };
            for (auto test : newTests)
            {
                testTimes.push_back(test);
            }
            std::cout << std::endl;
        }
    }

    std::cout << "Printing all test results:" << std::endl << std::endl;
    printTestHeader();
    for (auto time : testTimes)
    {
        printTestTime(time);
    }

    if (repeats > 1)
    {
        std::cout << std::endl
                  << "Printing the average test results after " << repeats << " repeats:"
                  << std::endl << std::endl;

        auto averageTimes{ takeAverages(testTimes) };

        printTestHeader();
        for (auto time : averageTimes)
        {
            printTestTime(time);
        }
    }

    return EXIT_SUCCESS;
}
