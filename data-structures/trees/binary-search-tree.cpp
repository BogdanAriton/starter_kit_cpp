#include "binary-search-tree.h"
#include <iostream>
#include <queue>
#include <algorithm>

int main()
{
    BST<int> myBSt;
    myBSt.insert(13);
    myBSt.insert(21);
    myBSt.insert(10);
    myBSt.insert(6);
    myBSt.insert(4);
    myBSt.insert(2);
    myBSt.insert(1);
    myBSt.insert(3);
    myBSt.insert(5);
    myBSt.insert(8);
    myBSt.insert(7);
    myBSt.insert(9);
    myBSt.insert(11);
    myBSt.insert(17);
    myBSt.insert(15);
    myBSt.insert(14);
    myBSt.insert(16);
    myBSt.insert(19);
    myBSt.insert(20);
    myBSt.insert(18);
    myBSt.insert(25);
    myBSt.insert(27);
    myBSt.insert(28);
    myBSt.insert(23);
    myBSt.insert(22);
    myBSt.insert(24);
    myBSt.insert(26);
    /// make it not balanced
    myBSt.insert(29);
    myBSt.insert(30);
    myBSt.insert(31);
    myBSt.insert(32);
    myBSt.insert(33);
    myBSt.insert(34);

    //myBSt.InOrder();
    //myBSt.PostOrder();
    //myBSt.PreOrder();
    //myBSt.LevelFirstOrder();
    int value = 13;
    std::cout << value << (myBSt.searchNode(value) ? " was found": " was not found") << '\n';
    std::cout << value << (myBSt.BFSearch(value) ? " was found": " was not found") << '\n';

    std::cout << value << " has depth of = " << myBSt.getDepthOf(value) << '\n';
    std::cout << value << " has hight of = " << myBSt.getHightOf(value) << '\n';
    std::cout << "The tree has hight of = " << myBSt.getHightOf() << '\n';

    std::cout << (myBSt.isTreeBalanced() ? "is balanced" : "not balanced" ) << '\n';

    myBSt.deleteNode(29);
    myBSt.deleteNode(30);
    myBSt.deleteNode(31);
    myBSt.deleteNode(32);
    myBSt.deleteNode(33);
    myBSt.deleteNode(34);

    std::cout << (myBSt.isTreeBalanced() ? "is balanced" : "not balanced" ) << '\n';
    //myBSt.InOrder();
}

template <typename Data>
void BST<Data>::insert(const Data& value)
{
    root = insertRec(root, value);
}

template <typename Data>
BST<Data>::Node* BST<Data>::insertRec(Node* node, const Data& value)
{
    if (node == nullptr)
    {
        Node* newNode = new Node(value);
        node = newNode;
        return node;
    }

    if (value < node->data) 
    {
        node->left = insertRec(node->left, value);
    }
    if (value > node->data)
    {
        node->right = insertRec(node->right, value);
    }
    if (value == node->data)
    {
        Node* newNode = new Node(value);
        node->left = newNode;
    }
    return node;
}

template <typename Data>
void BST<Data>::InOrder() const
{
    InOrderRec(root);
}

template <typename Data>
void BST<Data>::InOrderRec(const Node* node) const
{
    if (node == nullptr) return;
    InOrderRec(node->left);
    std::cout << node->data << '\n';
    InOrderRec(node->right);
}

template <typename Data>
void BST<Data>::PostOrder() const
{
    PostOrderRec(root);
}

template <typename Data>
void BST<Data>::PostOrderRec(const Node* node) const
{
    if (node == nullptr) return;
    PostOrderRec(node->left);
    PostOrderRec(node->right);
    std::cout << node->data << '\n';
}

template <typename Data>
void BST<Data>::PreOrder() const
{
    PreOrderRec(root);
}

template <typename Data>
void BST<Data>::PreOrderRec(const Node* node) const
{
    if (node == nullptr) return;
    std::cout << node->data << '\n';
    PreOrderRec(node->left);
    PreOrderRec(node->right);
}

template <typename Data>
void BST<Data>::LevelFirstOrder() const
{
    if (root == nullptr) return;
    std::queue<Node*> queuedNodes;
    Node* current = root;

    queuedNodes.push(current);
    
    while (!queuedNodes.empty())
    {
        Node* tempNode = queuedNodes.front();
        std::cout << tempNode->data << '\n';

        if (tempNode->left != nullptr) queuedNodes.push(tempNode->left);
        if (tempNode->right != nullptr) queuedNodes.push(tempNode->right);
        queuedNodes.pop();
    }
}

