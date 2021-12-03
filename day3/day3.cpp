#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int binaryToDecimal(string n) {
    string num = n;
    int dec = 0;
    int base = 1;
    for (int i=11; i>=0;i--) {
        if (num[i] == '1') {
            dec += base;
        }
        base *= 2;
    }
    return dec;
}

vector <string> find_most_common(vector<string> input, int pos) {
    int tot = input.size();
    if (tot == 1) return input;
    vector<string> out;
    int counter_1 = 0;
    int counter_0 = 0;
    char most_common;
    for (auto& s : input) {
        if (s[pos] == '1') {
            counter_1++;
        } else {
            counter_0++;
        }
    }
    if (counter_1 >= counter_0) {
        most_common = '1';
    } else {
        most_common = '0';
    }
    for (auto& s : input) {
        if (s[pos] == most_common) {
            out.push_back(s);
        }
    }
}

vector <string> find_least_common(vector<string> input, int pos) {
    int tot = input.size();
    if (tot == 1) return input;
    vector<string> out;
    int counter_1 = 0;
    int counter_0 = 0;
    char least_common;
    for (auto& s : input) {
        if (s[pos] == '1') {
            counter_1++;
        } else {
            counter_0++;
        }
    }
    if (counter_1 < counter_0) {
        least_common = '1';
    } else {
        least_common = '0';
    }
    for (auto& s : input) {
        if (s[pos] == least_common) {
            out.push_back(s);
        }
    }
    return out;
}

int first() {
    ifstream infile("day3.txt");
    int N = 12;
    string input;
    int i;
    int tot = 0;
    vector <int> most_common(N,0);
    while (infile >> input) {
        i = 0;
        tot++;
        for (string::iterator it=input.begin(); it!=input.end(); it++) {
            if (*it == 49) {
                most_common[i] += 1;
            }
            i++;
        }
    }
    string gamma;
    string epsilon;
    

    double tot_half = tot/2;
    for (auto& n: most_common) {
        if (n > tot_half) {
            gamma += '1';
            epsilon += '0';
        } else {
            gamma += '0';
            epsilon += '1';
        }
    }

    int g, e;
    g = binaryToDecimal(gamma);
    e = binaryToDecimal(epsilon);
    return g*e;
}

int second() {
    ifstream infile("day3.txt");
    int N = 12;
    string input;
    vector<string> all;
    int i;
    while (infile >> input) {
        all.push_back(input);
    }
    vector<string> all_copy;
    for (auto& s: all) {
        all_copy.push_back(s);
    }
    for (i=0; i<N; i++) {
        all = find_most_common(all, i);
        all_copy = find_least_common(all_copy, i);
    }
    int o2, co2;
    o2 = binaryToDecimal(all[0]);
    co2 = binaryToDecimal(all_copy[0]);
    return o2*co2;
}

int main() {
    cout << first() << endl;
    cout << second() << endl;
}