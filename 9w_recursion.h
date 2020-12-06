#include "iostream"


using namespace std;

namespace w9 {
    void movePanel(int n, char from, char to) {
        cout << "원판 " << n << " : " << from << " -> " << to << endl;
    }

    void hanoiTower(int n, char from, char tmp, char to) {
        if (n == 1) {
            movePanel(n, from, to);
        } else {
            hanoiTower(n - 1, from, to, tmp);
            movePanel(n, from, to);
            hanoiTower(n - 1, tmp, from, to);
        }
    }

#define HEIGHT 10
#define WIDTH 20

    void labelComponent(char img[HEIGHT][WIDTH], int x, int y, int label) {
        if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
            return;

        if (img[y][x] != 9)
            return;

        labelComponent(img, x - 1, y, label);
        labelComponent(img, x, y - 1, label);
        labelComponent(img, x + 1, y, label);
        labelComponent(img, x, y + 1, label);
    }

    void blobColoring(char img[10][20]) {
        int label = 1;
        for (int y = 0; y < HEIGHT; y++) {
            for(int x = 0; x < WIDTH; x++) {
                if (img[y][x] != 9)
                    continue;
                labelComponent(img, x, y, label++);
            }
        }
    }


}