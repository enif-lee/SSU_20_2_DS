#include <cmath>
#include <iostream>
#include <bits/exception.h>
#include <cstdio>
#include <cstring>

using namespace std;


namespace c5_1 {
    int **allocateMatrix(int rows, int cols) {
        if (fmin(rows, cols) < 0)
            exit(-1);

        int** matrix = new int*[rows];
        for (int i = 0; i < rows; i++)
            matrix[i] = new int[cols]{};

        return matrix;
    }

    void freeMatrix(int **matrix, int rows) {
        if (matrix == nullptr)
            return;

        for (int i = 0; i < rows; i++)
            delete[] matrix[i];
        delete[] matrix;
    }

    void setMatrixRandom(int **matrix, int rows, int cols) {
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                matrix[i][j] = rand() % 100;
    }

    void displayMatrix(int **matrix, int rows, int cols) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++)
                printf("%4d", matrix[i][j]);
            cout << endl;
        }
    }

    struct Matrix {
    private:


    public:
        Matrix(int **d, int r, int c) : data(d), rows(r), cols(c) {}

        Matrix(int r, int c) : data(allocateMatrix(r, c)), rows(r), cols(c) {}

        int **const data;
        const int rows;
        const int cols;


        void setRandom() {
            setMatrixRandom(data, rows, cols);
        }

        void display() {
            displayMatrix(data, rows, cols);
        }

        virtual ~Matrix() {
            freeMatrix(data, rows);
        }
    };

    void solution() {
        int **matrix = allocateMatrix(10, 10);
        setMatrixRandom(matrix, 10, 10);
        displayMatrix(matrix, 10, 10);
        freeMatrix(matrix, 10);


//        Matrix matrix(10, 10);
//
//        matrix.display();
//        cout << "-------------------------------------------" << endl;
//        matrix.setRandom();
//        matrix.display();
    }
}

namespace c5_2 {
#define MAX_STRING    100

    class Student {
        int id;
        char name[MAX_STRING];
        char dept[MAX_STRING];
    public:
        Student(int i = 0, char *nam = "", char *dep = "") {
            set(i, nam, dep);
        }

        void set(int i, char *nam, char *dep) {
            id = i;
            strcpy(name, nam);
            strcpy(dept, dep);
        }

        void display() {
            printf(" 학번:%-15d 성명:%-10s 학과:%-20s\n", id, name, dept);
        }
    };

    class Node : public Student {
        Node *link;    // 다음 노드를 가리키는 포인터 변수
    public:
        Node(int id = 0, char *name = "", char *dept = "")
                : Student(id, name, dept) { link = NULL; }

        ~Node(void) {}

        Node *getLink() { return link; }

        void setLink(Node *p) { link = p; }
    };

    class LinkedStack {
        Node *top;
    public:
        LinkedStack() { top = NULL; }

        ~LinkedStack() { while (!isEmpty()) delete pop(); }

        bool isEmpty() { return top == NULL; }

        void push(Node *n) {
            n->setLink(top);
            top = n;
        }

        Node *pop() {
            if (isEmpty())
                return NULL;

            auto item = top;
            top = top->getLink();
            return item;
        }

        Node *peek() { return top; }

        void display() {
            cout << "[LinkedStack]" << endl;
            auto node = top;
            while (node != NULL) {
                node->display();
                node = node->getLink();
            }
        }
    };

    void solution() {
        LinkedStack stack;
        stack.push(new Node(2015130007, "홍길동", "컴퓨터공학과"));
        stack.push(new Node(2015130100, "이순신", "기계공학과"));
        stack.push(new Node(2015130135, "황희", "법학과"));
        stack.display();

        Node *node = stack.pop();
        cout << "[Pop항목]" << endl;
        node->display();

        delete node;
        stack.display();
    }
}

namespace c5_3 {
    class Node
    {
        Node*	link;
        int		data;
    public:
        Node( int val=0) : data(val), link(NULL) { }
        Node* getLink()		{ return link; }
        void setLink(Node* next)	{ link=next; }
        void display() 		{ printf(" <%2d>", data); }
    };

    class LinkedQueue
    {
        Node*	front;
        Node*	rear;
    public:
        LinkedQueue(): front(NULL), rear(NULL) { }
        ~LinkedQueue() { while(!isEmpty()) delete dequeue(); }
        bool isEmpty() { return front == NULL; }

        // 삽입 연산
        void enqueue (Node* n)	{
            if (isEmpty()) {
                front = rear = n;
            } else {
                rear->setLink(n);
                rear = n;
            }
        }
        // 삭제 연산
        Node* dequeue ( ) {
            if (isEmpty()) // 빈거
                return NULL;
            if (rear == front) { // 하나만 있느거
                auto item = front;
                rear = front = NULL;
                return item;
            }

            // 최소 두개 이상 있을 때
            auto item = front;
            front = item->getLink();
            return item;
        }

        Node* peek ( )	{ return front; }
        void display( ) {
            cout << "[큐 내용] : ";
            auto item = front;
            while (item != NULL) {
                item->display();
                item = item->getLink();
            }
            cout << endl;
        }
    };

    void solution()
    {
        LinkedQueue que;
        for( int i=1 ; i<10 ; i++ )
            que.enqueue( new Node(i) );
        que.display();
        delete que.dequeue();
        delete que.dequeue();
        delete que.dequeue();
        que.display();
    }
}