#include <bits/stdc++.h>
using namespace std;

int Q, sz = 0;
pair<int, int> query[100001];
map<int, pair<int, int>> points;
vector<int> graph[100001];
int dep[100001], parents[100001][17], root[100001];

void dfs(int v, int p) {
    parents[v][0] = p; dep[v] = dep[p] + 1;
    for (auto i: graph[v]) if (i != p) dfs(i, v);
}

void getParents(int num) {
    for (int i = 1; i <= sz; ++i) parents[i][num] = parents[parents[i][num - 1]][num - 1];
}

int LCA(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    int dif = dep[u] - dep[v];
    for (int i = 0; dif; ++i) {
        if (dif % 2) u = parents[u][i];
        dif /= 2;
    }
    if (u != v) {
        for (int i = 16; i >= 0; --i) {
            if (parents[u][i] != -1 && parents[u][i] != parents[v][i]) {
                u = parents[u][i]; v = parents[v][i];
            }
        }
        u = parents[u][0];
    }
    return u;
}

int dis(int u, int v) { return dep[u] + dep[v] - 2 * dep[LCA(u, v)]; }

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> Q; char c; int v;
    for (int i = 0; i < Q; ++i) {
        cin >> c >> v;
        if (c == 'B') {
            ++sz;
            query[i] = {0, sz};
            if (v == -1) {
                root[sz] = sz; points[sz] = {0, 0};
            }
            else {
                graph[sz].push_back(v); graph[v].push_back(sz);
                root[sz] = root[v];
            }
        } else query[i] = {1, v};
    }
    for (auto i: points) dfs(i.first, 0);
    for (int i = 1; i < 17; ++i) getParents(i);

    int rt, dis1, dis2, dis3;
    for (auto i: query) {
        if (i.second == 0) break;
        if (i.first) {
            rt = root[i.second];
            cout << max(dis(i.second, points[rt].first), dis(i.second, points[rt].second)) << "\n";
        } else {
            rt = root[i.second];
            if (points[rt].first == 0) points[rt] = {i.second, i.second};
            else {
                dis1 = dis(points[rt].first, points[rt].second);
                dis2 = dis(points[rt].first, i.second);
                dis3 = dis(points[rt].second, i.second);
                if (dis1 < dis2) {
                    points[rt] = {points[rt].first, i.second};
                    if (dis2 < dis3) points[rt] = {points[rt].second, i.second};
                } else if (dis1 < dis3) points[rt] = {points[rt].second, i.second};
            }
        }
    }
    return 0;
}