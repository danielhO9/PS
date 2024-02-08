#include <bits/stdc++.h>
using namespace std;
int s[8];

void solution() {
    if (s[0] == 1) {
        for (int i = 1; i < 8; ++i) {
            if (s[i] != s[i - 1] + 1) { cout << "mixed"; return; }
        }
        cout << "ascending";
        return;
    }
    if (s[0] == 8) {
        for (int i = 1; i < 8; ++i) {
            if (s[i] != s[i - 1] - 1) { cout << "mixed"; return; }
        }
        cout << "descending";
        return;
    }
    cout << "mixed";
    return;
}

int main() {
    for (int i = 0; i < 8; ++i) cin >> s[i];
    solution();
}