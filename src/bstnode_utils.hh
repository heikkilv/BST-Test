#ifndef BSTNODE_UTILS_HH
#define BSTNODE_UTILS_HH

#include <memory>
#include <string>

template<typename Node>
std::string getValueString(Node* node);

template<typename Node>
std::string getLinkString(Node* node);

template<typename Node>
std::string getMetadataString(Node* node);

#include "bstnode_utils.tpp"

#endif  // BSTNODE_UTILS_HH
