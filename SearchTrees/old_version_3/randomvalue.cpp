// RandomValue class for choosing the used values for the binary search tree test program
//
// Ville Heikkilä

#include "randomvalue.hh"
#include <algorithm>
#include <chrono>
#include <random>
#include <iostream>

RandomValue::RandomValue(int max) :
    RandomValue{ 1, max }
{
}

RandomValue::RandomValue(int min, int max) :
    min_{ min },
    max_{ max },
    permutations_{ 0 }
{
    if (max_ < min_)
    {
        max_ = min_;
    }

    permutations_ = count() / 100;
}

int RandomValue::count() const
{
    return (max_ - min_ + 1);
}

std::vector<int> RandomValue::getValues(int n, RandomType type, bool distinct) const
{
    std::vector<int> values;
    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator{ seed };

    if (distinct)
    {
        std::vector<bool> check(count(), false);
        std::uniform_int_distribution<int> distribution(0, count() - 1);
        unsigned int nMax{ static_cast<unsigned int>(std::min(n, count())) };
        while (values.size() < nMax)
        {
            int index{ distribution(generator) };
            while (check[index])
            {
                index = distribution(generator);
            }
            values.push_back(min_ + index);
            check[index] = true;
        }
    }
    else
    {
        std::uniform_int_distribution<int> distribution(min_, max_);
        unsigned int nMax{ static_cast<unsigned int>(std::min(n, count())) };
        while (values.size() < nMax)
        {
            values.push_back(distribution(generator));
        }
    }

    if (type == RandomType::ordered)
    {
        std::sort(values.begin(), values.end());
    }
    else if (type == RandomType::nearlyOrdered)
    {
        std::sort(values.begin(), values.end());
        permutate(values);
    }
    else if (type == RandomType::reversed)
    {
        std::sort(values.begin(), values.end(), std::greater<int>());
    }

    return values;
}

std::vector<int> RandomValue::getValuesIn(int n, RandomType type, bool distinct,
                             const std::vector<int>& otherValues) const
{
    std::vector<int> values;
    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator{ seed };

    if (distinct)
    {
        std::vector<int> reference;
        for (auto value : otherValues)
        {
            reference.push_back(value);
        }

        while (static_cast<int>(values.size()) < n and not reference.empty())
        {
            std::uniform_int_distribution<int> distribution(0, reference.size()-1);
            int index{ distribution(generator) };
            values.push_back(reference[index]);
            reference.erase(reference.begin() + index);
        }
    }
    else
    {
        std::uniform_int_distribution<int> distribution(0, otherValues.size()-1);
        unsigned int nMax{ std::min(static_cast<unsigned int>(n), otherValues.size()) };
        while (values.size() < nMax)
        {
            values.push_back(otherValues[distribution(generator)]);
        }
    }

    if (type == RandomType::ordered)
    {
        std::sort(values.begin(), values.end());
    }
    else if (type == RandomType::nearlyOrdered)
    {
        std::sort(values.begin(), values.end());
        permutate(values);
    }
    else if (type == RandomType::reversed)
    {
        std::sort(values.begin(), values.end(), std::greater<int>());
    }

    return values;
}

