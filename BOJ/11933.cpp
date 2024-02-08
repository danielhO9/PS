#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

// (S + T + N) * logN으로.
// 각 centroid마다 dfs로 dep를 확인하고, 그때마다 ret 값 변경

int N, Q;
vector<pair<int, LL>> graph[500000];
int sz[500000]; bool visited[500000];
vector<int> fac[500000]; LL dis[200000];
vector<int> changed; LL ret[100000];

int getSize(int v, int p){
    sz[v] = 1;
    for(auto [i, _]: graph[v]) if(i != p && !visited[i]) sz[v] += getSize(i, v);
    return sz[v];
}

int getCent(int v, int p, int csz){
    for(auto [i, _]: graph[v]) if(i != p && !visited[i] && sz[i] * 2 > csz) return getCent(i, v, csz);
    return v;
}

void dfs(int v, int p, LL ld) {
    for (int i: fac[v]) if (dis[i] > ld) {
        dis[i] = ld;
        ret[i / 2] = min(ret[i / 2], dis[(i / 2) * 2] + dis[(i / 2) * 2 + 1]);
        changed.push_back(i);
    }
    for (auto [i, d]: graph[v]) if (!visited[i] && i != p) dfs(i, v, ld + d);
}

void dnc(int v) {
    getSize(v, -1); int csz = sz[v]; int cent = getCent(v, -1, csz); visited[cent] = true;
    for (int i: fac[cent]) { dis[i] = 0LL; ret[i / 2] = min(ret[i / 2], dis[(i / 2) * 2] + dis[(i / 2) * 2 + 1]); changed.push_back(i); }
    for (auto [i, d]: graph[cent]) if (!visited[i]) dfs(i, cent, d);
    for (int i: changed) dis[i] = 5e13;
    changed.clear();
    for (auto [i, _]: graph[cent]) if (!visited[i]) dnc(i);
}


int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> Q; int x, y; LL z;
    for (int i = 0; i < N - 1; ++i) {
        cin >> x >> y >> z;
        graph[x].push_back({y, z});
        graph[y].push_back({x, z});
    }
    int facnum = 0, temp;
    for (int i = 0; i < Q; ++i) {
        cin >> x >> y;
        for (int j = 0; j < x; ++j) {
            cin >> temp;
            fac[temp].push_back(facnum);
        }
        ++facnum;
        for (int j = 0; j < y; ++j) {
            cin >> temp;
            fac[temp].push_back(facnum);
        }
        ++facnum;
    }
    fill_n(dis, 200000, 5e13);
    fill_n(ret, 100000, 5e13);
    dnc(1);
    for (int i = 0; i < Q; ++i) cout << ret[i] << "\n";
    return 0;
}