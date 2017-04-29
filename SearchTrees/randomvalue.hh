#ifndef RANDOMVALUE_HH
#define RANDOMVALUE_HH

#include <vector>

enum class RandomType
{
    ordered,
    reversed,
    nearlyOrdered,
    uniform
};

class RandomValue
{
public:
    RandomValue(int max);
    RandomValue(int min, int max);

    int count() const;

    std::vector<int> getValues(int n, RandomType type, bool distinct = true) const;
    std::vector<int> getValuesIn(int n, RandomType type, bool distinct,
                                 const std::vector<int>& otherValues) const;
    std::vector<int> getValuesNotIn(int n, RandomType type, bool distinct,
                                    const std::vector<int>& otherValues) const;

    void permutate(std::vector<int>& values) const;

    void getTestValues(int n, RandomType insertType, RandomType deleteType,
                       std::vector<int>& insertValues1,
                       std::vector<int>& insertValues2,
                       std::vector<int>& searchValues1,
                       std::vector<int>& searchValues2,
                       std::vector<int>& searchValues3,
                       std::vector<int>& searchValuesAll,
                       std::vector<int>& deleteValues1,
                       std::vector<int>& deleteValues2) const;

private:
    int min_;
    int max_;
    int permutations_;
};

#endif // RANDOMVALUE_HH
