#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int Above(int i) {
    return i - 10 >= 0 && i != -1 ? i - 10 : -1;
}

int Below(int i) {
    return i + 10 <= 99 && i != -1 ? i + 10 : -1;
}

int Left(int i) {
    return i % 10 >= 1 ? i - 1 : -1;
}

int Right(int i) {
    return i % 10 < 9 ? i + 1 : -1;
}

int AboveLeft(int i) {
    return Above(Left(i));
}

int AboveRight(int i) {
    return Above(Right(i));
}

int BelowLeft(int i) {
    return Below(Left(i));
}

int BelowRight(int i) {
    return Below(Right(i));
}

void Increase(std::vector<int>& cave) {
    for (int i = 0; i < cave.size(); i++) {
        cave[i]++;
    }
}

void Flash(std::vector<int>& cave, int& flashes) {
    for (int i = 0; i < cave.size(); i++) {
        if (cave[i] > 9) {
            std::vector<int> neighbors = {Above(i), Below(i), Left(i), Right(i), AboveLeft(i), AboveRight(i), BelowLeft(i), BelowRight(i)};
            for (auto& n: neighbors) {
                if (n != -1 && cave[n] != 0) {
                    cave[n]++;
                }
            }
            cave[i] = 0;
            flashes++;
            Flash(cave, flashes);
        }
    }
}

void Step(std::vector<int>& cave, int& flashes) {
    Increase(cave);
    Flash(cave, flashes);
}

bool AllZero(std::vector<int> cave) {
    for (int i=0; i<100; i++) {
        if (cave[i] != 0) {
            return false;
        }
    }
    return true;
}

void First(std::vector<int> cave) {
    int flashes = 0;
    for (int i=0; i<100;i++) {
        Step(cave, flashes);
    }
    std::cout << flashes << std::endl;
}

void Second(std::vector<int> cave) {
    int step = 0;
    int flashes = 0;
    while(!AllZero(cave)) {
        Step(cave, flashes);
        step++;
    }
    std::cout << step << std::endl;
}

int main() {
    std::ifstream input("day11.txt");
    std::string line;
    std::vector<int> cave;
    while(input >> line) {
        for (auto& c: line) {
            cave.push_back(c-'0');
        }
    }
    First(cave);
    Second(cave);
    return 0;
}