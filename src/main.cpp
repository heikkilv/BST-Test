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
    BSTNode<int, int, bool> node3{3, 6, true, node2.getPointer(), node1.getPointer(), node2.getPointer()};
    std::cout << node1 << std::endl;
    std::cout << node2 << std::endl;
    std::cout << node3 << std::endl;

    std::cout << "Command line:" << std::endl;
    for (auto& argument : std::vector<char*>(argv, argv + argc))
        std::cout << argument << " ";
    std::cout << std::endl;
    return EXIT_SUCCESS;
}
