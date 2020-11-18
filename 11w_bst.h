#include <iostream>
#include <queue>

namespace w11 {
    using namespace std;
    class BinaryNode {
        int data = 0;
        BinaryNode *left = nullptr;
        BinaryNode *right = nullptr;

    public:
        BinaryNode(int data) : data(data) {}

        void setData(int item) { data = item; }
        void setLeft(BinaryNode* node) { left = node; }
        void setRight(BinaryNode* node) { right = node; }
        int getData() { return data; }
        BinaryNode* getLeft() { return left; }
        BinaryNode* getRight() { return right; }

        bool isParent(BinaryNode* node) {
            if (node == nullptr)
                return false;

            return left == node || right == node;
        }
        bool isLeftEmpty() { return getLeft() == nullptr; }
        bool isRightEmpty() { return getRight() == nullptr; }

        bool isLeaf() { return left == right && left == nullptr; }

        int getNodeCounts() {
            return 1
                + (left == nullptr ? 0 : left->getNodeCounts())
                + (right == nullptr ? 0 : right->getNodeCounts());
        }
        
        int getHeight() {
            int leftHeight = left == nullptr ? 0 : left->getHeight();
            int rightHeight = right == nullptr ? 0 : right->getHeight();
            return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
        }
    };

    class BinaryTree {
        BinaryNode* root;
    public:
        BinaryTree() : root(nullptr) {}

        void setRoot(BinaryNode* node) { root = node; }
        BinaryNode* getRoot() { return root; }
        bool isEmpty() { return root == nullptr; }
        int getCount() {
            return isEmpty() ? 0 : root->getNodeCounts();
        }

        int getHeight() {
            return isEmpty() ? 0 : root->getHeight();
        }

        void printLevelOrder() {
            if (isEmpty())
                return;

            queue<BinaryNode*> nodes;

            cout << "[LEVEL ORDER] ";

            nodes.push(root);
            while (!nodes.empty()) {
                auto node = nodes.front();
                nodes.pop();
                cout << node->getData() << " ";

                auto left = node->getLeft();
                if (left != nullptr) nodes.push(left);

                auto right = node->getRight();
                if (right != nullptr) nodes.push(right);
            }

            cout << endl;
        }
    };

    class BinarySearchTree : public BinaryTree {
    public:
        void insert(int data) {
            insert(new BinaryNode(data));
        }

        void insert(BinaryNode * n) {
            if (isEmpty()) {
                setRoot(n);
                return;
            }

            auto node = getRoot();
            int newNodeData = n->getData();

            while (node != nullptr) {
                if (node->getData() == newNodeData)
                    return;

                if (node->getData() > newNodeData) {
                    if (node->getLeft() == nullptr) {
                        node->setLeft(n);
                        return;
                    } else node = node->getLeft();
                } else {
                    if (node->getRight() == nullptr) {
                        node->setRight(n);
                        return;
                    } else node = node->getRight();
                }
            }
        }

        void remove(int data) {
            remove(search(data));
        }

        void remove(BinaryNode* node) {
            remove(getParent(getRoot(), node), node);
        }

        BinaryNode* getParent(BinaryNode* tree, BinaryNode* node) {
            if (tree == nullptr || tree->isLeaf())
                return nullptr;
            
            if (tree->isParent(node))
                return tree;

            auto leftSearch = getParent(tree->getLeft(), node);
            return leftSearch != nullptr
                ? leftSearch
                : getParent(tree->getRight(), node);
        }


        void remove(BinaryNode* parent, BinaryNode* node) {
            if (node->isLeaf())
            {
                if (parent->getLeft() == node)
                    parent->setLeft(nullptr);
                else
                    parent->setRight(nullptr);
            } else if (node->isLeftEmpty() || node->isRightEmpty()) {
                auto child = node->isLeftEmpty() ? node->getRight() : node->getLeft();
                if (getRoot() == node)
                    setRoot(child);
                else if (parent->getLeft() == node)
                    parent->setLeft(child);
                else
                    parent->setRight(child);
            } else {
                BinaryNode* succp = node;
                BinaryNode* succ = node->getRight();
                while (succ->getLeft() != nullptr) {
                    succp = succ;
                    succ = succ->getLeft();
                }

                if( succp->getLeft() == succ )
                    succp->setLeft(succ->getRight());
                else
                    succp->setRight(succ->getRight());

                node->setData(succ->getData());
                node = succ;
            }

            delete node;
        }

        BinaryNode* search(int key) {
            return search(getRoot(), key);
        }

        BinaryNode* search(BinaryNode* node, int key) {
            if (node == nullptr)
                return nullptr;

            if (node->getData() == key)
                return node;

            if (key < node->getData())
                return search(node->getLeft(), key);
            else
                return search(node->getRight(), key);
        }
    };


    void solution() {
        BinarySearchTree bst;
        bst.insert(5);
        bst.insert(3);
        bst.insert(1);
        bst.insert(2);
        bst.insert(4);
        bst.insert(9);
        bst.insert(7);
        bst.insert(6);
        bst.insert(8);
        bst.printLevelOrder();
        bst.remove(9);
        bst.printLevelOrder();
    }

}