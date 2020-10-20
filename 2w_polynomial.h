#include <iostream>
#include <cstring>

#define MAX_DEGREE 80                 // 다항식의 처리 가능한 최대 차수+1
using namespace std;

class Polynomial {
    int degree;                  // 다항식의 최고 차수
    float coef[MAX_DEGREE];     // 각 항에 대한 계수
public:
    Polynomial() { degree = 0; }      // 생성자: 최대 차수를 0으로 초기화
    // 다항식의 내용을 입력받는 멤버함수
    void read() {
        cout << "다항식의 최고 차수를 입력하시오: ";
        cin >> degree;
        cout << endl << "각 항의 계수를 입력하시오 (총 " << degree + 1 << "): ";
        for (int i = 0; i <= degree; i++)
            cin >> *(coef + i);
    }

    // 다항식의 내용을 화면에 출력하는 함수
    void display(const string& str = "Poly = ") {
        cout << str;
        for (int i = 0; i < degree; i++)
            printf("%5.1f x^%d + ", coef[i], degree - i);
        printf("%4.1f\n", coef[degree]);
    };

    Polynomial add(Polynomial a) {
        Polynomial big, *less;

        if (degree < a.degree) {
            big = a;
            less = this;
        } else {
            big = *this;
            less = &a;
        }

        for (int i = 0; i <= less->degree; i++)
            big.coef[big.degree - i] += less->coef[less->degree - i];

        return big;
    }

    bool isZero() {
        return degree == 0;
    }

    Polynomial negate() {
        Polynomial newer = *this;
        for (int i = 0; i <= newer.degree; i++)
            newer.coef[i] = -newer.coef[i];
        return newer;
    }
};


struct Term {
    int expo; // 차수
    float coef; // 계수


    Term operator+(Term &other) {
        if (this->expo != other.expo)
            exit(-1);

        Term newTerm;
        newTerm.expo = other.expo;
        newTerm.coef = this->coef + other.coef;
        return newTerm;
    }

    static int compare(const void* a, const void* b) {
        Term *termA = (Term *) a;
        Term *termB = (Term *) b;

        return termA->expo == termB->expo
            ? termA->coef - termB->coef
            : termA->expo - termB->expo;
    }

    static Term* createTerms(int count) {
        return (Term*) malloc(sizeof(Term) * count);
    }

    static void sort(Term* terms, int count) {
        qsort(terms, count, sizeof(Term), Term::compare);
    }
};

class SparsePoly {
    int termCount;
    Term* terms;

private:
    SparsePoly(int termCount, Term* terms) {
        this->termCount = termCount;
        this->terms = terms;
    }

public:
    static SparsePoly create(Term* terms, int count) {
        Term::sort(terms, count);
        int reduceCount = 0, lastExpo = INT32_MIN;
        for(int i = 0; i < count; i++) {
            Term &term = terms[i];
            if (lastExpo != term.expo)
            {
                lastExpo = term.expo;
                reduceCount++;
            }
        }

        int newTermsIndex = 0;
        Term* newTerms = Term::createTerms(reduceCount);

        for(int i = 0; i < count; i++) {
            Term &term = terms[i];

            if (i == 0) {
                newTerms[newTermsIndex] = term;
            } else {
                if (newTerms[newTermsIndex].expo != term.expo) {
                    newTermsIndex++;
                    newTerms[newTermsIndex] = term;
                } else {
                    newTerms[newTermsIndex] =  newTerms[newTermsIndex] + term;
                }
            }
        }

        return SparsePoly(reduceCount, newTerms);
    }

    static SparsePoly readToCreatePoly() {
        int termsCount;
        cout << "항의 갯수를 입력해주세요 : ";
        cin >> termsCount;


        Term* terms = Term::createTerms(termsCount);
        for (int i = 0; i < termsCount; i++) {
            Term newTerm;
            cout << i + 1 << "번 째 항의 계수와 차수를 입력해 주세요 : ";
            cin >> newTerm.coef >> newTerm.expo;
            terms[i] = newTerm;
        }

        return SparsePoly::create(terms, termsCount);
    }

    SparsePoly add(SparsePoly &other) {
        int count = other.termCount + termCount;
        Term* terms = Term::createTerms(count);

        for (int i = 0; i < other.termCount; i++)
            terms[i] = other.terms[i];

        for (int i = other.termCount; i < count; i++)
            terms[i] = this->terms[i - other.termCount];

        return create(terms, count);
    }

    ~SparsePoly() {
        free(terms);
    }


    void display(char *str = "Poly = ") {
        cout << str;
        for (int i = 0; i < termCount; i++){
            Term &term = this->terms[i];

            auto format = i == termCount - 1 ? "%5.1f x^%d" : "%5.1f x^%d + ";
            printf(format, term.coef, term.expo);
        }
        cout << endl;
    }
};
