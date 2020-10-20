#include <iostream>
#include "math.h"
#include "stack"
#include "queue"

using namespace std;


namespace ds_3w {
    namespace escape_miro {
        struct Location {
            int row;
            int col;
            Location (int r=0, int c=0) {
                row = r;
                col = c;
            }

            bool isNeighbor(Location &p) {
                return abs(p.col - col) + abs(p.row - row) == 1;
            }

            bool operator==(Location &p) {
                return p.col == col && row == p.row;
            }

            Location operator+(Location &p) {
                return Location(p.row + row, p.col + col);
            }
        };


        const int MAZE_SIZE = 6;
        char map[MAZE_SIZE][MAZE_SIZE] = {
                {'1', '1', '1', '1', '1', '1'},
                {'e', '0', '1', '0', '0', '1'},
                {'1', '0', '0', '0', '1', '1'},
                {'1', '0', '1', '0', '1', '1'},
                {'1', '0', '1', '0', '0', 'x'},
                {'1', '1', '1', '1', '1', '1'},
        };

        bool isValidLoc(int r, int c) {
            if (min(r, c) < 0 && max(r, c) >= MAZE_SIZE) return false;
            char loc = map[r][c];
            return loc == '0' || loc == 'x';
        }

        bool isValidLocation(Location &p) {
            return isValidLoc(p.row, p.col);
        }

        void travelMazeDfs() {
            stack<Location> locations;
            Location entry (1, 0);
            locations.push(entry);

            Location directions[4] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1}};

            while (!locations.empty()) {
                auto here = locations.top();
                locations.pop();
                cout << "(" << here.row << "," << here.col << ")";

                if (map[here.row][here.col] == 'x') {
                    cout << "탈출!" << endl;
                    return;
                } else {
                    map[here.row][here.col] = '.';
                    for (auto direction : directions) {
                        Location next = here + direction;
                        if (isValidLocation(next))
                            locations.push(next);
                    }
                }
            }
            cout << "미로 탐색 실패" << endl;
        }

        void travelMazeBfs() {
            queue<Location> locations;
            Location entry (1, 0);
            locations.push(entry);

            Location directions[4] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1}};

            while (!locations.empty()) {
                auto here = locations.front();
                locations.pop();
                cout << "(" << here.row << "," << here.col << ")";

                if (map[here.row][here.col] == 'x') {
                    cout << "탈출!" << endl;
                    return;
                } else {
                    map[here.row][here.col] = '.';
                    for (auto direction : directions) {
                        Location next = here + direction;
                        if (isValidLocation(next))
                            locations.push(next);
                    }
                }
            }
            cout << "미로 탐색 실패" << endl;
        }
    }

    namespace calculator {
        static bool isOperator(char &c) {
            switch (c) {
                case '+':
                case '-':
                case '*':
                case '/':
                    return true;
                default:
                    return false;
            }
        }

        static double calculate(char &oper, double &oper1, double &oper2) {
            switch (oper) {
                case '+': return oper1 + oper2;
                case '-': return oper1 - oper2;
                case '*': return oper1 * oper2;
                case '/': return oper1 / oper2;
            }
            exit(-1);
        }

        bool isNumber(char c) { return '0' <= c && c <= '9'; }

        double calculatePostfixExpression(FILE *fp = stdin) {
            stack<double> operands;

            char c;
            while ((c = getc(fp)) != '\n') {
                if (isOperator(c)) {
                    double op1 = operands.top();
                    operands.pop();
                    double op2 = operands.top();
                    operands.pop();
                    operands.push(calculate(c, op1, op2));
                } else if (isNumber(c)) {
                    ungetc(c, fp);
                    double value;
                    fscanf(fp, "%lf", &value);
                    operands.push(value);
                }
            }

            return operands.top();
        }

        int precedence(char &op) {
            switch (op) {
                case '+': case '-': return 1;
                case '*': case '/': return 2;
            }
            return -1;
        }

        void infixExpToPostfixExp(FILE *fp = stdin) {
            stack<char> operators;
            char c;
            while ((c = getc(fp)) != '\n') {
                if (isNumber(c)) {
                    ungetc(c, fp);
                    double operand;
                    fscanf(fp, "%lf", &operand);
                    printf("%4.1f ", operand);
                } else if (c == '(') {
                    operators.push(c);
                } else if (c == ')') {
                    while (!operators.empty()) {
                        char op = operators.top();
                        operators.pop();
                        if (op == '(') break;
                        else printf("%c ", op);
                    }
                } else if (isOperator(c)) {
                    while (!operators.empty()) {
                        char op = operators.top();
                        if (precedence(c) <= precedence(op)) {
                            printf("%c ", op);
                            operators.pop();
                        }
                        else break;
                    }
                    operators.push(c);
                }
            }

            while (!operators.empty()) {
                printf("%c ", operators.top());
                operators.pop();
            }
        }

        struct OP {
        public:
            OP(double number) {
                value = number;
                isNumber = true;
            }
            OP(char oper) {
                op = oper;
                isNumber = false;
            }
            char op;
            double value;
            bool isNumber;
        };

        double calculateExpression(string expression) {
            int pointer = 0;

            queue<OP> ops;
            stack<char> operators;

            while (pointer != expression.length()) {
                char c = expression[pointer];

                if (isNumber(c)) {
                    auto next = expression.find_first_not_of("0123456789.", pointer);
                    auto number = stod(expression.substr(pointer, next - 1));
                    ops.push(OP(number));
                    pointer = next;
                    continue;
                }

                if (c == '(') {
                    operators.push(c);
                } else if (c == ')') {
                    while (!operators.empty()) {
                        char op = operators.top();
                        operators.pop();
                        if (op == '(') break;
                        else ops.push(OP(c));
                    }
                } else if (isOperator(c)) {
                    while (!operators.empty()) {
                        char op = operators.top();
                        if (precedence(c) <= precedence(op)) {
                            ops.push(OP(op));
                            operators.pop();
                        }
                        else break;
                    }
                    operators.push(c);
                }
                pointer += 1;
            }
            while (!operators.empty()) {
                ops.push(OP(operators.top()));
                operators.pop();
            }
            stack<double> operands;
            while (!ops.empty()) {
                auto op = ops.front();
                ops.pop();
                if (!op.isNumber) {
                    double op1 = operands.top();
                    operands.pop();
                    double op2 = operands.top();
                    operands.pop();
                    operands.push(calculate(op.op, op1, op2));
                } else {
                    operands.push(op.value);
                }
            }

            return operands.top();
        }
    }
}