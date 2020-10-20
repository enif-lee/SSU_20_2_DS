#include "iostream"
#include <cmath>
#include <cstdlib>

using namespace std;

template<typename T>
class IQueue {
public:
    virtual void enqueue(T e) = 0;
    virtual T dequeue() = 0;
    virtual bool isEmpty() = 0;
    virtual bool isFull() = 0;
    virtual void peek() = 0;
    virtual int size() = 0;
    virtual void display() = 0;
};


template<typename T>
class CircularQueue : public IQueue<T>{
protected:
    int MaxSize = 0;
    T *items;
    int front = 0, rear = 0;
    string name = "QUEUE";

    void moveForward(int& index){
        index = (index + 1) % MaxSize;
    }
    void moveBackward(int& index){
        index = (index - 1 + MaxSize) % MaxSize;
    }

public:
    CircularQueue (int maxSize) {
        MaxSize = maxSize;
        items = (T *) malloc(sizeof(T) * maxSize);
    }

    virtual void enqueue(T e) {
        if (isFull())
            return;
        moveForward(rear);
        items[rear] = e;
    }

    virtual T dequeue() {
        if (isEmpty())
            return 0;

        moveForward(front);
        return items[front];
    }

    virtual bool isEmpty() override {
        return rear == front;
    }

    virtual bool isFull() override {
        return front == (rear + 1) % MaxSize;
    }

    void peek() override {
        if (!isEmpty())
            moveForward(front);
    }

    int size() override {
        return fmax(rear, front) - fmin(rear, front);
    }

    void display() override {
        string result;
        result = name;
        cout << "[" << result << "] : ";
        if (isEmpty()) {
            cout << "EMPTY";
            return;
        }

        for (int i = (front + 1) % MaxSize; i <= rear; i = (i + 1) % MaxSize) {
            cout << items[i] << (i != rear ? ", " : "");
        }
        cout << endl;
    }
};

template <typename T>
class CircularDeque : public CircularQueue<T>
{


public:
    CircularDeque(int maxSize) : CircularQueue<T>(maxSize) {
        this->name = "DEQUE";
    }

    void addFront(T item) {
        if (this->isFull())
            return;
        this->items[this->front] = item;
        this->moveBackward(this->front);
    }

    T deleteFront() {
        return this->dequeue();
    }

    T getFront() {
        if (this->isEmpty())
            return 0;

        return this->items[(this->front + 1) % this->MaxSize];
    }

    void addRear(T item) {
        this->enqueue(item);
    }

    T deleteRear() {
        if (this->isEmpty())
            return 0;

        T item = this->items[this->rear];
        this->moveBackward(this->rear);
        return item;

    }
    T getRear() {
        if (this->isEmpty())
            return 0;

        return this->items[this->rear];
    }
};

void solution() {
    CircularDeque<int> queue = CircularDeque<int>(100);

    queue.enqueue(1);
    queue.addRear(2);
    queue.addFront( 3);
    queue.display();
    queue.deleteFront();
    queue.deleteRear();
    queue.display();
    queue.dequeue();
    queue.display();
}