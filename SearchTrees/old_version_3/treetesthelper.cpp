#include "treetesthelper.hh"
#include <iomanip>
#include <iostream>
#include <vector>

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
