#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>

using namespace std;

vector<vector<int>> markHorizontal(int x1, int x2, int y, vector<vector<int>> floor) {
    int start;
    int end;
    if (x1 < x2) {
        start = x1;
        end = x2;
    } else {
        start = x2;
        end = x1;
    }
    for (int i = start; i <= end; i++) {
        floor[y][i]++;
    }
    return floor;
}

vector<vector<int>> markVertical(int y1, int y2, int x, vector<vector<int>> floor) {
    int start;
    int end;
    if (y1 < y2) {
        start = y1;
        end = y2;
    } else {
        start = y2;
        end = y1;
    }
    for (int i = start; i <= end; i++) {
        floor[i][x]++;
    }
    return floor;
}

vector<vector<int>> markDiagonal(int x1, int y1, int x2, int y2, vector<vector<int>> floor) {
    int n = abs(x1 - x2);
    vector<int> x, y;
    if (x1 < x2 && y1 < y2) {
        while (x1 <= x2) {
            x.push_back(x1);
            y.push_back(y1);
            x1++;
            y1++;
        }
    } else if (x1 < x2 && y1 > y2) {
        while (x1 <= x2) {
            x.push_back(x1);
            y.push_back(y1);
            x1++;
            y1--;
        }
    } else if (x1 > x2 && y1 < y2) {
        while (x1 >= x2) {
            x.push_back(x1);
            y.push_back(y1);
            x1--;
            y1++;
        }
    } else {
        while (x1 >= x2) {
            x.push_back(x1);
            y.push_back(y1);
            x1--;
            y1--;
        }
    }
    for (int i = 0; i <= n; i++) {
        floor[y[i]][x[i]]++;
    }
    return floor;
}

int overlaps(vector<vector<int>> floor) {
    int counter = 0;
    for (auto& y : floor) {
        for (auto& x : y) {
            if (x >= 2) {
                counter++;
            }
        }
    }
    return counter;
}


int first(vector<vector<int>> lines, vector<vector<int>> floor) {
    int x1, y1, x2, y2;
    /*floor = markHorizontal(916, 922, 5, floor);
    floor = markVertical(6, 2, 920, floor);
    floor = markVertical(0, 989)*/
    
    for (auto& line : lines) {
        x1 = line[0];
        y1 = line[1];
        x2 = line[2];
        y2 = line[3];
        if (x1 != x2 && y1 == y2) {
            floor = markHorizontal(x1, x2, y1, floor);
        } else if (y1 != y2 && x1 == x2) {
            floor = markVertical(y1, y2, x1, floor);
        }
    }
    cout << "Part 1: " << overlaps(floor) << endl;
    return 0;
}

int second(vector<vector<int>> lines, vector<vector<int>> floor) {
    int x1, y1, x2, y2;
    for (auto& line : lines) {
        x1 = line[0];
        y1 = line[1];
        x2 = line[2];
        y2 = line[3];
        if (x1 != x2 && y1 == y2) {
            floor = markHorizontal(x1, x2, y1, floor);
        } else if (y1 != y2 && x1 == x2) {
            floor = markVertical(y1, y2, x1, floor);
        } else {
            floor = markDiagonal(x1, y1, x2, y2, floor);
        }
    }
    cout << "Part 2: " << overlaps(floor) << endl;
    return 0;
}
int main() {
    ifstream infile("day5.txt");
    int x1, y1, x2, y2;
    int x_max = 0;
    int y_max = 0;
    vector<int> line;
    vector<vector<int>> lines;
    vector<vector<int>> floor;
    string start, arrow, end;
    while (infile >> start >> arrow >> end) {
        stringstream pos0(start);
        pos0 >> x1;
        pos0.ignore(1);
        pos0 >> y1;
        stringstream pos1(end);
        pos1 >> x2;
        pos1.ignore(1);
        pos1 >> y2;
        if (x1 >= x2) {
            if (x1 > x_max) {
                x_max = x1;
            }
        } else if (x2 > x_max) { 
            x_max = x2;
        }
        if (y1 >= y2) {
            if (y1 > y_max) {
                y_max = y1;
            }
        } else if (y2 > y_max) {
            y_max = y2;
        }
        line = {x1, y1, x2, y2};
        lines.push_back(line);
    }
    
    for (int i=0; i<y_max+1; i++) {
        vector<int> x(x_max+1, 0);
        floor.push_back(x);
    }
    cout << lines.size() << endl;
    first(lines, floor);
    second(lines, floor);
}