#include "bstnode_utils.hh"
#include <fmt/core.h>

template<typename Node>
std::string getValueString(Node* node)
{
    if (node == nullptr)
    {
        return "";
    }
    return fmt::format("{} -> {}", node->getKey(), node->getValue());
}

template<typename Node>
std::string getLinkString(Node* node)
{
    std::string linkString;
    if (node == nullptr)
    {
        return linkString;
    }

    auto parent{node->getParent()};
    if (parent != nullptr)
    {
        linkString += fmt::format(", P: ({})", parent->getKey());
    }

    auto left{node->getLeft()};
    if (left != nullptr)
    {
        linkString += fmt::format(", L: ({})", left->getKey());
    }

    auto right{node->getRight()};
    if (right != nullptr)
    {
        linkString += fmt::format(", R: ({})", right->getKey());
    }

    return linkString;
}

template<typename Node>
std::string getMetadataString(Node* node)
{
    if (node == nullptr)
    {
        return "";
    }
    return fmt::format(" ({})", node->getMetadata());
}
