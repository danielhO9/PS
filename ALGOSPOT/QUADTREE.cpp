#include <bits/stdc++.h>
using namespace std;

// xbwxwbbwb
deque<char> divide(deque<char>& data) {
    if (data.front() == 'w') return {'w'};
    else if (data.front() == 'b') return {'b'};
    else {
        deque<deque<char>> send(4);
        deque<int> temp = {0};
        data.pop_front();
        for (char i: data) {
            send[temp.front()].push_back(i);
            if (i == 'x') temp.push_back(0);
            else temp.back()++;
            while (!temp.empty() && temp.back() == 4) {
                temp.pop_back();
                if (!temp.empty()) temp.back()++;
            }
        }
        deque<char> ret = {'x'};
        for (char i: divide(send[2])) ret.push_back(i);
        for (char i: divide(send[3])) ret.push_back(i);
        for (char i: divide(send[0])) ret.push_back(i);
        for (char i: divide(send[1])) ret.push_back(i);
        return ret;
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int C; cin >> C; string s;
    for (int i = 0 ; i < C; ++i) {
        cin >> s;
        deque<char> chars;
        for (char j: s) chars.push_back(j);
        deque<char> ans = divide(chars);
        for (char j: ans) cout << j;
        cout << "\n";
    }
    return 0;
}