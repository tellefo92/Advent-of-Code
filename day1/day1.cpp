#include <iostream>
#include <fstream>

using namespace std;

int first() {
    int n = 0;
    int prev;
    int curr;
    ifstream infile("day1.txt");
    infile >> prev;

    while (infile >> curr) {
        if (curr > prev){
            n++;
        }
        prev = curr;
    }
    return n;
}

int second() {
    int n = 0;
    int first, second, third, sum;
    ifstream infile("day1.txt");
    infile >> first >> second >> third;
    sum = first + second + third;
    first = second;
    second = third;
    while(infile >> third) {
        int new_sum = first + second + third;
        if (new_sum > sum) {
            n++;
        }
        sum = new_sum;
        first = second;
        second = third;
    }
    return n;
}

int main(){
    cout << first() << endl;
    cout << second() << endl;
}