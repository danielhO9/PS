#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N;

void dnc(vector<int>& v, int l, int r) {
    if (l + 1 == r) return;
    int m = (l + r) / 2;
    dnc(v, l, m);
    dnc(v, m, r);
    bool flag = false;
    if (v[l] > v[m]) {
        for (int i = 0; i < m-l; ++i) swap(v[i + l], v[i + m]);
    }
    return;
}

void solve() {
    cin >> N;
    vector<int> v(1 << N);
    for (int i = 0; i < (1 << N); ++i) cin >> v[i];
    dnc(v, 0, (1 << N));
    for (int i = 0; i < (1 << N); ++i) cout << v[i] << " ";
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}