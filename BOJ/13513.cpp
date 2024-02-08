#include <bits/stdc++.h>
using namespace std;

int N, M;
vector<pair<int, int>> graph[100001];
int sz[100001], centP[100001]; bool visited[100001];
int dep[100001], parents[100001][17]; int dis[100001];
bool black[100001];

// 각 정점마다 서브트리에서 온 값들을 저장, 정점에서의 값들을 저장, 각 정점에서의 값을 저장
map<int, multiset<int>> ma[100001]; multiset<int> eachAns[100001], ans;

void dfs(int v, int p, int d) {
    parents[v][0] = p;
    dep[v] = dep[p] + 1; dis[v] = dis[p] + d;
    for (auto [i, nd]: graph[v]) if (i != p) dfs(i, v, nd);
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

void getMap(int v) {
    int i = v, centp;
    eachAns[v].insert(0);
    while (true) {
        centp = centP[i];
        if (centp == 0) break;
        ma[centp][i].insert(dis[centp] + dis[v] - 2 * dis[LCA(centp, v)]);
        i = centP[i];
    }
}

void getAns(int v) {
    for (auto i: ma[v]) if (!i.second.empty()) { eachAns[v].insert(*i.second.rbegin()); }
    if (eachAns[v].size() == 1) ans.insert(0);
    else if (eachAns[v].size() >= 2) ans.insert(*eachAns[v].rbegin() + *next(eachAns[v].rbegin()));
}

void requery(int v, int lvalue, int nvalue) {
    // ans delete
    if (eachAns[v].size() == 1) ans.erase(ans.find(0));
    else if (eachAns[v].size() >= 2) ans.erase(ans.find(*eachAns[v].rbegin() + *next(eachAns[v].rbegin())));
    // eachAns change
    if (lvalue != 100000000) eachAns[v].erase(eachAns[v].find(lvalue));
    if (nvalue != 100000000) eachAns[v].insert(nvalue);
    // ans change
    if (eachAns[v].size() == 1) ans.insert(0);
    else if (eachAns[v].size() >= 2) ans.insert(*eachAns[v].rbegin() + *next(eachAns[v].rbegin()));
}
void query(int v) {
    black[v] = !black[v];
    if (black[v]) requery(v, 0, 100000000);
    else requery(v, 100000000, 0);
    int i = v, ndis, centp;
    while (true) {
        centp = centP[i];
        if (centp == 0) break;
        ndis = dis[centp] + dis[v] - 2 * dis[LCA(centp, v)];

        if (black[v]) {
            auto ite = ma[centp][i].find(ndis);
            if (ndis == *ma[centp][i].rbegin()) {
                ma[centp][i].erase(ite);
                if (ma[centp][i].empty()) requery(centp, ndis, 100000000);
                else requery(centp, ndis, *ma[centp][i].rbegin());
            } else ma[centp][i].erase(ite);
        } else {
            if (ma[centp][i].empty()) {
                ma[centp][i].insert(ndis);
                requery(centp, 100000000, ndis);
            } else if (ndis > *ma[centp][i].rbegin()) {
                requery(centp, *ma[centp][i].rbegin(), ndis);
                ma[centp][i].insert(ndis);
            } else ma[centp][i].insert(ndis);
        }

        i = centP[i];
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N;
    int x, y, z;
    for (int i = 0; i < N - 1; ++i) {
        cin >> x >> y >> z;
        graph[x].push_back({y, z});
        graph[y].push_back({x, z});
    }
    dfs(1, 0, 0); for (int i = 1; i < 17; ++i) getParents(i); getCentP(1, 0);
    for (int i = 1; i <= N; ++i) getMap(i);
    for (int i = 1; i <= N; ++i) getAns(i);
    cin >> M;
    for (int i = 0; i < M; ++i) {
        cin >> x;
        if (x == 1) {
            cin >> y;
            query(y);
        } else {
            if (ans.empty()) cout << -1 << "\n";
            else cout << *ans.rbegin() << "\n";
        }
    }
    return 0;
}
/*
3
1 2 1
1 3 1
7
2
1 1
2
1 2
2
1 3
2

*/