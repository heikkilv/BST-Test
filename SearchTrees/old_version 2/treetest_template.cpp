#ifndef TREETEST_TEMPLATE_CPP
#define TREETEST_TEMPLATE_CPP

#include "timer.hh"
#include "treetest.hh"
#include <iostream>
#include <utility>
#include <vector>

struct substitution_failure
{};

template<typename T>
struct substitution_succeeded : std::true_type
{};

template<>
struct substitution_succeeded<substitution_failure> : std::false_type
{};

template<typename T>
struct get_height_result
{
private:
    template<typename X>
    static auto check(X const& x) -> decltype(x.height());
    static substitution_failure check(...);
public:
    using type = decltype(check(std::declval<T>()));
};

template<typename T>
struct has_height : substitution_succeeded<typename get_height_result<T>::type>
{};

template<typename T>
constexpr bool Has_height()
{
    return has_height<T>::value;
}

template<typename Container, bool C = Has_height<Container>()>
struct HeightStruct
{
    int height_;
    HeightStruct<Container, C>(const Container& container) : height_{ container.height() } {}
};

template<typename Container>
struct HeightStruct<Container, false>
{
    int height_;
    HeightStruct<Container, false>(...) : height_{ -1 } {}
};

template<typename Container>
int getHeight(const Container& container)
{
    HeightStruct<Container, Has_height<Container>()> heightStruct{ container };
    return heightStruct.height_;
}

template<typename Container>
ContainerDescription getDescription()
{
    if (std::is_same<Container, rbt_tree>::value)
    {
        return ContainerDescription{ "Red Black Tree", "RBT", true };
    }
    else if (std::is_same<Container, avl_tree>::value)
    {
        return ContainerDescription{ "AVL Tree", "AVL", true };
    }
    else if (std::is_same<Container, aa_tree>::value)
    {
        return ContainerDescription{ "AA Tree", "AA", true };
    }
    else if (std::is_same<Container, bst_tree>::value)
    {
        return ContainerDescription{ "Binary Search Tree", "BST", false };
    }
    else if (std::is_same<Container, map_tree>::value)
    {
        return ContainerDescription{ "std::map", "MAP", true };
    }
    else
    {
        return ContainerDescription{ "Unknown Container", "---", false };
    }
}

template<typename Container, typename Key, typename Value>
int insertValues(Container& container, const std::vector<Key>& keys,
                 const std::vector<Value>& values)
{
    if (keys.size() != values.size())
    {
        return -1;
    }
    size_t length{ keys.size() };

    Timer timer;
    for (size_t i{ 0 }; i < length; ++i)
    {
        container.insert(std::pair<Key, Value>{ keys[i], values[i] });
    }
    double duration{ timer.elapsed() };

    if (VERBOSE)
    {
        std::cout << "Inserted " << keys.size() << " to ";
        std::cout << getDescription<Container>().name_ << std::endl;
        std::cout << "Time duration: " << duration << " ms" << std::endl;
        std::cout << getDescription<Container>().name_;
        std::cout << " contains " << container.size() << " nodes. ";
        std::cout << "Tree height is " << getHeight(container) << std::endl;
        std::cout << std::endl;
    }

    return static_cast<int>(duration);
}

template<typename Container, typename Key>
int searchValues(Container& container, const std::vector<Key>& keys)
{
    Timer timer;
    for (auto key : keys)
    {
        container.find(key);
    }
    double duration{ timer.elapsed() };

    if (VERBOSE)
    {
        std::cout << "Searched " << keys.size() << " values from ";
        std::cout << getDescription<Container>().name_ << std::endl;
        std::cout << "Time duration: " << duration << " ms" << std::endl;
        std::cout << std::endl;
    }

    return static_cast<int>(duration);
}

template<typename Container, typename Key>
int deleteValues(Container& container, const std::vector<Key>& keys)
{
    Timer timer;
    for (auto key : keys)
    {
        container.erase(key);
    }
    double duration{ timer.elapsed() };

    if (VERBOSE)
    {
        std::cout << "Deleted " << keys.size() << " from ";
        std::cout << getDescription<Container>().name_ << std::endl;
        std::cout << "Time duration: " << duration << " ms" << std::endl;
        std::cout << getDescription<Container>().name_;
        std::cout << " contains " << container.size() << " nodes. ";
        std::cout << "Tree height is " << getHeight(container) << std::endl;
        std::cout << std::endl;
    }

    return static_cast<int>(duration);
}

template<typename Container>
TestTime runTest(Container& container, const TestData& testData)
{
    TestTime newTest;
    newTest.n_ = 0;

    if (testData.bst or getDescription<Container>().balanced_)
    {
        newTest.test_ = testData.testName;
        newTest.n_ = testData.insertKeys1.size();

        std::cout << std::setw(9) << " " << getDescription<Container>().name_ << std::endl;
        container.clear();
        newTest.tree_ = getDescription<Container>().identifier_;
        newTest.insert1_ = insertValues(container, testData.insertKeys1, testData.insertData1);
        newTest.height1_ = getHeight(container);
        newTest.search1a_ = searchValues(container, testData.searchKeys1);
        newTest.search1b_ = searchValues(container, testData.searchKeysAll);
        newTest.delete1_ = deleteValues(container, testData.deleteKeys1);
        newTest.height2_ = getHeight(container);
        newTest.search2a_ = searchValues(container, testData.searchKeys2);
        newTest.search2b_ = searchValues(container, testData.searchKeysAll);
        newTest.insert2_ = insertValues(container, testData.insertKeys2, testData.insertData2);
        newTest.height3_ = getHeight(container);
        newTest.search3a_ = searchValues(container, testData.searchKeys3);
        newTest.search3b_ = searchValues(container, testData.searchKeysAll);
        newTest.delete2_ = deleteValues(container, testData.deleteKeys2);
        newTest.total_ = newTest.insert1_ + newTest.insert2_ +
                         newTest.delete1_ + newTest.delete2_ +
                         newTest.search1a_ + newTest.search2a_ + newTest.search3a_ +
                         newTest.search1b_ + newTest.search2b_ + newTest.search3b_;
    }

    return newTest;
}

template<typename TupleType>
void runTest_for_each(TupleType&&,
                      std::integral_constant<size_t, std::tuple_size<typename std::remove_reference<TupleType>::type >::value>,
                      std::vector<TestTime>&, const TestData&) {}

template<std::size_t I, typename TupleType,
         typename = typename std::enable_if<I != std::tuple_size<typename std::remove_reference<TupleType>::type>::value>::type >
void runTest_for_each(TupleType&& t, std::integral_constant<size_t, I>,
                      std::vector<TestTime>& tests, const TestData& testData)
{
    auto newTest = runTest(std::get<I>(t), testData);
    if (newTest.n_ > 0)
    {
        tests.push_back(newTest);
    }
    runTest_for_each(std::forward<TupleType>(t),
                     std::integral_constant<size_t, I+1>(), tests, testData);
}

template<typename TupleType>
void runTest_for_each(TupleType&& t, std::vector<TestTime>& tests, const TestData& testData)
{
    runTest_for_each(std::forward<TupleType>(t), std::integral_constant<size_t, 0>(), tests, testData);
}

#endif // TREETEST_TEMPLATE_CPP
