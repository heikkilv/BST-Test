// Red Black tree implementation
//
// Implementation is based on T.H. Cormen, C.E. Leiserson, R.L. Rivest, C. Stein,
// Introduction to algorithms, 3rd ed. MIT Press, Cambridge, MA, 2009, Chapter 13
//
// Ville Heikkilä

#ifndef REDBLACKTREE_HH
#define REDBLACKTREE_HH

enum class Color
{
    Red,
    Black
};

struct RedBlackNode
{
    int key_;
    Color color_;
    RedBlackNode* parent_;
    RedBlackNode* left_;
    RedBlackNode* right_;

    RedBlackNode(int key) :
        key_{ key },
        color_{ Color::Black },
        parent_{ nullptr },
        left_{ nullptr },
        right_{ nullptr } {}
};

class RedBlackTree
{
public:
    RedBlackTree();
    ~RedBlackTree();

    int nodes() const;
    int height() const;
    int height(RedBlackNode* node) const;
    bool isNull(RedBlackNode* node) const;

    void clear();

    RedBlackNode* maximum() const;
    RedBlackNode* maximum(RedBlackNode* node) const;
    RedBlackNode* minimum() const;
    RedBlackNode* minimum(RedBlackNode* node) const;

    RedBlackNode* successor(RedBlackNode* node) const;
    RedBlackNode* predecessor(RedBlackNode* node) const;

    bool isInTree(RedBlackNode* node) const;

    RedBlackNode* search(int key) const;
    void insertNode(RedBlackNode* node);
    void deleteNode(RedBlackNode* node);

    void print() const;

private:
    RedBlackNode* nil_;
    RedBlackNode* root_;
    int nodes_;

    void rotateLeft(RedBlackNode* x);
    void rotateRight(RedBlackNode* x);
    void insertFix(RedBlackNode* x);
    void deleteFix(RedBlackNode* x);
    void transplant(RedBlackNode* u, RedBlackNode* v);
};

#endif // REDBLACKTREE_HH
