#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int X; cin >> X;
    vector<int> v;
    for (int i = 0; i < 25; ++i) v.push_back(0);
    for (int i = 0; i < 25; ++i) v.push_back(1);
    int cnt = 625;
    while (cnt > X) {
        for (int i = 0; i < 49; ++i) {
            if (v[i] == 0 && v[i + 1] == 1) {
                swap(v[i], v[i + 1]);
                break;
            }
        }
        --cnt;
    }
    for (int i = 0; i < 50; ++i) {
        if (v[i] == 0) cout << 'A';
        else cout << 'C';
        if (i + 1 != 50) cout << 'R';
    }
}