#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
    set<string> s;
    int N; cin >> N;
    vector<string> S(N);
    for (int i = 0; i < N; ++i) cin >> S[i];
    for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) if (i != j) {
        s.insert(S[i] + S[j]);
    }
    cout << s.size();
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}