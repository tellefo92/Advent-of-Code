#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <cmath>
#include <chrono>
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

int main() {
    ifstream input("day7.txt");
    string line;
    input >> line;
    stringstream ss(line);
    vector<int> v;
    int j;
    int sum = 0;
    while (ss >> j) {
        sum += j;
        v.push_back(j);
        ss.ignore(1);
    }
    auto start = chrono::steady_clock::now();
    sort(v.begin(), v.end());
    int index;
    if (v.size() % 2 == 0) {
        index = v.size() / 2;
    } else {
        index = (v.size() - 1) / 2;
    }
    int median = v[index];
    int fuel = 0;
    int fuel2 = 0;
    int k;
    int avg = (int) ((double) sum / (double) v.size());

    for (auto& n : v) {
        fuel += abs(n - median);
        k = abs(n - avg);
        for (int i = 0; i < k; i++) {
            fuel2 += i + 1;
        }
    }
    auto end = chrono::steady_clock::now();
    chrono::duration<double> t = end-start;
    cout << "Part 1: " << fuel << endl;
    cout << "Part 2: " << fuel2 << endl;
    cout << "Solve time: " << t.count() << "s" << endl;
}

/* 
Part 1: 323647
Part 2: 87640209
Solve time: 0.0009183s
*/