// AA tree implementation
//
// Implementation is based on https://en.wikipedia.org/wiki/AA_tree (1.4.2017)
//
// Ville Heikkilä

#ifndef AATREE_HH
#define AATREE_HH

struct AANode
{
    int key_;
    int level_;
    AANode* parent_;
    AANode* left_;
    AANode* right_;

    AANode(int key) :
        key_{ key },
        level_{ 1 },
        parent_{ nullptr },
        left_{ nullptr },
        right_{ nullptr } {}
};

class AATree
{
public:
    AATree();
    ~AATree();

    int nodes() const;
    int height() const;
    int height(AANode* node) const;

    void clear();

    AANode* maximum() const;
    AANode* maximum(AANode* node) const;
    AANode* minimum() const;
    AANode* minimum(AANode* node) const;

    AANode* successor(AANode* node) const;
    AANode* predecessor(AANode* node) const;

    bool isInTree(AANode* node) const;

    AANode* search(int key) const;
    void insertNode(AANode* node);
    void deleteNode(AANode* node);

    void print() const;

private:
    AANode* root_;
    int nodes_;

    AANode* skew(AANode* node);
    AANode* split(AANode* node);
    AANode* insertNode(AANode* node, AANode* rootNode);
    AANode* deleteNode(AANode* node, AANode* rootNode);
    AANode* decreaseLevel(AANode* node);
};

#endif // AATREE_HH
