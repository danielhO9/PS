#include <bits/stdc++.h>
using namespace std;
int N;
vector<int> graph[100001];
int c[100001], sz[100001];
vector<int> visited(100001, false);

int getSize(int v, int p){
    sz[v] = 1;
    for(auto i: graph[v]) if(i != p && !visited[i]) sz[v] += getSize(i, v);
    return sz[v];
}
int getCent(int v, int p, int csz){
    for(auto i: graph[v]) if(i != p && !visited[i] && sz[i] * 2 > csz) return getCent(i, v, csz);
    return v;
}

void getDistance(int v, int p, int d, map<int, int>& ndis) {
    if (ndis.find(c[v]) == ndis.end()) ndis[c[v]] = d;
    else ndis[c[v]] = min(ndis[c[v]], d);
    for (auto i: graph[v]) if (i != p && !visited[i]) getDistance(i, v, d + 1, ndis);
}

int solution(int v) {
    int ret = N;
    map<int, int> dis;
    getSize(v, 0); int csz = sz[v]; int cent = getCent(v, 0, csz);
    // dis에 cent 추가
    visited[cent] = true; dis[c[cent]] = 0;
    // ndis와 dis 비교
    for (auto i: graph[cent]) {
        if (visited[i]) continue;
        map<int, int> ndis;
        getDistance(i, cent, 1, ndis);
        auto ite = dis.begin(); auto nite = ndis.begin();
        while (ite != dis.end() && nite != ndis.end()) {
            if (ite->first > nite->first) ++nite;
            else if (ite->first == nite->first) {
                ret = min(ret, ite->second + nite->second); ++ite; ++nite;
            }
            else ++ite;
        }
        for (auto j: ndis) {
            if (dis.find(j.first) == dis.end()) dis[j.first] = j.second;
            else dis[j.first] = min(dis[j.first], j.second);
        }
    }
    for (int i: graph[cent]) if (!visited[i]) ret = min(ret, solution(i));
    return ret;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N;
    for (int i = 1; i <= N; ++i) cin >> c[i];
    int x, y;
    for (int i = 0; i < N - 1; ++i) {
        cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    cout << solution(1);
    return 0;
}