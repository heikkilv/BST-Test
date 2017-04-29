#ifndef AVLTREE_HH
#define AVLTREE_HH

struct AVLNode
{
    int key_;
    int balance_;
    AVLNode* parent_;
    AVLNode* left_;
    AVLNode* right_;

    AVLNode(int key) :
        key_{ key },
        balance_{ 0 },
        parent_{ nullptr },
        left_{ nullptr },
        right_{ nullptr } {}
};

class AVLTree
{
public:
    AVLTree();
    ~AVLTree();

    int nodes() const;
    int height() const;
    int height(AVLNode* node) const;

    void clear();

    AVLNode* maximum() const;
    AVLNode* maximum(AVLNode* node) const;
    AVLNode* minimum() const;
    AVLNode* minimum(AVLNode* node) const;

    AVLNode* successor(AVLNode* node) const;
    AVLNode* predecessor(AVLNode* node) const;

    bool isInTree(AVLNode* node) const;

    AVLNode* search(int key) const;
    void insertNode(AVLNode* node);
    void deleteNode(AVLNode* node);

    void print() const;

private:
    AVLNode* root_;
    int nodes_;

    void insertBalance(AVLNode* node, int balance);
    void deleteBalance(AVLNode* node, int balance);
    AVLNode* rotateLeft(AVLNode* x);
    AVLNode* rotateLeftRight(AVLNode* x);
    AVLNode* rotateRight(AVLNode* x);
    AVLNode* rotateRightLeft(AVLNode* x);
    void replace(AVLNode* target, AVLNode* source);
};

#endif // AVLTREE_HH
