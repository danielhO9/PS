#include <bits/stdc++.h>
using namespace std;

// 1번 쿼리
// 해당 정점이 흰색이라면 해당 정점부터 루트까지 set에 dist 추가
// 해당 정점이 검정색이라면 해당 정점부터 루트까지 set에 dist erase

// 2번 쿼리
// 해당 정점에서부터 루트까지 올라가며 각 정점의 set을 통해 연산

int N;
vector<int> graph[100001];
vector<int> sz(100001); vector<bool> visited(100001, false);
multiset<int> st[100001]; vector<bool> white(100001, false);
vector<int> centParent(100001, 0);

vector<int> dep(100001);
vector<vector<int>> parents(100001, vector<int>(17, 0));

void dfs(int v, int p) {
    parents[v][0] = p; dep[v] = dep[p] + 1;
    for (int i: graph[v]) if (i != p) dfs(i, v);
}

void getParents(int num) {
    for (int i = 1; i <= N; ++i) parents[i][num] = parents[parents[i][num - 1]][num - 1];
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
            if (parents[u][i] != 0 && parents[u][i] != parents[v][i]) {
                u = parents[u][i]; v = parents[v][i];
            }
        }
        u = parents[u][0];
    }
    return u;
}

int getSize(int v, int p){
    sz[v] = 1;
    for(auto i: graph[v]) if(i != p && !visited[i]) sz[v] += getSize(i, v);
    return sz[v];
}
int getCent(int v, int p, int csz){
    for(auto i: graph[v]) if(i != p && !visited[i] && sz[i] * 2 > csz) return getCent(i, v, csz);
    return v;
}
void getParent(int v, int p) {
    getSize(v, p); int csz = sz[v]; int cent = getCent(v, p, csz);
    visited[cent] = true; centParent[cent] = p;
    for (int i: graph[cent]) if (!visited[i]) getParent(i, cent);
}
void query1(int v) {
    white[v] = !white[v];
    int dis, i = v;
    while (true) {
        dis = dep[i] + dep[v] - 2 * dep[LCA(i, v)];
        if (white[v]) st[i].insert(dis);
        else st[i].erase(st[i].find(dis));
        if (centParent[i] == 0) break;
        i = centParent[i];
    }
}
int query2(int v) {
    if (white[v]) return 0;
    int dis, ret = N, i = v;
    while (true) {
        dis = dep[i] + dep[v] - 2 * dep[LCA(i, v)];
        if (!st[i].empty()) ret = min(ret, dis + *(st[i].begin()));
        if (centParent[i] == 0) break;
        i = centParent[i];
    }
    if (ret == N) return -1;
    return ret;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N;
    int x, y;
    for (int i = 0; i < N - 1; ++i) {
        cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    dep[0] = -1; dfs(1, 0);
    for (int i = 1; i < 17; ++i) getParents(i);
    getParent(1, 0);
    int M; cin >> M;
    for (int i = 0; i < M; ++i) {
        cin >> x >> y;
        if (x == 1) query1(y);
        else cout << query2(y) << "\n";
    }
    return 0;
}