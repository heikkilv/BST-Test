// The main program for the binary search tree test
//
// Ville Heikkilä

#include <iostream>
#include <vector>
#include "bstnode.hh"
#include "bstnode_metadata.hh"

int main(int argc, char *argv[])
{
    BSTNode<int, int> node1{1, 5};
    BSTNode<int, int> node2{2, 2, node1.getPointer(), nullptr, nullptr};
    BSTNode<int, int> node3{3, 6, node2.getPointer(), node1.getPointer(), node2.getPointer()};
    std::cout << node1 << std::endl;
    std::cout << node2 << std::endl;
    std::cout << node3 << std::endl;

    BSTNodeMetadata<int, int, bool> node4{1, 5};
    BSTNodeMetadata<int, int, bool> node5{2, 2, true, node4.getPointer(), nullptr, nullptr};
    BSTNodeMetadata<int, int, bool> node6{3, 6, true, node5.getPointer(), node4.getPointer(), node5.getPointer()};
    std::cout << node4 << std::endl;
    std::cout << node5 << std::endl;
    std::cout << node6 << std::endl;

    std::cout << "Command line:" << std::endl;
    for (auto& argument : std::vector<char*>(argv, argv + argc))
        std::cout << argument << " ";
    std::cout << std::endl;
    return EXIT_SUCCESS;
}
