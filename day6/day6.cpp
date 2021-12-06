#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <cmath>
#include <chrono>

typedef long long ll;

using namespace std;

map<int,ll> nextDay(map<int,ll> fish) {
    ll births = fish[0];
    for (int i=1; i<9; i++) {
        fish[i-1] = fish[i];
    }
    fish[6] += births;
    fish[8] = births;
    return fish;
}

ll totalFish(map<int,ll> fish) {
    ll sum = 0;
    ll n;
    for (int i=0; i<9; i++) {
        n = fish[i];
        sum += n;
    }
    return sum;
}

int main() {
    ifstream input("day6.txt");
    string line;
    input >> line;
    stringstream ss(line);
    map<int,ll> fish;
    for (int i=0; i<9; i++) {
        fish[i] = 0;
    }
    int j;
    while (ss >> j) {
        fish[j]++;
        ss.ignore(1);
    }
    auto s1 = chrono::steady_clock::now();
    // Part 1, total fish after 80 days
    for (int i = 0; i < 80; i++) {
        fish = nextDay(fish);
    }
    auto e1 = chrono::steady_clock::now();
    chrono::duration<double> t1 = e1-s1;
    ll ans_1 = totalFish(fish);
    
    // Part 2, total fish after an additional 176 days (256 total)
    auto s2 = chrono::steady_clock::now();
    for (int i = 0; i < 176; i++) {
        fish = nextDay(fish);
    }
    auto e2 = chrono::steady_clock::now();
    chrono::duration<double> t2 = e2-s2+t1;
    ll ans_2 = totalFish(fish);
    cout << "Total fish after 80 days: " << ans_1 << ", solve time: " << t1.count() << "s" << endl;
    cout << "Total fish after 256 days: " << ans_2 << ", solve time: " << t2.count() << "s" << endl;
    return 0;
}

/* 
Total fish after 80 days: 388739, solve time: 0.0002653s
Total fish after 256 days: 1741362314973, solve time: 0.0008421s
*/