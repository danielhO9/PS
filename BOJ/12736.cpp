#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
int N, M;
LL C[300001], a[300001], b[300001];
vector<int> tree[300001];
priority_queue<LL> Q[300001];

void combine(priority_queue<LL>& v, priority_queue<LL>& u) {
    if (v.size() < u.size()) swap(v, u);
    while (!u.empty()) {
        v.push(u.top()); u.pop();
    }
}

void dfs(int v) {
    if (tree[v].empty()) {
        Q[v].push(C[v]); Q[v].push(C[v]);
        a[v] = 1; b[v] = -C[v];
        return;
    }
    for (auto i: tree[v]) {
        dfs(i);
        a[v] += a[i];
        b[v] += b[i];
        combine(Q[v], Q[i]);
    }
    while (a[v] > 1) {
        --a[v];
        b[v] += Q[v].top();
        Q[v].pop();
    }
    LL f = Q[v].top(); Q[v].pop();
    LL s = Q[v].top(); Q[v].pop();
    Q[v].push(f + C[v]); Q[v].push(s + C[v]);
    b[v] -= C[v];
}

int main() {
    cin >> N >> M; int temp;
    for (int i = 2; i <= N + M; ++i) {
        cin >> temp >> C[i];
        tree[temp].push_back(i);
    }
    dfs(1);
    if (a[1] > 0) { b[1] += Q[1].top(); }
    cout << b[1];
}