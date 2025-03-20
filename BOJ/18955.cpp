#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MOD = 998244353;

int n, m;
set<int> adj[200001];
int deg[200001];
bool vis[200001];
int nidx[200001];
ll ans = 1;

ll lpow(ll a, ll b) {
    if (b == 0) return 1;
    ll half = lpow(a, b / 2);
    half = (half * half) % MOD;
    if (b % 2) return (a * half) % MOD;
    return half;
}

template<class T>
class Matrix {
public:
    int m, n;
	vector<int> cidx;
    vector< vector<T> > entry;
    Matrix(int m_, int n_) : m(m_), n(n_), cidx(n_), entry(m_, vector<T>(n_)) { iota(cidx.begin(), cidx.end(), 0); }
    Matrix(int m_) : Matrix(m_, m_) {}
    T& operator[](const pair<int, int>& p) { return entry[p.first][cidx[p.second]]; }
    const T& operator[](const pair<int, int>& p) const { return entry[p.first][cidx[p.second]]; }

    void rswap(int i, int j) { swap(entry[i], entry[j]); }
    void rmul(int i, T x) {
        for (int j = 0; j < n; ++j) {
            entry[i][j] *= x; entry[i][j] %= MOD;
        }
    }
    void radd(int i1, int i2, T x) {
        for (int j = 0; j < n; ++j) {
            entry[i1][j] += (entry[i2][j] * x) % MOD;
            entry[i1][j] %= MOD;
        }
    }
	void cswap(int i, int j) { swap(cidx[i], cidx[j]); };
	void cmul(int j, T x) {
		for (int i = 0; i < n; ++i) {
			entry[i][cidx[j]] *= x;
            entry[i][cidx[j]] %= MOD;
		}
	}
	void cadd(int j1, int j2, T x) {
		for (int i = 0; i < n; ++i) {
			entry[i][cidx[j1]] += (entry[i][cidx[j2]] * x) % MOD;
            entry[i][cidx[j1]] %= MOD;
		}
	}
};

template<class T>
T det(Matrix<T>& A) {
	int n = A.n;
    assert(A.n == A.m);
    T ret = 1;
    for (int j = 0; j < n; ++j) {
        for (int i = j; i < n; ++i) {
            if (A[{i, j}] != 0) {
                if (i > j) {
                    A.rswap(j, i);
                    ret = -ret;
                }
                break;
            }
        }
        if (A[{j, j}] == 0) {
            return 0;
        }
        ret *= A[{j, j}];
        ret %= MOD;
        A.rmul(j, A[{j, j}] > 0 ? lpow(abs(A[{j, j}]), MOD - 2) : -lpow(abs(A[{j, j}]), MOD - 2));
        for (int i = j + 1; i < n; ++i) {
            A.radd(i, j, -A[{i, j}]);
        }
    }
    return ret;
}

void delEdge(int u, int v) {
    if (adj[u].find(v) != adj[u].end()) {
        --deg[u];
        adj[u].erase(v);
    }
    swap(u, v);
    if (adj[u].find(v) != adj[u].end()) {
        --deg[u];
        adj[u].erase(v);
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v;
        adj[u].insert(v); adj[v].insert(u);
        ++deg[u]; ++deg[v];
    }

    queue<int> q;
    for (int i = 1; i <= n; ++i) if (deg[i] == 1) q.push(i);
    while (!q.empty()) {
        int here = q.front(); q.pop();
        if (vis[here]) continue;
        if (deg[here] == 0) { cout << 0; return 0; }
        int there = *adj[here].begin();

        vis[here] = true; vis[there] = true;
        deg[here] = 0; deg[there] = 0;
        ans *= -1;
        adj[there].erase(here);
        for (auto i: adj[there]) {
            --deg[i];
            adj[i].erase(there);
            if (deg[i] == 0) { cout << 0; return 0; }
            if (deg[i] == 1) q.push(i);
        }
        adj[here].clear(); adj[there].clear();
    }
    bool flag = true;
    for (int i = 1; i <= n; ++i) if (!vis[i]) {
        if (deg[i] != 2) flag = false;
    }
    if (flag) {
        vector<int> szs;
        for (int i = 1; i <= n; ++i) if (!vis[i]) {
            int sz = 1;
            q.push(i); vis[i] = true;
            while (!q.empty()) {
                int here = q.front(); q.pop();
                for (auto there: adj[here]) if (!vis[there]) {
                    q.push(there);
                    vis[there] = true;
                    ++sz;
                }
            }
            szs.push_back(sz);
        }
        if (szs.empty()) { cout << ((ans % MOD) + MOD) % MOD; return 0; }
        for (auto i: szs) {
            assert(i != 1 && i != 2);
            ans *= 2; ans %= MOD;
            if (i % 4 == 0) ans = 0;
            if (i % 2 == 0) ans *= -2;
            ans %= MOD;
        }
        cout << ((ans % MOD) + MOD) % MOD;
        return 0;
    }
    for (int i = 1; i <= n; ++i) if (!vis[i] && deg[i] > 2) {
        vector<int> arr;
        for (int j: adj[i]) if (deg[j] == 2) arr.push_back(j);
        for (auto j: arr) if (!vis[j]) {
            vector<int> chain;
            int p = i, v = j;
            while (true) {
                if (deg[v] != 2) break;
                chain.push_back(v);
                for (auto u: adj[v]) if (u != p) {
                    p = v; v = u;
                    break;
                }
            }
            int idx = chain.size(); --idx;
            if (idx < 5) continue;
            while (idx % 4 != 1) --idx;
            for (int k = 0; k < idx; ++k) delEdge(chain[k], chain[k + 1]);
            for (int k = 1; k < idx; ++k) vis[chain[k]] = true;
            adj[chain[0]].insert(chain[idx]);
            adj[chain[idx]].insert(chain[0]);
            ++deg[chain[0]]; ++deg[chain[idx]];
        }
    }
    int num = 0;
    for (int i = 1; i <= n; ++i) if (!vis[i]) nidx[i] = num++;
    assert(num <= 1000);
    Matrix<ll> A(num);
    for (int i = 1; i <= n; ++i) if (!vis[i]) {
        for (auto j: adj[i]) A[{nidx[i], nidx[j]}] = 1;
    }
    ans *= det(A);
    ans %= MOD;
    ans += MOD;
    ans %= MOD;
    cout << ans;
}