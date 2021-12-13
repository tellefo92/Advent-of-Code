#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_set>
#include <bits/stdc++.h>

int Above(int i) {
    // Returns index of element above i in FlattenedMap
    // If i is on top row, return -1
    return i - 100 >= 0 ? i - 100 : 10;
}

int Below(int i) {
    // Returns index of element below i in FlattenedMap
    // If i is bottom row, return 10
    return i + 100 < 9999 ? i + 100 : -1;
}

int Left(int i) {
    // Returns index of element left of i in FlattenedMap
    // If i is in left column, return 10
    return i % 100 > 0 ? i - 1 : -1;
}

int Right(int i) {
    // Returns index of element right of i in FlattenedMap
    // If i is in right column, return 10
    return i % 100 < 99 ? i + 1 : -1;
}

std::vector<int> LowPoints(std::vector<int> FlattenedMap) {
    std::vector<int> points;
    for (int i = 0; i < FlattenedMap.size(); i++) {
        std::vector<int> neighbors = {Above(i), Below(i), Left(i), Right(i)};
        bool low_point = true;
        for (auto& d: neighbors) {
            if (d != -1) {
                if (FlattenedMap[i] >= FlattenedMap[d]) {
                    low_point = false;
                }
            }
        }
        if (low_point) {
            points.push_back(i);
        }
    }
    return points;
}

void GetBasinSize(int i, std::vector<int> FlattenedMap, std::unordered_set<int>& indices) {

    if (i == -1 || FlattenedMap[i] == 9 || indices.find(i) != indices.end()) {
        return;
    }

    indices.insert(i);
    GetBasinSize(Above(i), FlattenedMap, indices);
    GetBasinSize(Below(i), FlattenedMap, indices);
    GetBasinSize(Left(i), FlattenedMap, indices);
    GetBasinSize(Right(i), FlattenedMap, indices);
}

void Part1(std::vector<int> FlattenedMap) {
    int sum = 0;
    std::vector<int> points = LowPoints(FlattenedMap);
    for (auto& i: points) {
        sum += FlattenedMap[i] + 1;
    }
    std::cout << sum << std::endl;
}

void Part2(std::vector<int> FlattenedMap) {
    int prod = 1;
    std::vector<int> points = LowPoints(FlattenedMap);
    std::vector<int> sizes;
    for (auto i: points) {
        std::unordered_set<int> indices;
        GetBasinSize(i, FlattenedMap, indices);
        sizes.push_back(indices.size());
    }
    sort(sizes.begin(), sizes.end(), std::greater<int>());
    for (int i=0; i<3; i++) {
        prod *= sizes[i];
    }
    std::cout << prod << std::endl;
}

int main() {
    std::ifstream infile("day9.txt");
    std::string line;
    std::vector<int> FlattenedMap;
    while (infile >> line) {
        for (auto& c: line) {
            FlattenedMap.push_back(c-'0');
        }
    }
    Part1(FlattenedMap);
    Part2(FlattenedMap);
    return 0;
}