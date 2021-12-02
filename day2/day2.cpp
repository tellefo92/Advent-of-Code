#include <iostream>
#include <fstream>

using namespace std;

int first() {
    ifstream infile("day2.txt");
    int horizontal = 0;
    int depth = 0;
    string dir;
    int n;
    while (infile >> dir >> n) {
        if(dir == "forward") {
            horizontal += n;
        } else if (dir == "down") {
            depth += n;
        } else if (dir == "up") {
            depth -= n;
        }
    }
    return horizontal*depth;
}

int second() {
    ifstream infile("day2.txt");
    int horizontal = 0;
    int depth = 0;
    int aim = 0;
    string dir;
    int n;
    while (infile >> dir >> n) {
        if(dir == "forward") {
            horizontal += n;
            depth += aim * n;
        } else if (dir == "down") {
            aim += n;
        } else if (dir == "up") {
            aim -= n;
        }
    }
    return horizontal * depth;
}

int main() {
    cout << first() << endl;
    cout << second() << endl;
}