#ifndef BSTNODE_BASE_HH
#define BSTNODE_BASE_HH

template<typename Key, typename Value>
class BSTNodeBase
{
  public:
    using key_type = Key;
    using value_type = Value;

    BSTNodeBase();

    BSTNodeBase(
        const key_type& key,
        const value_type& value
    );

    key_type getKey() const;
    value_type getValue() const;

    virtual operator std::string() const;

    friend class BSTTree;

  protected:
    key_type key_;
    value_type value_;
};

template<typename Key, typename Value>
std::ostream& operator<<(std::ostream& os, const BSTNodeBase<Key, Value>& node);

#include "bstnode_base.tpp"

#endif // BSTNODE_BASE_HH
