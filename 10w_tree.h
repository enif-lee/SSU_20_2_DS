namespace w10 {

#include "cstdio"
#include "cmath"

#include "iostream"

    using namespace std;

    class Node {
    public:
        char data;
        Node *left;
        Node *right;

        Node(char data) : data(data), left(NULL), right(NULL) {
        }

        void setLeftNode(char data) {
            left = new Node(data);
        }

        void setRightNode(char data) {
            right = new Node(data);
        }

        void display() {
            cout << data << " " << endl;
        }
    };

    void preOrder(Node *node) {
        if (node == NULL)
            return;

        node->display();
        preOrder(node->left);
        preOrder(node->right);
    }

    void inOrder(Node *node) {
        if (node == NULL)
            return;

        inOrder(node->left);
        node->display();
        inOrder(node->left);
    }

    void postOrder(Node *node) {
        if (node == NULL)
            return;

        inOrder(node->left);
        inOrder(node->left);
        node->display();
    }

    int count(Node *node) {
        if (node == NULL)
            return 0;
        return 1 + count(node->left) + count(node->right);
    }

    int depth(Node *node, int deep = 0) {
        if (node == NULL)
            return deep;

        auto rdeep = depth(node->right, deep + 1);
        auto ldeep = depth(node->left, deep + 1);

        return rdeep > ldeep ? rdeep : ldeep;
    }
}