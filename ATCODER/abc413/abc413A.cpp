#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
    int N, M; cin >> N >> M;
    int sm = 0;
    for (int i = 0; i < N; ++i) {
        int A; cin >> A;
        sm += A;
    }
    if (sm <= M) cout << "Yes";
    else cout << "No";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}