#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <string>
#include <map>
#include <cstring>

using namespace std;

string findOne(vector<string> pattern) {
    bool found = false;
    string output;
    for (int i=0; i<pattern.size(); i++) {
        if (pattern[i].length() == 2) {
            output = pattern[i];
            found = true;
            break;
        }
        if (found) {
            break;
        }
    }
    return output;
}

string findTwo(string three, string five, vector<string> pattern) {
    bool found = false;
    string output;
    for (auto& s: pattern) {
        if (s.length() == 5 && s != three && s != five) {
            output = s;
            found = true;
            break;
        }
        if (found) {
            break;
        }
    }
    return output;
}

string findThree(string seven, vector<string> pattern) {
    bool found = false;
    string output;
    for (auto& s: pattern) {
        if (s.length() == 5) {
            bool seveninstring = true;
            for (auto& c: seven) {
                if (s.find(c) == string::npos) {
                    seveninstring = false;
                    break;
                }
            }
            if (seveninstring) {
                output = s;
                found = true;
                break;
            }
        }
        if (found) {
            break;
        }
    }
    return output;
}

string findFour(vector<string> pattern) {
    bool found = false;
    string output;
    for (int i=0; i<pattern.size(); i++) {
        if (pattern[i].length() == 4) {
            output = pattern[i];
            found = true;
            break;
        }
        if (found) {
            break;
        }
    }
    return output;
}

string findFive(string six, vector<string> pattern) {
    bool found = false;
    string output;
    for (auto& s: pattern) {
        if (s.length() == 5) {
            bool stringinsix = true;
            for (auto& c: s) {
                if (six.find(c) == string::npos) {
                    stringinsix = false;
                    break;
                }
            }
            if (stringinsix) {
                output = s;
                found = true;
                break;
            }
        }
        if (found) {
            break;
        }
    }
    return output;
}

string findSix(string nine, string zero, vector<string> pattern) {
    bool found = false;
    string output;
    for (auto& s: pattern) {
        if (s.length() == 6 && s != nine && s != zero) {
            output = s;
            found = true;
            break;
        }
        if (found) {
            break;
        }
    }
    return output;
}

string findSeven(vector<string> pattern) {
    bool found = false;
    string output;
    for (int i=0; i<pattern.size(); i++) {
        if (pattern[i].length() == 3) {
            output = pattern[i];
            found = true;
            break;
        }
        if (found) {
            break;
        }
    }
    return output;
}

string findEight(vector<string> pattern) {
    bool found = false;
    string output;
    for (int i=0; i<pattern.size(); i++) {
        if (pattern[i].length() == 7) {
            output = pattern[i];
            found = true;
            break;
        }
        if (found) {
            break;
        }
    }
    return output;
}

string findNine(string four, vector<string> pattern) {
    bool found = false;
    string output;
    for (auto& s: pattern) {
        if (s.length() == 6) {
            bool fourinstring = true;
            for (auto& c: four) {
                if (s.find(c) == string::npos) {
                    fourinstring = false;
                    break;
                }
            }
            if (fourinstring) {
                output = s;
                found = true;
                break;
            }
        }
        if (found) {
            break;
        }
    }
    return output;
}

string findZero(string seven, string nine, vector<string> pattern) {
    bool found = false;
    string output;
    for (auto& s: pattern) {
        if (s.length() == 6) {
            bool seveninstring = true;
            for (auto& c: seven) {
                if (s.find(c) == string::npos) {
                    seveninstring = false;
                    break;
                }
            }
            if (seveninstring && s!= nine) {
                output = s;
                found = true;
                break;
            }
        }
        if (found) {
            break;
        }
    }
    return output;
}

int getOutput(vector<string> mapping, vector<string> output) {
    int sum = 0;
    int divisor = 1;
    for (auto& s: output) {
        for (int i=0; i<10; i++) {
            bool oinmapping = true;
            for (auto& c: s) {
                if (mapping[i].find(c) == string::npos) {
                    oinmapping = false;
                    break;
                }
            }
            if (oinmapping && s.length() == mapping[i].length()) {
                sum += 1000/divisor*i;
                divisor *= 10;
                break;
            }
        }
    }
    return sum;
}

int part1(map<int,vector<string>> outputs, int index) {
    int count = 0;
    int len;
    for (int i=0; i<index; i++) {
        for (int j=0; j<4; j++) {
            len = outputs[i][j].length();
            if (len == 2 || len == 3 || len == 4 || len == 7) {
                count++;
            }
        }
    }
    cout << count << endl;
    return 0;
}

int part2(map<int,vector<string>> patterns, map<int,vector<string>> outputs, int index) {
    vector<string> pattern;
    vector<string> output;
    vector<string> mapping;
    string one, two, three, four, five, six, seven, eight, nine, zero;
    int sum = 0;
    int n;
    for (int i=0; i<index;i++) {
        pattern = patterns[i];
        output = outputs[i];
        one = findOne(pattern);
        seven = findSeven(pattern);
        four = findFour(pattern);
        eight = findEight(pattern);
        nine = findNine(four, pattern);
        zero = findZero(seven, nine, pattern);
        six = findSix(nine, zero, pattern);
        three = findThree(seven, pattern);
        five = findFive(six, pattern);
        two = findTwo(three, five, pattern);
        mapping = {zero, one, two, three, four, five, six, seven, eight, nine};
        sum += getOutput(mapping, output);
    }
    cout << sum << endl;
    return 0;
}

int main() {
    ifstream infile("day8.txt");
    string digit;
    vector<string> pattern;
    vector<string> output;
    map<int,vector<string>> patterns;
    map<int,vector<string>> outputs;
    int index = 0;
    while (infile >> digit) {
        pattern = {};
        output = {};
        pattern.push_back(digit);
        for (int i=0; i<9; i++) {
            infile >> digit;
            pattern.push_back(digit);
        }
        patterns[index] = pattern;
        // ignoring delimiter
        infile >> digit;

        for (int i=0; i<4; i++) {
            infile >> digit;
            output.push_back(digit);
        }
        outputs[index] = output;
        index++;
    }
    // prints solution to part 1
    part1(outputs, index);
    part2(patterns, outputs, index);
}