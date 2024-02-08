#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

int sz[100000], centP[100000]; bool visited[100000];

int getSize(vector<vector<pair<int, LL>>>& graph, int v, int p){
    sz[v] = 1;
    for(auto [i, _]: graph[v]) if(i != p && !visited[i]) sz[v] += getSize(graph, i, v);
    return sz[v];
}

int getCent(vector<vector<pair<int, LL>>>& graph, int v, int p, int csz){
    for(auto [i, _]: graph[v]) if(i != p && !visited[i] && sz[i] * 2 > csz) return getCent(graph, i, v, csz);
    return v;
}

void getCentP(vector<vector<pair<int, LL>>>& graph, int v, int p) {
    getSize(graph, v, p); int csz = sz[v]; int cent = getCent(graph, v, p, csz);
    visited[cent] = true; centP[cent] = p;
    for (auto [i, _]: graph[cent]) if (!visited[i]) getCentP(graph, i, cent);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
	int N; cin >> N;
	vector<vector<pair<int, LL>>> graph(N);
    getCentP(graph, 0, -1);
}