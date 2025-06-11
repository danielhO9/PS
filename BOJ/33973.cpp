#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 998244353;

int N, Q;
int A[2000][2000];
pair<int, int> query[2000];
ll fac[2001];
vector<vector<int>> v;

void part(int idx) {
    vector<vector<int>> nv;
    for (auto vec: v) {
        sort(vec.begin(), vec.end(), [idx](int a, int b) {
            return A[a][idx] < A[b][idx];
        });
        vector<int> tmp;
        for (int i = 0; i < vec.size(); ++i) {
            if (i != 0 && A[vec[i - 1]][idx] != A[vec[i]][idx]) {
                nv.push_back(tmp);
                vector<int> ttmp;
                swap(tmp, ttmp);
            }
            tmp.push_back(vec[i]);
        }
        nv.push_back(tmp);
    }
    swap(nv, v);
}

void solve() {
    cin >> N >> Q;
    for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) cin >> A[i][j];
    for (int i = 0; i < Q; ++i) cin >> query[i].first >> query[i].second;

    fac[0] = 1ll;
    for (ll i = 1; i <= 2000; ++i) {
        fac[i] = fac[i - 1] * i;
        fac[i] %= MOD;
    }
    int s = 0;
    for (int i = Q - 1; i >= 0; --i) {
        if (query[i].first == 1) {
            s = i;
            break;
        }
    }
    v.push_back({});
    for (int i = 0; i < N; ++i) v[0].push_back(i);
    // for (auto j: v[0]) cout << j << ' ';
    // cout << "\n";
    for (int i = s; i < Q; ++i) {
        part(query[i].second - 1);
        for (auto i: v) {
            // for (auto j: i) cout << j << ' ';
            // cout << "\n";
        }
    }
    ll ans = 1;
    for (auto i: v) {
        ans *= fac[i.size()];
        ans %= MOD;
    }
    cout << ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}