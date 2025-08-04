#include <bits/stdc++.h>
using namespace std;

int main() {
    string s; cin >> s;
    int sm = 0;
    for (int i = 0; i <= 9; ++i) {
        int tmp = 0;
        for (int j = 0; j < s.size(); ++j) {
            int val;
            if (s[j] == '*') val = i;
            else val = s[j] - '0';
            if (j % 2) tmp += val * 3;
            else tmp += val;
        }
        if (tmp % 10 == 0) {
            cout << i;
            break;
        }
    }
}