#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

// Nlog^3(N)이 될 수 없으므로 LCA를 사용 불가.
// 거리값들을 저장해두자. 최대 거리 수: NlogN : 45 * 10^5
// T1의 한 점을 루트로 하는 서브트리의 각 점에 대해
// 각 점에서 T2의 부모들에 값을 저장한다.
// 다시 서브트리의 각 점에 대해 부모들의 값을 바탕으로 최신화한다.
// T1에서는 각 점의 자식들이, T2에서는 각 점의 부모들이 필요

int N;
vector<pair<int, LL>> graph[2][250001];
int sz[250001]; bool visited[250001];
vector<pair<int, LL>> dis[2][250001];
pair<pair<int, LL>, pair<int, LL>> memo[2500001];
LL ret[250001];

int getSize(int id, int v, int p){
    sz[v] = 1;
    for(auto [i, _]: graph[id][v]) if(i != p && !visited[i]) sz[v] += getSize(id, i, v);
    return sz[v];
}

int getCent(int id, int v, int p, int csz){
    for(auto [i, _]: graph[id][v]) if(i != p && !visited[i] && sz[i] * 2 > csz) return getCent(id, i, v, csz);
    return v;
}

void dfs(int id, int cent, int v, int p, LL d) {
    if (id) dis[id][v].push_back({cent, d});
    else dis[id][cent].push_back({v, d});
    for (auto [i, nd]: graph[id][v]) if (i != p && !visited[i]) dfs(id, cent, i, v, d + nd);
}

// 센트로이드 구하고, 센트로이드 포함 서브 트리 내의 모든 점들에 대해 distance 구한다.
void getDis(int id, int v) {
    getSize(id, v, 0); int cent = getCent(id, v, 0, sz[v]); visited[cent] = true;
    dis[id][cent].push_back({cent, 0LL});
    for (auto [i, d]: graph[id][cent]) if (!visited[i]) dfs(id, cent, i, cent, d);
    for (auto [i, d]: graph[id][cent]) if (!visited[i]) getDis(id, i);
    visited[cent] = false;
}

// T1에서 v를 루트로 하는 서브트리의 점들에 대해 T2에 각각의 부모값을 최신화
// i -> v, i -> j
void solution(int v) {
    for (auto i: dis[0][v]) for (auto j: dis[1][i.first]) memo[j.first] = {{0, 25e13}, {0, 25e13}};
    for (auto i: dis[0][v]) for (auto j: dis[1][i.first]) {
        if (memo[j.first].first.second > i.second + j.second) {
            memo[j.first].second.first = memo[j.first].first.first;
            memo[j.first].second.second = memo[j.first].first.second;
            memo[j.first].first.first = i.first;
            memo[j.first].first.second = i.second + j.second;
        } else if (memo[j.first].second.second > i.second + j.second) {
            memo[j.first].second.first = i.first;
            memo[j.first].second.second = i.second + j.second;
        }
    }
    for (auto i: dis[0][v]) for (auto j: dis[1][i.first]) {
        if (memo[j.first].first.first != i.first) {
            ret[i.first] = min(ret[i.first], memo[j.first].first.second + i.second + j.second);
            ret[memo[j.first].first.first] = min(ret[memo[j.first].first.first], memo[j.first].first.second + i.second + j.second);
            continue;
        }
        ret[i.first] = min(ret[i.first], memo[j.first].second.second + i.second + j.second);
        ret[memo[j.first].second.first] = min(ret[memo[j.first].second.first], memo[j.first].second.second + i.second + j.second);
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    fill_n(ret, 250001, 25e13);
    cin >> N; int S, E; LL W;
    for (int i = 0; i < 2 * (N - 1); ++i) {
        cin >> S >> E >> W;
        if (i < N - 1) {
            graph[0][S].push_back({E, W});
            graph[0][E].push_back({S, W});
        } else {
            graph[1][S].push_back({E, W});
            graph[1][E].push_back({S, W});
        }
    }
    for (int i = 0; i < 2; ++i) getDis(i, 1);
    // for (int i = 1; i <= N; ++i) { cout << i << "\n"; for (auto j: dis[1][i]) cout << j.first << " " << j.second << "\n";}
    for (int i = 1; i <= N; ++i) solution(i);
    for (int i = 1; i <= N; ++i) cout << ret[i] << "\n";
    return 0;
}