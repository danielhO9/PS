#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll N;
ll A[200000];

void solve() {
    cin >> N;
    set<ll> s;
    for (int i = 0; i < N; ++i) cin >> A[i];
    sort(A, A+N, [](ll& a, ll& b) {
        return abs(a) < abs(b);
    });
    // for (int i = 0; i < N; ++i) cout << A[i] << ' ';
    // cout << '\n';
    for (int i = 0; i < N; ++i) s.insert(abs(A[i]));
    if (s.size() == 1) {
        int pcnt = 0, mcnt = 0;
        for (int i = 0; i < N; ++i) {
            if (A[i] > 0) ++pcnt;
            else ++mcnt;
        }
        if (abs(pcnt - mcnt) <= 1 || pcnt == 0 || mcnt == 0) cout << "Yes\n";
        else cout << "No\n";
        return;
    }
    bool flag = true;
    for (int i = 1; i + 1 < N; ++i) {
        if (A[i] * A[i] != A[i - 1] * A[i + 1]) flag = false;
    }
    if (flag) cout << "Yes\n";
    else cout << "No\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}