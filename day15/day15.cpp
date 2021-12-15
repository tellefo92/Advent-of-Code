#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>
#include <map>

using namespace std;

int Below(int i) {
    return i + 100 <= 9999 ? i + 100 : -1;
}

int Right(int i) {
    return i % 100 < 99 ? i + 1 : -1;
}

void findAllPaths(vector<int>& cave, int i, int risk, vector<int>& risks, map<int,int>& visited) {
    risk += cave[i];
    map<int,int>::iterator it = visited.find(i);
    if (it != visited.end()) {
        if (risk >= visited[i]) {
            return;
        }
    }
    visited[i] = risk;
    if (Below(i) == -1 && Right(i) == -1) {
        risks.push_back(risk);
        return;
    }
    if (Below(i) != -1) {
        findAllPaths(cave, Below(i), risk, risks, visited);
    } 
    if (Right(i) != -1) {
        findAllPaths(cave, Right(i), risk, risks, visited);
    }
}

void min_risk(vector<int> cave) {
    vector<int> risks;
    int i = 0;
    int risk = 0;
    map<int,int> visited;
    findAllPaths(cave, i, risk, risks, visited);
    sort(risks.begin(), risks.end());
    int ans = risks[0] - cave[0];
    cout << ans << endl;
}

int main() {
    ifstream infile("day15.txt");
    string line;
    vector<int> cave;
    while(infile >> line) {
        for (auto& c: line) {
            cave.push_back(c-'0');
        }
    }
    min_risk(cave);
    return 0;
}