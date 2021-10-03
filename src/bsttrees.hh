#ifndef BSTTREES_HH
#define BSTTREES_HH

#include "bsttree.hh"
#include "redblackbalancer.hh"
#include "simplebstbalancer.hh"

template<typename Key, typename Value>
using SimpleBST = BSTTree<Key, Value, SimpleBSTBalancer>;

template<typename Key, typename Value>
using RedBlack = BSTTree<Key, Value, RedBlackBalancer>;

#endif // BSTTREES_HH
