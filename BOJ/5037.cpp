#include <bits/stdc++.h>
using namespace std;

// (n + 1) * i + j, (n + 1) * (i + 1) + (j + 1) \
// (n + 1) * i + (j + 1), (n + 1) * (i + 1) + j /

/**
 * Description: Union-Find data structure with rollback capability.
 *  Supports merging sets and rolling back merge operations to a previous state.
 *  Crucial for algorithms like dynamic connectivity.
 *  The `find` operation does NOT use path compression, which is necessary for the rollback to function correctly.
 * Time: `merge` and `find` are O(\log N). `rollback` is proportional to the number of merges to undo.
 */
struct UnionFindRollback {
    vector<int> par, rk;
    vector<tuple<int, int, int>> st;

    UnionFindRollback() = default;
    UnionFindRollback(int sz) {
        par.resize(sz);
        rk.resize(sz);
        for (int i = 0; i < sz; ++i) par[i] = i;
    }
    int time() { return st.size(); }
    void rollback(int t) {
        while (st.size() > t) {
            auto [v, p, r] = st.back(); st.pop_back();
            par[v] = p;
            rk[v] = r;
        }
    }
    int find(int x) {
        while (par[x] != x) x = par[x];
        return x;
    }
    void merge(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return;
        st.push_back({x, par[x], rk[x]});
        st.push_back({y, par[y], rk[y]});
        if (rk[x] > rk[y]) swap(x, y);
        par[x] = y;
        if (rk[x] == rk[y]) ++rk[y];
    }
} uf;

int n;
int remain[64];
int current[64];
int cnt[64];
int answer[49];

void dfs(int row, int col) {
    if (row == n) {
        for (int i = 0; i < n + 1; ++i) for (int j = 0; j < n + 1; ++j) {
            if (cnt[i * (n + 1) + j] <= 4) assert(cnt[i * (n + 1) + j] == current[i * (n + 1) + j]);
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (answer[i * n + j]) cout << '/';
                else cout << '\\';
            }
            cout << '\n';
        }
        exit(EXIT_SUCCESS);
    }

    int nrow = col == n - 1 ? row + 1 : row;
    int ncol = (col + 1) % n;

    int v[2];
    int pv[2];
    int pa;
    for (int i = 0; i < 2; ++i) {
        if (i == 0) v[0] = (n + 1) * row + col, v[1] = (n + 1) * (row + 1) + (col + 1);
        else v[0] = (n + 1) * row + (col + 1), v[1] = (n + 1) * (row + 1) + col;

        if (uf.find(v[0]) == uf.find(v[1])) continue;
        if (current[v[0]] + 1 > cnt[v[0]]) continue;
        if (current[v[1]] + 1 > cnt[v[1]]) continue;

        bool skip = false;
        for (int j = row; j < row + 2; ++j) for (int k = col; k < col + 2; ++k) {
            int edge = (n + 1) * j + k;
            if (cnt[edge] == 5) continue;
            int tmp = current[edge] + remain[edge];
            if (edge != v[0] && edge != v[1]) --tmp;
            if (tmp < cnt[edge]) skip = true;
        }
        if (skip) continue;

        
        int tm = uf.time();

        uf.merge(v[0], v[1]);
        pa = answer[row * n + col];
        answer[row * n + col] = i;
        ++current[v[0]];
        ++current[v[1]];
        for (int j = row; j < row + 2; ++j) for (int k = col; k < col + 2; ++k) {
            int edge = (n + 1) * j + k;
            --remain[edge];
        }
        

        dfs(nrow, ncol);

        answer[row * n + col] = pa;
        uf.rollback(tm);
        --current[v[0]];
        --current[v[1]];
        for (int j = row; j < row + 2; ++j) for (int k = col; k < col + 2; ++k) {
            int edge = (n + 1) * j + k;
            ++remain[edge];
        }
        
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n;

    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {
        ++remain[(n + 1) * i + j];
        ++remain[(n + 1) * (i + 1) + (j + 1)];
        ++remain[(n + 1) * i + (j + 1)];
        ++remain[(n + 1) * (i + 1) + j];
    }

    for (int i = 0; i < n + 1; ++i) {
        string s; cin >> s;
        for (int j = 0; j < n + 1; ++j) {
            if (s[j] == '.') cnt[i * (n + 1) + j] = 5;
            else cnt[i * (n + 1) + j] = s[j] - '0';
        }
    }
    uf = UnionFindRollback {(n + 1) * (n + 1)};
    dfs(0, 0);
    exit(EXIT_FAILURE);
}