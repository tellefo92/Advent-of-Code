#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

vector<vector<int>> markBoards(vector<vector<int>> boards, int n) {
    for (int i=0; i<boards.size(); i++) {
        for (int j=0; j<25; j++) {
            if (boards[i][j] == n) {
                boards[i][j] = 0;
                break;
            }
        }
    }
    return boards;
}

bool bingo(vector<int> board) {
    // check for horizontal bingo
    for (int i = 0; i < 5; i++) {
        bool horizontal = true;
        for (int j = 0; j < 5; j++) {
            if (board[j + 5*i] != 0) {
                horizontal = false;
                break;
            }
        }
        if (horizontal) return true;
    }
    // check for vertical bingo
    for (int i = 0; i < 5; i++) {
        bool vertical = true;
        for (int j = 0; j < 5; j++) {
            if (board[5*j + i] != 0) {
                vertical = false;
                break;
            }
        }
        if (vertical) return true;
    }
    return false;
}

int valueofBoard(vector<int> board) {
    int sum = 0;
    for (auto& n : board) {
        sum += n;
    }
    return sum;
}

vector<vector<int>> checkBoards(vector<vector<int>> boards, bool remove_all) {
    vector<vector<int>> out;
    bool bingo_board;
    for (auto& board: boards) {
        bingo_board = bingo(board);
        if (bingo_board) {
            if (!remove_all) {
                out = {};
                out.push_back(board);
                return out;
            } else {
                continue;
            }
        } else {
            if (remove_all) {
                out.push_back(board);
            }
        }
    }
    return out;
}

int first(vector<vector<int>> boards, vector<int> numbers) {
    vector<vector<int>> bingo_board;
    int tot;
    bool remove_all = false;
    for (auto& n : numbers) {
        tot = boards.size();
        boards = markBoards(boards, n);
        bingo_board = checkBoards(boards, remove_all);
        if (bingo_board.size() > 0) {
            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 5; j++) {
                    cout << bingo_board[0][j+5*i] << " ";
                }
                cout << endl;
            }
            cout << "Part 1: " << valueofBoard(bingo_board[0]) * n << endl;
            return 0;
        }
    }
    
    return 0;
}

int second(vector<vector<int>> boards, vector<int> numbers) {
    bool remove_all = true;
    vector<vector<int>> temp;
    for (auto& n : numbers) {
        temp = markBoards(boards, n);
        temp = checkBoards(temp, remove_all);
        if (temp.size() == 0) {
            cout << "Part 2: " << (valueofBoard(boards[0]) - n) * n << endl;
            return 0;
        } else {
            boards = temp;
        }
    }
    return 0;
}

int main() {
    ifstream infile("day4.txt");
    string line;
    infile >> line;
    stringstream ss(line);
    vector<int> numbers;
    vector<int> board;
    vector<vector<int>> boards;
    int i;
    int j;
    int n;
    while (ss >> j) {
        numbers.push_back(j);
        ss.ignore(1);
    }
    while (infile >> n) {
        board.push_back(n);
        if (board.size() == 25) {
            boards.push_back(board);
            board = {};
        }
    }
    vector<vector<int>> boards2 = boards;
    first(boards, numbers);
    second(boards2, numbers);
    return 0;
}