template <typename Data>
bool BST<Data>::BFSearch(const Data &value) const
{
    if (root == nullptr) return false;
    if (value == root->data) return true;

    std::queue<Node*> queuedNodes;
    Node* current = root;
    queuedNodes.push(current);

    while (!queuedNodes.empty())
    {
        if (queuedNodes.front()->data == value) return true;
        Node* tempNode = queuedNodes.front();
        if (tempNode->left != nullptr) queuedNodes.push(tempNode->left);
        if (tempNode->right != nullptr) queuedNodes.push(tempNode->right);
        queuedNodes.pop();
    }
    return false;
}

template <typename Data>
bool BST<Data>::searchNode(const Data &value) const
{
    return searchNodeRec(root, value);
}

template <typename Data>
bool BST<Data>::searchNodeRec(const Node* node, const Data &value) const
{
    if (node == nullptr)  return false;
    if (value == node->data) 
        return true;
    else if (value < node->data)
        return searchNodeRec(node->left, value);
    else
        return searchNodeRec(node->right, value);
}

template <typename Data>
BST<Data>::Node* BST<Data>::findMax(Node* node) const
{
    if (node->right == nullptr) return node;
    return findMax(node->right);
}

template <typename Data>
BST<Data>::Node* BST<Data>::findMin(Node* node) const
{
    if (node->left == nullptr) return node;
    return findMin(node->left);
}

template <typename Data>
int BST<Data>::getHightOf(const Data &value) const
{
    return nodeHeight(root, value);
}

template <typename Data>
int BST<Data>::nodeHeight(const Node* node, const Data &value) const
{
    if (node == nullptr) return -1; // null node has no hight
    return findHeight(getNode(node, value));
}

template <typename Data>
int BST<Data>::findHeight(const Node* node) const
{
    if (node == nullptr) return -1;
    return std::max(findHeight(node->left), findHeight(node->right)) + 1;
}

template <typename Data>
int BST<Data>::getDepthOf(const Data &value) const
{
    return nodeDepth(root, value);
}

template <typename Data>
int BST<Data>::nodeDepth(const Node* node, const Data &value) const
{
    if (node == nullptr) return -1; // null node has no depth
    if (value < node->data) return nodeDepth(node->left, value)+1;
    else if (value > node->data) return nodeDepth(node->right, value)+1;
    else return 0;
}

template <typename Data>
int BST<Data>::getHightOf() const
{
    return findHeight(root);
}

template <typename Data>
bool BST<Data>::isTreeBalanced() const
{
    int x = checkBalance(root);
    if ( x < 2 ) return true;
    return false;
}
template <typename Data>
int BST<Data>::checkBalance(const Node* node) const
{
    if (node == nullptr) return -1; // an null node has no left of right, thus is balanced by default

    int h1 = checkBalance(node->left)+1;
    int h2 = checkBalance(node->right)+1;
    //std::cout << "for node = " << node->data << " balance is " << h1 << " - " << h2 << " = " << abs(h1-h2) << '\n';

    if (abs(h1 - h2) >= 2) return std::max(h1, h2);
    else return abs(h1 - h2);
}

template <typename Data>
void BST<Data>::deleteNode(const Data &value)
{
    root = deleteNodeRec(root, value);
}

template <typename Data>
BST<Data>::Node* BST<Data>::deleteNodeRec(Node* node, const Data &value)
{
    if (node == nullptr) return node;
    else if ( value < node->data) node->left = deleteNodeRec(node->left, value);
    else if ( value > node->data) node->right = deleteNodeRec(node->right, value);
    else
    {
        if (node->left == nullptr && node->right == nullptr)
        {
            delete node;
            node = nullptr;
        }
        else if ( node->left == nullptr )
        {
            Node* temp = node;
            node = node->right;
            delete temp;
        }
        else if ( node->right == nullptr )
        {
            Node* temp = node;
            node = node->left;
            delete temp;
        }
        else
        {
            Node* maxLeft = findMax(node->left);
            node->data = maxLeft->data;
            node->left = deleteNodeRec(node->left, maxLeft->data);
        }
    }
    return node;
}

template <typename Data>
const BST<Data>::Node* BST<Data>::getNode(const Node* node, const Data &value) const
{
    if (node == nullptr)  return node;
    if (value == node->data) 
        return node;
    else if (value < node->data)
        return getNode(node->left, value);
    else
        return getNode(node->right, value);
}