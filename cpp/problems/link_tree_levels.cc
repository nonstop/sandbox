/*
 * Given a tree-like structure link all nodes at the same level from left to right
 *
 * struct Node
 * {
 *  Node *left, *right;
 *  Node *next;
 * }
 *
 *         A
 *    B         C
 * D         E    F
 *
 * A.next is null
 * B.next is C
 * C.next is null
 * D.next is E
 * E.next is F
 * F.next is null
 *
 * and so on
 *
 */

#include <vector>
#include <iostream>

struct Node
{
    char c;
    Node* left;
    Node* right;
    Node* next;
};

Node* makeTree()
{
    Node* f = new Node{'f'};
    Node* e = new Node{'e'};
    Node* d = new Node{'d'};
    Node* c = new Node{'c', e, f};
    Node* b = new Node{'b', d};
    Node* a = new Node{'a', b, c};
    return a;
}

void printNode(const Node* n)
{
    if (!n) {
        return;
    }
    std::cout << '[' << n->c << ']';
    if (n->next) {
        std::cout << "->" << n->next->c;
    }
    std::cout << std::endl;
    printNode(n->left);
    printNode(n->right);
}

void appendNode(std::vector<Node*>& nodes, Node* n)
{
    if (n) {
        nodes.push_back(n);
    }
}

int main()
{
    Node* root = makeTree();
    printNode(root);
    std::vector<Node*> nodes = {root};
    while (!nodes.empty()) {
        std::vector<Node*> nextNodes;
        Node* prev = nodes[0];
        appendNode(nextNodes, prev->left);
        appendNode(nextNodes, prev->right);
        for (unsigned i = 1, sz = nodes.size(); i < sz; ++i) {
            prev->next = nodes[i];
            prev = nodes[i];
            appendNode(nextNodes, prev->left);
            appendNode(nextNodes, prev->right);
        }
        nodes = nextNodes;
    }
    printNode(root);
    return 0;
};
