#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <bits/stdc++.h>

char Oposite(int c) {
    // <, [ or {
    if (c == 60 || c == 91 || c == 123) {
        return c + 2;
    // >, ], or }
    } else if (c == 62 || c == 93 || c == 125) {
        return c - 2;
    // (
    } else if (c == 40) {
        return 41;
    // )
    } else {
        return 40;
    }
}

int ValueOfBracket(char c) {
    int value;
    int x = c;
    switch(x) {
        case 41:
            // )
            value = 3;
            break;
        case 62:
            // >
            value = 25137;
            break;
        case 93:
            // ]
            value = 57;
            break;
        case 125:
            // }
            value = 1197;
            break;
    }
    return value;
}

int ValueOf(char c) {
    int value;
    int x = c;
    switch(x) {
        case 41:
            // )
            value = 1;
            break;
        case 62:
            // >
            value = 4;
            break;
        case 93:
            // ]
            value = 2;
            break;
        case 125:
            // }
            value = 3;
            break;
    }
    return value;
}

long long GetScore(std::string line) {
    std::vector<char> opening_brackets;
    for (auto& c: line) {
        if (c == 40 || c == 60 || c == 91 || c == 123) {
            opening_brackets.push_back(c);
        } else {
            opening_brackets.pop_back();
        }
    }
    long long score = 0;
    std::reverse(opening_brackets.begin(), opening_brackets.end());
    for (auto& c: opening_brackets) {
        score *= 5;
        score += ValueOf(Oposite(c));
    }
    return score;
}

int FirstIllegalCharacter(std::string line) {
    std::vector<char> opening_brackets;
    int value;
    for (auto& c: line) {
        if (c == 40 || c == 60 || c == 91 || c == 123) {
            opening_brackets.push_back(c);
        } else {
            if (Oposite(c) == opening_brackets.back()) {
                opening_brackets.pop_back();
            } else {
                value =  ValueOfBracket(c);
                break;
            }
        }
    }
    return value;
}

void Solve(std::vector<std::string>& lines) {
    int sum = 0;
    std::vector<long long> scores;
    for (auto& line: lines) {
        int k = FirstIllegalCharacter(line);
        if (k > 0) {
            sum += k;
        } else {
            scores.push_back(GetScore(line));
        }
    }
    sort(scores.begin(), scores.end());
    long long middle_score = scores[scores.size()/2];
    std::cout << sum << std::endl;
    std::cout << middle_score << std::endl;
}

int main() {
    std::ifstream infile("day10.txt");
    std::string line;
    std::vector<std::string> lines;
    while (infile >> line) {
        lines.push_back(line);
    }
    Solve(lines);
    return 0;
}