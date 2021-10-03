// The main program for the binary search tree test
//
// Ville Heikkilä

#include <iostream>
#include <vector>
#include "bstnode.hh"

int main(int argc, char *argv[])
{
    BSTNode<int, int, bool> node1;
    BSTNode<int, int, bool> node2{1, 2, true, node1.getPointer(), nullptr, nullptr};
    BSTNode<int, int, bool> node3{3, 6, true, node2.getPointer(), nullptr, nullptr};
    std::cout << node1.getKey() << " " << node1.getValue() << " " << node1.getParent() << std::endl;
    std::cout << node2.getKey() << " " << node2.getValue() << " " << node2.getParent()->getValue() << std::endl;
    std::cout << node3.getKey() << " " << node3.getValue() << " " << node3.getParent()->getValue() << std::endl;

    for (auto& argument : std::vector<char*>(argv, argv + argc))
        std::cout << argument << " ";
    std::cout << std::endl;
    return EXIT_SUCCESS;
}
