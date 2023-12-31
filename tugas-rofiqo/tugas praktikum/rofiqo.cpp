#include <iostream>
#include <cmath>
#include <stack>
#include <map>

using namespace std;

int nilai_ekspresi(string str) {
    map<char, int> prioritas;
    prioritas['^'] = 3;
    prioritas['*'] = 2, prioritas['/'] = 2;
    prioritas['+'] = 1, prioritas['-'] = 1;

    stack<char> tumpukan_operator;
    stack<int> tumpukan_nilai;

    int nilai = 0;
    for (int i = 0; str[i]; i++) {
        if (str[i] >= '0' && str[i] <= '9')
            nilai = nilai * 10 + str[i] - '0';
        else {
            if (tumpukan_operator.empty()) {
                tumpukan_nilai.push(nilai);
                tumpukan_operator.push(str[i]);
            } else if (prioritas[tumpukan_operator.top()] < prioritas[str[i]]) {
                tumpukan_nilai.push(nilai);
                tumpukan_operator.push(str[i]);
            } else {
                int num1, num2;
                num1 = tumpukan_nilai.top();
                tumpukan_nilai.pop();
                num2 = nilai;
                if (tumpukan_operator.top() == '+')
                    tumpukan_nilai.push(num1 + num2);
                else if (tumpukan_operator.top() == '-')
                    tumpukan_nilai.push(num1 - num2);
                else if (tumpukan_operator.top() == '*')
                    tumpukan_nilai.push(num1 * num2);
                else if (tumpukan_operator.top() == '/')
                    tumpukan_nilai.push(num1 / num2);
                else
                    tumpukan_nilai.push(pow(num1, num2));
                tumpukan_operator.pop();
                tumpukan_operator.push(str[i]);
            }
            nilai = 0;
        }
    }
    tumpukan_nilai.push(nilai);

    while (!tumpukan_operator.empty()) {
        int num1, num2;
        num2 = tumpukan_nilai.top();
        tumpukan_nilai.pop();
        num1 = tumpukan_nilai.top();
        tumpukan_nilai.pop();
        if (tumpukan_operator.top() == '+')
            tumpukan_nilai.push(num1 + num2);
        else if (tumpukan_operator.top() == '-')
            tumpukan_nilai.push(num1 - num2);
        else if (tumpukan_operator.top() == '*')
            tumpukan_nilai.push(num1 * num2);
        else if (tumpukan_operator.top() == '/')
            tumpukan_nilai.push(num1 / num2);
        else
            tumpukan_nilai.push(pow(num1, num2));
        tumpukan_operator.pop();
    }
    return tumpukan_nilai.top();
}

int main() {
    string input_ekspresi;
    cout << "Masukkan ekspresi matematika: ";
    cin >> input_ekspresi;

    int hasil = nilai_ekspresi(input_ekspresi);
    cout << "Hasil perhitungan: " << hasil << endl;

    return 0;
          }