#include <cstdio>
#include "iostream"

using namespace std;

class Node {
private:
    int data = 0;
    Node *link = NULL;
public:
    Node(int data) : data(data) {
    }

    Node *getLink() {
        return link;
    }

    void setLink(Node *node) {
        link = node;
    }

    void display() {
        cout << " <" << data << ">";
    }

    bool hasData(int value) {
        return data == value;
    }

    void insertNext(Node *node) {
        node->setLink(link);
        setLink(node);
    }

    Node *removeNext() {
        auto temp = link;

        if (temp != NULL)
            setLink(link->getLink());

        return temp;
    }
};

class LinkedList {
private:
    Node org;
public:
    LinkedList() : org(0) {}

    virtual ~LinkedList() {
    }

    Node *getHead() { return org.getLink(); }

    bool isEmpty() { return getHead() == NULL; }

    void clear() {
        while (!isEmpty())
            delete remove(0);
    }


    // pos번째 항목을 반환함
    Node *getEntry(int pos) {
        Node *n = &org;
        for (int i = -1; i < pos; i++, n = n->getLink())
            if (n == NULL) break;
        return n;
    }

    // 리스트의 어떤 위치에 항목 삽입
    void insert(int pos, Node *n) {
        Node *prev = getEntry(pos - 1);
        if (prev != NULL)
            prev->insertNext(n);
    }

    // 리스트의 어떤 위치의 항목 삭제
    Node *remove(int pos) {
        Node *prev = getEntry(pos - 1);
        return prev->removeNext();
    }

    int size() {
        int count = 0;
        for (Node *p = getHead(); p != NULL; p = p->getLink()) {
            count++;
        }
        return count;
    }

    void display() {

        cout << "[전체 항목 수 = " << size() << "] : ";
        for (Node *p = getHead(); p != NULL; p = p->getLink())
            p->display();
        cout << endl;
    }

    void replace(int pos, Node *n) { // pos 위치의 요소 변경
        Node *prev = getEntry(pos - 1);
        if (prev != NULL) {
            delete prev->removeNext();
            prev->insertNext(n);
        }
    }

    void reverse() {
        Node *current = getHead();
        Node *pre = NULL;
        Node *prepre = NULL;

        while (current != NULL) {
            prepre = pre;
            pre = current;
            current = current->getLink();
            pre->setLink(prepre);
        }
        org.setLink(pre);
    }

    void merge(LinkedList *that) {
        while (!that->isEmpty()) {
            auto p = that->remove(0);
            insert(size(), p);
        }
    }

};