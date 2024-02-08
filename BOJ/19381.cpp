#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

LL N, C[100001], ans;
vector<LL> tree[100001];

void combine(priority_queue<LL>& v, priority_queue<LL>& u) {
    if (v.size() < u.size()) swap(v, u);
    while (!u.empty()) {
        v.push(u.top()); u.pop();
    }
}

priority_queue<LL> dfs(int v, LL d) {
    priority_queue<LL> partial;
    for (auto i: tree[v]) {
        auto temp = dfs(i, d + 1);
        combine(partial, temp);
    }
    partial.push(C[v] + d);
    if (C[v] + d < partial.top()) {
        ans += partial.top() - C[v] - d;
        partial.pop();
        partial.push(C[v] + d);
    }
    return partial;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> C[1]; int p;
    for (LL i = 2; i <= N; ++i) {
        cin >> p >> C[i];
        tree[p].push_back(i);
    }
    dfs(1, 1);
    cout << ans;
}