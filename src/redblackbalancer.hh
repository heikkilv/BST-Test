#ifndef REDBLACKBALANCER_HH
#define REDBLACKBALANCER_HH

template <typename Key, typename Value, template<typename K, typename V> class Balancer>
class BSTTree;

template<typename Key, typename Value, typename BalanceType>
class BSTNode;

enum class NodeColor
{
    Red,
    Black
};

template<typename Key, typename Value>
class RedBlackBalancer
{
public:
    using key_type = Key;
    using mapped_type = Value;
    using balance_type = NodeColor;
    using tree_type = BSTTree<key_type, mapped_type, RedBlackBalancer>;
    using node_type = BSTNode<key_type, mapped_type, balance_type>;

    RedBlackBalancer(tree_type* tree) :
        tree_{ tree }
    {}

    RedBlackBalancer(RedBlackBalancer&& balancer) :
        tree_ { balancer.tree_ }
    {}

    ~RedBlackBalancer()
    {
    }

    static balance_type getDefaultBalance()
    {
        return NodeColor::Red;
    }

    void balanceAfterFind(node_type*)
    {
    }

    void balanceAfterInsert(node_type* node)
    {
        while (node->parent_->balance_ == NodeColor::Red)
        {
            if (node->parent_ == node->parent_->parent_->left_)
            {
                node_type* other{ node->parent_->parent_->right_ };
                if (other->balance_ == NodeColor::Red)
                {
                    node->parent_->balance_ = NodeColor::Black;
                    other->balance_ = NodeColor::Black;
                    node->parent_->parent_->balance_ = NodeColor::Red;
                    node = node->parent_->parent_;
                }
                else
                {
                    if (node == node->parent_->right_)
                    {
                        node = node->parent_;
                        rotateLeft(node);
                    }

                    node->parent_->balance_ = NodeColor::Black;
                    node->parent_->parent_->balance_ = NodeColor::Red;
                    rotateRight(node->parent_->parent_);
                }
            }
            else
            {
                node_type* other{ node->parent_->parent_->left_ };
                if (other->balance_ == NodeColor::Red)
                {
                    node->parent_->balance_ = NodeColor::Black;
                    other->color_ = NodeColor::Black;
                    node->parent_->parent_->balance_ = NodeColor::Red;
                    node = node->parent_->parent_;
                }
                else
                {
                    if (node == node->parent_->left_)
                    {
                        node = node->parent_;
                        rotateRight(node);
                    }

                    node->parent_->balance_ = NodeColor::Black;
                    node->parent_->parent_->balance_ = NodeColor::Red;
                    rotateLeft(node->parent_->parent_);
                }
            }
        }

        tree_->root_->balance_ = NodeColor::Black;
    }

    void balanceAfterErase(node_type*)
    {
    }

private:
    tree_type* tree_;

    RedBlackBalancer(const RedBlackBalancer&) = delete;
    RedBlackBalancer& operator=(const RedBlackBalancer&) = delete;
    RedBlackBalancer& operator=(RedBlackBalancer&&) = delete;

    void rotateLeft(node_type* node)
    {
        node_type* other{ node->right_ };

        node->right_ = other->left_;
        if (other->left_ != tree_->nil_)
        {
            other->left_->parent_ = node;
        }

        other->parent_ = node->parent_;
        if (node->parent_ == tree_->nil_)
        {
            tree_->root_ = other;
        }
        else if (node == node->parent_->left_)
        {
            node->parent_->left_ = other;
        }
        else
        {
            node->parent_->right_ = other;
        }

        other->left_ = node;
        node->parent_ = other;
    }

    void rotateRight(node_type* node)
    {
        node_type* other{ node->left_ };

        node->left_ = other->right_;
        if (other->right_ != tree_->nil_)
        {
            other->right_->parent_ = node;
        }

        other->parent_ = node->parent_;
        if (node->parent_ == tree_->nil_)
        {
            tree_->root_ = other;
        }
        else if (node == node->parent_->left_)
        {
            node->parent_->left_ = other;
        }
        else
        {
            node->parent_->right_ = other;
        }

        other->right_ = node;
        node->parent_ = other;
    }
};

#endif // REDBLACKBALANCER_HH
