#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

int N, Q;
vector<pair<int, LL>> graph[100000];
int sz[100000], centP[100000]; bool visited[100000];
int dep[100000], parents[100000][17]; LL dis[100000];
bool blue[100000];

map<int, LL> ret[100000]; map<int, int> ret_cnt[100000];
LL ret_sum[100000]; int ret_cnt_sum[100000];

void dfs(int v, int p, LL d) {
    parents[v][0] = p;
    if (p == -1) {
        dep[v] = 1; dis[v] = 0LL;
    } else {
        dep[v] = dep[p] + 1; dis[v] = dis[p] + d;
    }
    for (auto [i, nd]: graph[v]) if (i != p) dfs(i, v, nd);
}

void getParents(int num) {
    for (int i = 0; i < N; ++i) {
        if (parents[i][num - 1] == -1) parents[i][num] = -1;
        else parents[i][num] = parents[parents[i][num - 1]][num - 1];
    }
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

int getSize(int v, int p){
    sz[v] = 1;
    for(auto [i, _]: graph[v]) if(i != p && !visited[i]) sz[v] += getSize(i, v);
    return sz[v];
}

int getCent(int v, int p, int csz){
    for(auto [i, _]: graph[v]) if(i != p && !visited[i] && sz[i] * 2 > csz) return getCent(i, v, csz);
    return v;
}

void getCentP(int v, int p) {
    getSize(v, p); int csz = sz[v]; int cent = getCent(v, p, csz);
    visited[cent] = true; centP[cent] = p;
    for (auto [i, _]: graph[cent]) if (!visited[i]) getCentP(i, cent);
}

void query1(int v) {
    if (blue[v]) return;
    blue[v] = true;
    int i = v, centp; LL dis_cent;
    ++ret_cnt_sum[i];
    while (true) {
        if (centP[i] == -1) break;
        centp = centP[i];
        dis_cent = dis[centp] + dis[v] - 2 * dis[LCA(centp, v)];
        ret[centp][i] += dis_cent;
        ret_sum[centp] += dis_cent;
        ++ret_cnt[centp][i];
        ++ret_cnt_sum[centp];
        i = centp;
    }
}

LL query2(int v) {
    LL ans = 0;
    int i = v, centp; LL dis_cent;
    ans += ret_sum[i];
    while (true) {
        if (centP[i] == -1) break;
        centp = centP[i];
        dis_cent = dis[centp] + dis[v] - 2 * dis[LCA(centp, v)];
        ans += dis_cent * (ret_cnt_sum[centp] - ret_cnt[centp][i]) + ret_sum[centp] - ret[centp][i];
        i = centP[i];
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    // input
    cin >> N >> Q;
    int x, y; LL z;
    for (int i = 0; i < N - 1; ++i) {
        cin >> x >> y >> z;
        graph[x].push_back({y, z});
        graph[y].push_back({x, z});
    }
    // dep, parents
    dfs(0, -1, 0LL); for (int i = 1; i < 17; ++i) getParents(i);
    getCentP(0, -1);
    for (int i = 0; i < Q; ++i) {
        cin >> x >> y;
        if (x == 1) query1(y);
        else cout << query2(y) << "\n";
    }
    return 0;
}