#include<iostream>
#include<unistd.h>
#include "judge.h"

using namespace std;

int main(int argc, char **argv) {
    double x, y;
    char str = 'y';
    while (str == 'y' || str == 'Y') {
        cout << "input:\n";
        cin >> x;
        if (cin.get() == ',') {
            cin >> y;
        }
        bool result = Judge::judgementoflocation(x, y);
        if (result) {
            cout << "The car is in China\n";
        } else {
            cout<<"The car is not in China\n";
        }
        cout << "conutine:(y or Y)?\n";
        cin >> str;
    }
    return 0;
}