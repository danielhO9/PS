#include <bits/stdc++.h>
using namespace std;
int N, K;
vector<int> graph[200001];
map<pair<int, int>, int> c; int sz[200001];
vector<int> visited(200001, false);
vector<int> dis(1000001, 200001);

int getSize(int v, int p){
    sz[v] = 1;
    for(auto i: graph[v]) if(i != p && !visited[i]) sz[v] += getSize(i, v);
    return sz[v];
}
int getCent(int v, int p, int csz){
    for(auto i: graph[v]) if(i != p && !visited[i] && sz[i] * 2 > csz) return getCent(i, v, csz);
    return v;
}

void getDistance(int v, int p, int dp, int d, vector<pair<int, int>>& ndis) {
    if (dp + c[{v, p}] > K) return;
    ndis.push_back({dp + c[{v, p}], d});
    for (auto i: graph[v]) if (i != p && !visited[i]) getDistance(i, v, dp + c[{v, p}], d + 1, ndis);
}

int solution(int v) {
    int ret = N;
    getSize(v, 0); int csz = sz[v]; int cent = getCent(v, 0, csz);
    // dis에 cent 추가
    visited[cent] = true;
    // ndis와 dis 비교
    vector<int> toDis;
    for (auto i: graph[cent]) {
        if (visited[i]) continue;
        vector<pair<int, int>> ndis;
        getDistance(i, cent, 0, 1, ndis);
        for (auto [len, cnt]: ndis) ret = min(ret, dis[K - len] + cnt);
        for (auto [len, cnt]: ndis) {
            if (cnt < dis[len]) {
                dis[len] = cnt; toDis.push_back(len);
            }
        }
    }
    for (auto len: toDis) dis[len] = 200001;
    for (int i: graph[cent]) if (!visited[i]) ret = min(ret, solution(i));
    return ret;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> K;
    int x, y, z;
    for (int i = 0; i < N - 1; ++i) {
        cin >> x >> y >> z;
        graph[x].push_back(y);
        graph[y].push_back(x);
        c[{x, y}] = z; c[{y, x}] = z;
    }
    dis[0] = 0;
    int answer = solution(1);
    if (answer == N) cout << -1;
    else cout << answer;
    return 0;
}