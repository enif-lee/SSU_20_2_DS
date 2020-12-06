#include "iostream"
#include "queue"
#include <cstdio>

namespace w13 {
    using namespace std;
#define MAX_VTXS 100

    class AdjMatGraph {
    protected:
        int size;
        char vertices[MAX_VTXS];
        int adj[MAX_VTXS][MAX_VTXS];
    public:
        AdjMatGraph() { reset(); }

        char getVertex(int i) { return vertices[i]; }

        int getEdge(int i, int j) { return adj[i][j] }

        void setEdge(int i, int j, int val) { adj[i][j] = val; }


        bool isEmpty() { return size == 0; }

        bool isFull() { return size >= MAX_VTXS; }

        void reset() {
            size = 0;
            for (int i = 0; i < MAX_VTXS; i++)
                for (int j = 0; j < MAX_VTXS; j++)
                    setEdge(i, j, 0);
        }

        void insertVertex(char name) {
            if (!isFull())
                vertices[size++] = name;
            else cout << "ERROR : 그래프 정점 개수 초과" << endl;
        }

        void insertEdge(int u, int v) {
            setEdge(u, v, 1);
            setEdge(v, u, 1);
        }

        void removeEdge(int u, int v) {
            setEdge(u, v, 0);
            setEdge(v, u, 0);
        }
    };

    // 탐색 기능이 추가된 인접 행렬 기반 그래프 클래스
    class SrchAMGraph : public AdjMatGraph {
    protected:
        bool visited[MAX_VTXS];     // 정점의 방문 정보
    public:
        void resetVisited() {    // 모든 정점을 방문하지 않았다고 설정
            for (int i = 0; i < size; i++)
                visited[i] = false;
        }

        bool isLinked(int u, int v) { return getEdge(u, v) != 0; }

        // 깊이 우선 탐색 함수
        void DFS(int v) {
            visited[v] = true;     // 현재 정점을 방문함
            printf("%c ", getVertex(v)); // 정점의 이름 출력

            for (int w = 0; w < size; w++)
                if (isLinked(v, w) && visited[w] == false)
                    DFS(w);     // 연결 + 방문X => 순환호출로 방문
        }

        // 프로그램 11.8의 SrchAMGraph클래스의 멤버 함수로 구현
        void BFS(int v) {
            visited[v] = true;        // 현재 정점을 방문함
            printf("%c ", getVertex(v));    // 정점의 이름 출력

            queue<int> que;
            que.push(v);        // 시작 정점을 큐에 저장
            while (!que.empty()) {
                int v = que.front();
                que.pop();
                for (int w = 0; w < size; w++)
                    if (isLinked(v, w) && visited[w] == false) {
                        visited[w] = true;
                        printf("%c ", getVertex(w));
                        que.push(w);
                    }
            }
        }
    };

    class ConnectedComponentGraph : public SrchAMGraph {
        int label[MAX_VTXS];    // 정점의 색상 필드 추가
    public:
        void labelDFS(int v, int color) {
            visited[v] = true;    // 현재 정점을 방문함
            label[v] = color;    // 현재 정점의 색상
            for (int w = 0; w < size; w++)
                if (isLinked(v, w) && visited[w] == false)
                    labelDFS(w, color);
        }

        void displayConnectedComponent() {
            int count = 0;
            for (int i = 0; i < size; i++)
                if (visited[i] == false)
                    labelDFS(i, ++count);

            printf("그래프 연결성분 개수 = = %d\n", count);
            for (int i = 0; i < size; i++)
                printf("%c=%d", getVertex(i), label[i]);
            printf("\n");

            resetVisited();
            resetLabel();
        }


        int findConnectedComponent() {
            int count = 0;
            for (int i = 0; i < size; i++)
                if (visited[i] == false) {
                    DFS(i);
                    count++;
                }

            resetVisited();
            resetLabel();
            return count;
        }

        int findBridge() {
            int count = 0;
            for (int i = 0; i < size; i++)
                for (int j = 0; j < size; i++) {
                    if (getEdge(i, j) == 0)
                        continue;

                    // 임시로 끊어 봄
                    removeEdge(i, j);

                    if (findConnectedComponent() > 1)
                        count++;

                    // 다시 붙힘
                    insertEdge(i, j);
                }

            return count;
        }

        void resetLabel() {
            for (int i = 0; i < MAX_VTXS; i++)
                label[i] = 0;
        }
    };


    class Node {
    protected:
        int id;
        Node *link;
    public:
        Node(int i, Node *l = NULL) : id(i), link(l) {}

        ~Node() {
            if (link != NULL) delete link;
        }

        int getId() { return id; }

        Node *getLink() { return link; }

        void setLink(Node *l) { link = l; }
    };

    class AdjListGraph {
    protected:
        int size;
        char vertices[MAX_VTXS];
        Node *adj[MAX_VTXS];
    public:
        AdjListGraph() : size(0) {}

        void reset() {
            for (int i = 0; i < size; i++)
                if (adj[i] != NULL)
                    delete adj[i];
        }

        ~AdjListGraph() { reset(); }

        void insertVertex(char val) {
            if (!isFull()) {
                vertices[size] = val;
                adj[size++] = NULL;
            } else cout << "그래프 정점 개수 초과" << endl;
        }

        bool isEmpty() { return size == 0; }

        bool isFull() { return size >= MAX_VTXS; }

        void insertEdge(int u, int v) {
            adj[u] = new Node(v, adj[u]);
            adj[v] = new Node(u, adj[v]);
        }
    };
}