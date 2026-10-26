#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N;
int A[400000];
vector<int> idx[200001];
map<pair<int, int>, int> m; 

void solve() {
    cin >> N;
    for (int i = 1; i <= N; ++i) idx[i].clear();
    m.clear();
    for (int i = 0; i < 2 * N; ++i) {
        cin >> A[i];
        idx[A[i]].push_back(i);
    }
    int ans = 0;
    for (int i = 0; i + 1 < 2 * N; ++i) {
        // i, i + 1
        if (A[i] == A[i + 1]) continue;
        int a = A[i], b = A[i + 1];
        if (idx[a][0] + 1 == idx[a][1]) continue;
        if (idx[b][0] + 1 == idx[b][1]) continue;
        int aa, bb;
        for (auto j: idx[a]) if (j != i) aa = j;
        for (auto j: idx[b]) if (j != i + 1) bb = j;
        if (abs(aa - bb) == 1) {
            if (a > b) swap(a, b);
            if (m[{a, b}] == 0) {
                ++ans;
                m[{a, b}] = 1;
            }
        }
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}