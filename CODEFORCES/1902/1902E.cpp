#include <bits/stdc++.h>
using namespace std;

int nxt;
int to[1000001][26];
int sum[1000001];
long long res;

void add(const string& s) {
    int v = 0;
    ++sum[v];
    for (auto c : s) {
        int i = c - 'a';
        if (to[v][i] == -1)
            to[v][i] = nxt++;
        v = to[v][i];
        ++sum[v];
    }
}

void upd(const string& s) {
    int curLen = s.size();
    int v = 0;
    for (auto c : s) {
        int i = c - 'a';
        if (to[v][i] == -1) {
            res += sum[v] * 1LL * curLen;
            break;
        } else {
            int nxtV = to[v][i];
            res += (sum[v] - sum[nxtV]) * 1LL * curLen;
            --curLen;
            v = nxtV;
        }
    }
}

void solve(int n, vector <string> v) {
    nxt = 1;
    memset(sum, 0, sizeof sum);
    memset(to, -1, sizeof to);
    for(int i = 0; i < n; ++i) add(v[i]);
    for (int i = 0; i < n; ++i) {
        reverse(v[i].begin(), v[i].end());
        upd(v[i]);
    }
}
 
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    vector <string> v(n);
    for (int i = 0; i < n; ++i) cin >> v[i];
    solve(n, v);
    cout << res * 2 << endl;
}