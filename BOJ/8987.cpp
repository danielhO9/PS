#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N, K, n;
vector<ll> x, y;
ll psmx[150001], val[150001];
int par[150001], mx_leaf[150001], l[150001], r[150001], node[150001];
vector<int> adj[150001];

void dfs(int v) {
    if (adj[v].empty()) {
        mx_leaf[v] = v;
        return;
    }
    for (int u: adj[v]) dfs(u);

    ll mx = 0;
    for (int u: adj[v]) mx = max(mx, val[mx_leaf[u]]);
    for (int u: adj[v]) if (val[mx_leaf[u]] == mx) {
        val[mx_leaf[u]] += val[v];
        mx_leaf[v] = mx_leaf[u];
        break;
    }
}


int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N;
    ll prvx = 0;
    x.push_back(0);
    y.push_back(-1);
    for (int i = 0; i < N; ++i) {
        ll xcor, ycor; cin >> xcor >> ycor;
        if (i == 0 || i + 1 == N || i % 2) continue;
        x.push_back(xcor - prvx);
        y.push_back(ycor);
        prvx = xcor;
    }
    x.push_back(0);
    y.push_back(-1);

    n = x.size(); n -= 2;

    for (int i = 1; i <= n + 1; ++i) psmx[i] = psmx[i - 1] + x[i];

    stack<int> st;
    for (int i = 0; i <= n + 1; ++i) {
        while (!st.empty() && y[st.top()] > y[i]) {
            int j = st.top(); st.pop();
            r[j] = i;
        }
        st.push(i);
    }
    while (!st.empty()) st.pop();
    for (int i = n + 1; i >= 0; --i) {
        while (!st.empty() && y[st.top()] > y[i]) {
            int j = st.top(); st.pop();
            l[j] = i;
        }
        st.push(i);
    }
    
    memset(par, -1, sizeof(par));
    for (int i = 0; i <= n + 1; ++i) node[i] = i;
    vector<int> index(n);
    for (int i = 0; i < n; ++i) index[i] = i + 1;
    sort(index.begin(), index.end(), [&](const int& a, const int& b) {
        if (y[a] == y[b]) return a < b;
        return y[a] < y[b];
    });
    for (int i = 1; i <= n; ++i) {
        val[i] = psmx[r[i] - 1];
        val[i] -= psmx[l[i]];
    }

    unordered_map<ll, int> m;
    for (auto i: index) {
        if (m.find(y[i]) != m.end() && l[m[y[i]]] == l[i] && r[m[y[i]]] == r[i]) {
            node[i] = m[y[i]];
            continue;
        }
        if (y[l[i]] < y[r[i]]) par[i] = node[r[i]];
        else par[i] = node[l[i]];
        adj[par[i]].push_back(i);
        m[y[i]] = i;
    }

    cin >> K;
    int rt = -1;
    for (int i = 1; i <= n; ++i) {
        if (par[i] == 0) {
            assert(rt == -1);
            rt = i;
            val[i] *= y[i];
        } else {
            val[i] *= y[i] - y[par[i]];
        }
    }
    assert(rt != -1);
    dfs(rt);
    priority_queue<ll> pq;
    for (int i = 1; i <= n; ++i) if (node[i] == i && adj[i].empty()) pq.push(val[i]);
    ll ans = 0;
    K = min(K, (int) pq.size());
    while (K--) {
        ans += pq.top(); pq.pop();
    }
    cout << ans;
}