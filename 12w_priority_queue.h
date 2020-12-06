#include "iostream"
#include "queue"
#include "functional"

using namespace std;

namespace w12 {
#define MAX_ELEMENT 100

    class HeapNode {
        int key;
    public:
        HeapNode(int key = 0) : key(key) {}

        virtual ~HeapNode() {
        }

        int getKey() { return key; }

        void setKey(int value) { key = value; }

        void display() { printf("\t%d", key); };
    };

    class MaxHeap {
        HeapNode node[MAX_ELEMENT];
        int size;

    public:
        MaxHeap() : size(0) {}

        bool isEmpty() { return size == 0; }

        bool isFull() { return size == MAX_ELEMENT; }

        HeapNode &getParent(int i) { return node[i / 2]; }

        HeapNode &getLeft(int i) { return node[i * 2]; }

        HeapNode &getRight(int i) { return node[i * 2 + 1]; }

        void insert(int key) {
            if (isFull()) return;

            int index = ++size;
            while (index != 1 && key > getParent(index).getKey()) {
                node[index] = getParent(index);
                index /= 2;
            }
            node[index].setKey(key);
        }

        HeapNode remove() {
            if (isEmpty()) return NULL;

            auto root = node[1];
            auto last = node[size--];

            int parent = 1;
            int child = 2;
            while (child <= size) {
                if (child < size && getLeft(parent).getKey() < getRight(parent).getKey())
                    child++;

                if (last.getKey() >= node[child].getKey()) break;

                node[parent] = node[child];
                parent = child;
                child *= 2;
            }

            node[parent] = last;
            return root;
        }

        HeapNode find() { return node[1]; }

        void display() {
            for (int i = 0, level = 1; i <= size; i ++) {
                if (i == level) {
                    cout << endl;
                    level *= 2;
                }
                node[i].display();
            }
        }
    };\

    void solution() {
        MaxHeap heap;
        heap.insert(10);
        heap.insert(10);
        heap.insert(10);
        heap.insert(10);
        heap.insert(10);
        heap.insert(10);
        heap.display();
    }
    void heapSortInc(int a[], int n) {
        priority_queue<int, vector<int>, greater<int>> minHeap;
        for (int i=0; i<n; ++i) minHeap.push(a[i]);

        for (int i=0; i<n; ++i) {
            a[i] = minHeap.top();
            minHeap.pop();
        }
    }

    void heapSortDec(int a[], int n) {
        priority_queue<int, vector<int>, less<int>> maxHeap;
        for (int i=0; i<n; ++i) maxHeap.push(a[i]);

        for (int i=0; i<n; ++i) {
            a[i] = maxHeap.top();
            maxHeap.pop();
        }
    }

    void display(int a[], int n) {
        for (int i=0; i<n; ++i) cout << a[i] << " ";
        cout << endl;
    }

    int solution2() {
        int arr1[] = {5, 6, 2, 4, 10, 9, 12, 60, 30};
        int arr2[] = {5, 6, 2, 4, 10, 9, 12, 60, 30};

        heapSortInc(arr1, 9);
        display(arr1, 9);

        heapSortDec(arr2, 9);
        display(arr2, 9);
    }
}