#include <bits/stdc++.h>
using namespace std;

int getSz(vector<int>& sz, vector<vector<int>>& adj, int v, int p) {
    sz[v] = 1;
    for (auto u: adj[v]) if (u != p) sz[v] += getSz(sz, adj, u, v);
    return sz[v];
}

int centroid(vector<int>& sz, vector<vector<int>>& adj, int v, int p, int N) {
    for (auto u: adj[v]) if (u != p && sz[u] * 2 > N) return centroid(sz, adj, u, v, N);
    return v; 
}

void getDep(vector<int>& dep, vector<vector<int>>& adj, int rt) {
    queue<int> q; q.push(rt); dep[rt] = 0; 
    while (!q.empty()) {
        int v = q.front(); q.pop();
        for (auto u: adj[v]) if (dep[u] == -1) {
            q.push(u);
            dep[u] = dep[v] + 1;
        }
    }
}

vector< pair<int, int> > encode_map(int N, int K, int &X, vector< pair<int, int> > E) {
    vector<vector<int>> adj(N + 1);
    vector<pair<int, int>> ret;
    for (auto& edge: E) {
        adj[edge.first].push_back(edge.second);
        adj[edge.second].push_back(edge.first);
    }
    vector<int> sz(N + 1);
    getSz(sz, adj, 1, 0);
    X = centroid(sz, adj, 1, 0, N);
    vector<int> dep(N + 1, -1);
    getDep(dep, adj, X);
    vector<vector<int>> darr(N);
    for (int i = 1; i <= N; ++i) darr[dep[i]].push_back(i);

    for (int i = 1; i < N; ++i) {
        if (K == 0) break;
        for (int j = 0; j < darr[i].size(); ++j) {
            if (K == 0) break;
            for (int k = j + 1; k < darr[i].size(); ++k) {
                if (K == 0) break;
                ret.push_back(make_pair(darr[i][j], darr[i][k]));
                --K;
            }
        }
    }
    assert(K == 0);
    return ret;
}

vector< pair<int, int> > decode_map(int N, int K, int X, vector< pair<int, int> > E) {
    vector<vector<int>> adj(N + 1);
    vector<pair<int, int>> ret;
    for (auto& edge: E) {
        adj[edge.first].push_back(edge.second);
        adj[edge.second].push_back(edge.first);
    }
    vector<int> dep(N + 1, -1);
    getDep(dep, adj, X);
    for (auto& edge: E) {
        if (dep[edge.first] != dep[edge.second]) ret.push_back(edge);
    }
    assert(ret.size() == N - 1);
    return ret;
}