std::vector<int> RandomValue::getValuesNotIn(int n, RandomType type, bool distinct,
                                const std::vector<int>& otherValues) const
{
    std::vector<int> values;
    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator{ seed };

    if (distinct)
    {
        std::vector<int> reference;
        for (int i{ min_ }; i <= max_; ++i)
        {
            reference.push_back(i);
        }
        for (auto value : otherValues)
        {
            auto iter{ std::find(reference.begin(), reference.end(), value) };
            if (iter != reference.end())
            {
                reference.erase(iter);
            }
        }

        while (static_cast<int>(values.size()) < n and not reference.empty())
        {
            std::uniform_int_distribution<int> distribution(0, reference.size()-1);
            int index{ distribution(generator) };
            values.push_back(reference[index]);
            reference.erase(reference.begin() + index);
        }
    }
    else
    {
        std::vector<int> reference;
        for (int i{ min_ }; i <= max_; ++i)
        {
            reference.push_back(i);
        }
        for (auto value : otherValues)
        {
            auto iter{ std::find(reference.begin(), reference.end(), value) };
            if (iter != reference.end())
            {
                reference.erase(iter);
            }
        }

        std::uniform_int_distribution<int> distribution(0, reference.size()-1);
        unsigned int nMax{ std::min(static_cast<unsigned int>(n), reference.size()) };
        while (values.size() < nMax)
        {
            values.push_back(reference[distribution(generator)]);
        }
    }

    if (type == RandomType::ordered)
    {
        std::sort(values.begin(), values.end());
    }
    else if (type == RandomType::nearlyOrdered)
    {
        std::sort(values.begin(), values.end());
        permutate(values);
    }
    else if (type == RandomType::reversed)
    {
        std::sort(values.begin(), values.end(), std::greater<int>());
    }

    return values;
}

void RandomValue::permutate(std::vector<int>& values) const
{
    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator{ seed };
    std::uniform_int_distribution<int> distribution1{ 0, static_cast<int>(values.size()) - 1 };
    std::uniform_int_distribution<int> distribution2{ 1, static_cast<int>(values.size()) - 1 };

    for (int i{ 0 }; i < permutations_; ++i)
    {
        int k1{ distribution1(generator) };
        int k2{ (k1 + distribution2(generator)) % static_cast<int>(values.size()) };

        int temp{ values[k1] };
        values[k1] = values[k2];
        values[k2] = temp;
    }
}

void RandomValue::getTestValues(int n, RandomType insertType, RandomType deleteType,
                                std::vector<int>& insertValues1,
                                std::vector<int>& insertValues2,
                                std::vector<int>& searchValues1,
                                std::vector<int>& searchValues2,
                                std::vector<int>& searchValues3,
                                std::vector<int>& searchValuesAll,
                                std::vector<int>& deleteValues1,
                                std::vector<int>& deleteValues2) const
{
    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator{ seed };

    auto values{ getValues(2*n, RandomType::uniform, true) };

    std::vector<int> v1{ values.begin(), values.begin() + n };
    std::vector<int> v2{ values.begin(), values.begin() + n/2 };
    std::vector<int> v3{ values.begin() + n/2, values.begin() + n };
    std::vector<int> v4{ values.begin() + n, values.begin() + 3*n/2 };
    std::vector<int> v5{ values.begin() + n/2, values.begin() + 3*n/2 };

    insertValues1 = v1;
    searchValues1 = getValuesIn(10*n, RandomType::uniform, false, v1);
    deleteValues1 = v2;
    searchValues2 = getValuesIn(10*n, RandomType::uniform, false, v3);
    insertValues2 = v4;
    searchValues3 = getValuesIn(10*n, RandomType::uniform, false, v5);
    deleteValues2 = v5;
    searchValuesAll = getValuesIn(10*n, RandomType::uniform, false, values);

    std::shuffle(insertValues1.begin(), insertValues1.end(), generator);
    std::shuffle(deleteValues2.begin(), deleteValues2.end(), generator);

    if (insertType == RandomType::ordered)
    {
        std::sort(insertValues1.begin(), insertValues1.end());
    }
    else if (insertType == RandomType::nearlyOrdered)
    {
        std::sort(insertValues1.begin(), insertValues1.end());
        permutate(insertValues1);
    }
    else if (insertType == RandomType::reversed)
    {
        std::sort(insertValues1.begin(), insertValues1.end(), std::greater<int>());
    }

    if (deleteType == RandomType::ordered)
    {
        std::sort(deleteValues1.begin(), deleteValues1.end());
    }
    else if (deleteType == RandomType::nearlyOrdered)
    {
        std::sort(deleteValues1.begin(), deleteValues1.end());
        permutate(deleteValues1);
    }
    else if (deleteType == RandomType::reversed)
    {
        std::sort(deleteValues1.begin(), deleteValues1.end(), std::greater<int>());
    }
}
