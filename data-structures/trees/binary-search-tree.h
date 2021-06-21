/*

What is a bst (binary search tree)
A bst is a binary tree where all of the data are set in oreder (meaning that if we would visit all nodes from left to right we would get an ordered list - visiting using DFS - In-order)

                   7
        4                     13
    2       5           11          15
1              6    10      12   14

In-order will have the following result:
1 2 3 4 5 6 7 10 11 12 13 14 15

Let see how we can implement it:
*/

template <typename Data>
class BST
{
    struct Node
    {
        Data data{};
        Node *left = nullptr;
        Node *right = nullptr;

        Node(const Data& data)
        {
            this->data = data;
        }
    };

public:
    void insert(const Data &value);
    bool searchNode(const Data &value) const;
    void deleteNode(const Data &value);

    void InOrder() const;
    void PreOrder() const;
    void PostOrder() const;
    void LevelFirstOrder() const;
    bool BFSearch(const Data &value) const;

    int getDepthOf(const Data &value) const;
    int getHightOf(const Data &value) const;
    int getHightOf() const;

    bool isTreeBalanced() const;
    
private:
    bool searchNodeRec(const Node* node, const Data &value) const;
    Node* deleteNodeRec(Node* node, const Data &value);
    Node* insertRec(Node* node, const Data & value);
    void InOrderRec(const Node* node) const;
    void PreOrderRec(const Node* node) const;
    void PostOrderRec(const Node* node) const;

    Node* findMax(Node* node) const;
    Node* findMin(Node* node) const;

    // distance from node to leaf
    int nodeHeight(const Node* node, const Data &value) const;
    int findHeight(const Node* node) const;
    // distance from node to root
    int nodeDepth(const Node* node, const Data &value) const;
    int checkBalance(const Node*) const;

    const Node* getNode(const Node* node, const Data &value) const;

    Node *root = nullptr;
};