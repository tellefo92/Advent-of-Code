#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>
#include <map>
#include <chrono>
#include <math.h>

using namespace std;

int Below(int i, vector<int>& cave) {
    int width = sqrt(cave.size());
    return i + width < cave.size() ? i + width : -1;
}

int Right(int i, vector<int>& cave) {
    int width = sqrt(cave.size());
    return i % width < width - 1 ? i + 1 : -1;
}


void findAllPaths(vector<int>& cave, int i, int risk, int &lowest_risk, map<int,int>& visited) {
    risk += cave[i];
    if (risk >= lowest_risk) {
        return;
    }
    map<int,int>::iterator it = visited.find(i);
    if (it != visited.end()) {
        if (risk >= visited[i]) {
            return;
        }
    }
    visited[i] = risk;
    if (Below(i, cave) == -1 && Right(i, cave) == -1) {
        lowest_risk = risk;
        return;
    }
    if (Below(i, cave) != -1) {
        findAllPaths(cave, Below(i, cave), risk, lowest_risk, visited);
    } 
    if (Right(i, cave) != -1) {
        findAllPaths(cave, Right(i, cave), risk, lowest_risk, visited);
    }
}

int min_risk(vector<int>& cave) {
    int lowest_risk = cave.size();
    int i = 0;
    int risk = 0;
    map<int,int> visited;
    findAllPaths(cave, i, risk, lowest_risk, visited);
    int ans = lowest_risk - cave[0];
    return ans;
}

vector<int> scale_up(vector<int>& cave) {
    vector<int> scaled_cave;
    int width = sqrt(cave.size());
    int height = sqrt(cave.size());
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < 5; j++) {
            for (int k = 0; k < width; k++) {
                if (cave[k + i * height] + j > 9) {
                    scaled_cave.push_back((cave[k + i * height] + j) % 9);
                } else {
                    scaled_cave.push_back(cave[k + i * height] + j);
                }
            }
        }
    }
    int new_size = scaled_cave.size();
    for (int i = 1; i < 5; i++) {
        for (int j = 0; j < new_size; j++) {
            if (scaled_cave[j] + i > 9) {
                scaled_cave.push_back((scaled_cave[j] + i) % 9);
            } else {
                scaled_cave.push_back(scaled_cave[j] + i);
            }
        }
    }
    return scaled_cave;
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
    auto start = chrono::steady_clock::now();
    int ans = min_risk(cave);
    auto end = chrono::steady_clock::now();
    chrono::duration<double> t = end - start;
    cout << "Part 1: " << ans << ", solve time: " << t.count() << " s" << endl;
    start = chrono::steady_clock::now();
    vector<int> scaled_cave = scale_up(cave);
    ans = min_risk(scaled_cave);
    end = chrono::steady_clock::now();
    t = end - start;
    cout << "Part 2: " << ans << ", solve time: " << t.count() << " s" << endl;
    // Not 2967
    return 0;
}