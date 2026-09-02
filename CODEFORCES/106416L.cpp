#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Edge {
	ll a, b;
	int s, e;
};

int n;
vector<vector<Edge>> tree;
int N, C, L, Q;
ll X[1002], V[1002], q[2000000];
int ans[2000001];

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> C >> L;
    for (int i = 0; i < N; ++i) cin >> X[i] >> V[i];
    cin >> Q;
    for (int i = 0; i < Q; ++i) cin >> q[i];
    X[N] = 0, V[N] = 0, X[N + 1] = L, V[N + 1] = 0;
    N += 2;

    vector<pair<int, int>> ints;
    for (int i = 0; i < N; ++i) for (int j = i + 1; j < N; ++j) {
        if (V[i] == V[j]) continue;
        if (V[j] < V[i] && (X[i] - X[j]) >= q[0] * (V[j] - V[i])) continue;
        if (V[j] > V[i] && (X[i] - X[j]) <= q[0] * (V[j] - V[i])) continue;
        
        if (V[i] < V[j]) ints.emplace_back(i, j);
        else ints.emplace_back(j, i);
    }

    sort(ints.begin(), ints.end(), [&](const auto& a, const auto& b) {
        if ((X[a.first] - X[a.second]) * (V[b.first] - V[b.second]) == (X[b.first] - X[b.second]) * (V[a.first] - V[a.second])) {
            return tie(V[a.first], V[a.second]) < tie(V[b.first], V[b.second]);
        }
        return (X[a.first] - X[a.second]) * (V[b.second] - V[b.first]) < (X[b.first] - X[b.second]) * (V[a.second] - V[a.first]);
    });

    // for (auto i: ints) {
    //     cout << i.first << ' ' << i.second << '\n';
    // }

    vector<int> ord(N), inv(N);
    for (int i = 0; i < N; ++i) ord[i] = i;
    sort(ord.begin(), ord.end(), [&](int a, int b) {
        ll pa = X[a] + q[0] * V[a];
        ll pb = X[b] + q[0] * V[b];

        if (pa != pb) return pa < pb;
        return V[a] < V[b];
    });

    for (int i = 0; i < N; ++i) inv[ord[i]] = i;
    // for (int i = 0; i < N; ++i) cout << ord[i] << ' ';
    // cout << '\n';
    
    vector<Edge> diff(N), input;
    
    auto erase = [&](int idx, int qnum) {
        if (idx == 0) return;
        diff[idx].e = qnum;
        if (inv[N - 2] < idx && idx <= inv[N - 1]) {
            assert(qnum >= 0);
            input.push_back(diff[idx]);
            // cout << diff[idx].a << ' ' << diff[idx].b << ' ' << diff[idx].s << ' ' << diff[idx].e << '\n';
        }
    };

    auto add = [&](int idx, int qnum) {
        if (idx == 0) return;
        diff[idx].a = V[ord[idx]] - V[ord[idx - 1]];
        diff[idx].b = X[ord[idx]] - X[ord[idx - 1]];
        diff[idx].s = qnum;
    };

    for (int i = 1; i < N; ++i) {
        add(i, 0);
    }
    
    int idx = 0;
    for (int i = 0; i < Q; ++i) {
        while (idx < ints.size()) {
            auto [ii, jj] = ints[idx];
            if (V[ii] * q[i] + X[ii] >= V[jj] * q[i] + X[jj]) break;

            ++idx;
            assert(abs(inv[ii] - inv[jj]) == 1);
            int j = min(inv[ii], inv[jj]);
            erase(j, i - 1);
            erase(j + 1, i - 1);
            if (j + 2 < N) erase(j + 2, i - 1);
            
            swap(ord[j], ord[j + 1]);
            inv[ord[j]] = j;
            inv[ord[j + 1]] = j + 1;

            add(j, i);
            add(j + 1, i);
            if (j + 2 < N) add(j + 2, i);
        }
    }
    for (int i = inv[N - 2] + 1; i <= inv[N - 1]; ++i) {
        erase(i, Q - 1);
    }

    for (auto edge: input) {
        if (edge.a == 0) {
            if (C - edge.b <= 0) {
                ++ans[edge.s];
                --ans[edge.e + 1];
            }
        } else if (edge.a > 0) {
            int l = -1, r = Q;
            while (l + 1 < r) {
                int mid = (l + r) >> 1;
                if (mid == -1) l = mid;
                else if (mid == Q || q[mid] * edge.a >= (C - edge.b)) r = mid;
                else l = mid;
            }
            if (r <= edge.e) {
                ++ans[max(r, edge.s)];
                --ans[edge.e + 1];
            }
        } else {
            int l = -1, r = Q;
            while (l + 1 < r) {
                int mid = (l + r) >> 1;
                if (mid == Q) r = mid;
                else if (mid == -1 || q[mid] * edge.a >= (C - edge.b)) l = mid;
                else r = mid;
            }
            if (edge.s <= l) {
                ++ans[edge.s];
                --ans[min(edge.e, l) + 1];
            }
        }
    }
    for (int i = 1; i < Q; ++i) ans[i] += ans[i - 1];
    for (int i = 0; i < Q; ++i) {
        if (ans[i]) cout << "Y\n";
        else cout << "N\n";
    }
}