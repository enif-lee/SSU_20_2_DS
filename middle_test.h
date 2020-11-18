#include "iostream"


using namespace std;

namespace middle_test {
    template<typename T>
    class IDeque {
    public:
        virtual void insertFront(T e) = 0;
        virtual T deleteFront() = 0;

        virtual void insertRear(T e) = 0;
        virtual T deleteRear() = 0;

        virtual T peekFront() = 0;
        virtual T peekRear() = 0;

        virtual void printDQ() = 0;
        virtual int DequeSize() = 0;
    };

    template<typename T>
    struct Node {
        Node *prev;
        Node *next;
        T value;

        void setPrev(Node *node) {
            node->next = this;
            this->prev = node;
        }

        void setNext(Node *node) {
            this->next = node;
            node->prev = this;
        }
    };

    template<typename T>
    class LinkedDeque : public IDeque<T>{
    protected:
        Node<T> *front = nullptr, *rear = nullptr;
    public:
        void insertFront(T e) override {
            auto node = new Node<T> {nullptr, nullptr, e};
            if (isEmpty())
                front = rear = node;
            else {
                node->setNext(front);
                front = node;
            }
        }

        T deleteFront() override {
            if (isEmpty())
                exit(-1);

            if (front == rear) {
                auto value = front->value;
                delete front;
                front = rear = nullptr;
                return value;
            }

            auto temp = front;
            auto value = front->value;

            front = front->next;
            front->prev = nullptr;
            delete temp;
            return value;
        }

        void insertRear(T e) override {
            auto node = new Node<T> {nullptr, nullptr, e};
            if (isEmpty())
                front = rear = node;
            else {
                node->setPrev(rear);
                rear = node;
            }
        }

        T deleteRear() override {
            if (isEmpty())
                exit(-1);

            if (front == rear) {
                auto value = rear->value;
                delete rear;
                front = rear = nullptr;
                return value;
            }

            auto temp = rear;
            auto value = rear->value;

            rear = rear->prev;
            rear->next = nullptr;
            delete temp;
            return value;
        }

        T peekFront() override {
            if (isEmpty())
                exit(-1);

            return front->value;
        }

        T peekRear() override {
            if (isEmpty())
                exit(-1);

            return rear->value;
        }

        void printDQ() override {
            cout << "DeQue : [ ";
            auto node = front;
            while(node != nullptr) {
                cout << node->value << " ";
                node = node->next;
            }
            cout << "]" << endl;
        }

        int DequeSize() override {
            if (isEmpty())
                return 0;

            int size = 0;
            auto node = front;
            while(node != nullptr) {
                size++;
                node = node->next;
            }

            return size;
        }

        bool isEmpty() {
            return front == nullptr;
        }

        virtual ~LinkedDeque() {
            if (isEmpty())
                return;

            auto node = front;
            while(node != nullptr) {
                auto next = node->next;
                delete node;
                node = next;
            }
        }

    };

    void solution() {
        auto dq = new LinkedDeque<char>();
        cout << "Front 삽입 A >> ";
        dq->insertFront('A');
        dq->printDQ();

        cout << "Front 삽입 B >> ";
        dq->insertFront('B');
        dq->printDQ();

        cout << "Rear 삽입 C >> ";
        dq->insertRear('C');
        dq->printDQ();

        cout << "Size of Deque = " << dq->DequeSize() << endl;

        cout << "Front 삭제 >> ";
        dq->deleteFront();
        dq->printDQ();

        cout << "Rear 삭제 >> ";
        dq->deleteRear();
        dq->printDQ();

        cout << "Rear 삽입 D >> ";
        dq->insertRear('D');
        dq->printDQ();

        cout << "Front 삽입 E >> ";
        dq->insertFront('E');
        dq->printDQ();

        cout << "Front 삽입 F >> ";
        dq->insertFront('F');
        dq->printDQ();

        cout << "Size of Deque = " << dq->DequeSize() << endl;

        cout << "peek Front item  : " << dq->peekFront() << endl;
        cout << "peek Rear item  : " << dq->peekRear() << endl;

        delete dq;
    }
}