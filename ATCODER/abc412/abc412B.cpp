#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
    string S, T; cin >> S >> T;
    int n = S.size();
    for (int i = 1; i < n; ++i) if ('A' <= S[i] && S[i] <= 'Z') {
        bool flag = false;
        for (auto j: T) if (j == S[i - 1]) {
            flag = true;
            break;
        }
        if (!flag) {
            cout << "No";
            return;
        }
    }
    cout << "Yes";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}