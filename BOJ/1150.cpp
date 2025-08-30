#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n, k;
ll s[100000], pfxsm[100000];
bool vis[100000];
int prv[100000], nxt[100000];

void update(int x) {
    if (prv[x] != -1) nxt[prv[x]] = nxt[x];
    if (nxt[x] != n) prv[nxt[x]] = prv[x];
}

ll val(int x, int y) {
    ll ret = pfxsm[y] - pfxsm[y - 1];
    if (x - 1 >= 0) ret -= pfxsm[x - 1];
    if (x - 2 >= 0) ret += pfxsm[x - 2];
    return ret;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n >> k;
    for (int i = 0; i < n; ++i) cin >> s[i];
    for (int i = 0; i < n; ++i) {
        if (i == 0 || i == 1) pfxsm[i] = s[i];
        else pfxsm[i] = pfxsm[i - 2] + s[i];
    }
    for (int i = 0; i < n; ++i) {
        prv[i] = i - 1;
        nxt[i] = i + 1;
    }
    priority_queue<pair<ll, pair<int, int>>> pq;
    for (int i = 0; i + 1 < n; ++i) pq.push(make_pair(-val(i, i + 1), make_pair(i, i + 1)));
    ll ans = 0;
    int cnt = 0;
    
    while (cnt < k) {
        auto [dis, v] = pq.top(); pq.pop();
        if (vis[v.first] || vis[v.second]) continue;
        ans += -dis;
        if (prv[v.first] != -1 && nxt[v.second] != n) pq.push(make_pair(-val(prv[v.first], nxt[v.second]) + val(prv[v.first] + 1, nxt[v.second] - 1),
        make_pair(prv[v.first], nxt[v.second])));
        vis[v.first] = true;
        update(v.first);
        vis[v.second] = true;
        update(v.second);
        ++cnt;
    }
    cout << ans;
}