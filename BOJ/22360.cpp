#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

int N, sz[200001];
char alpha[200001];
bool visited[200001];
vector<int> graph[200001];
map<vector<int>, int> ma;
LL ret = 0;

int getSize(int v, int p){
    sz[v] = 1;
    for(auto i: graph[v]) if(i != p && !visited[i]) sz[v] += getSize(i, v);
    return sz[v];
}

int getCent(int v, int p, int csz){
    for(auto i: graph[v]) if(i != p && !visited[i] && sz[i] * 2 > csz) return getCent(i, v, csz);
    return v;
}

void retdfs(int v, int p, int U, int C, int P) {
    if (alpha[v] == 'U') ++U;
    else if (alpha[v] == 'C') ++C;
    else ++P;
    int time = max(U, C % 2 == 0 ? C/2 : ((C + 1)/2)); time = max(time, P);
    ret += ma[{time - U, 2*time - C, time - P}];
    for (int i: graph[v]) if (!visited[i] && i != p) retdfs(i, v, U, C, P);
}

void updatedfs(int v, int p, int U, int C, int P) {
    if (alpha[v] == 'U') ++U;
    else if (alpha[v] == 'C') ++C;
    else ++P;
    int time = min(U, C/2); time = min(time, P);
    ++ma[{U - time, C - (time * 2), P - time}];
    for (int i: graph[v]) if (!visited[i] && i != p) updatedfs(i, v, U, C, P);
}

void dnc(int v) {
    getSize(v, 0); int csz = sz[v]; int cent = getCent(v, 0, csz); visited[cent] = true;
    int U = 0, C = 0, P = 0;
    if (alpha[cent] == 'U') ++U;
    else if (alpha[cent] == 'C') ++C;
    else ++P;
    ++ma[{U, C, P}];
    for (int i: graph[cent]) if (!visited[i]) {
        retdfs(i, cent, 0, 0, 0);
        updatedfs(i, cent, U, C, P);
    }
    ma.clear();
    for (int i: graph[cent]) if (!visited[i]) dnc(i);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N; char c;
    for (int i = 1; i <= N; ++i) {
        cin >> c;
        if (c == 'U') alpha[i] = 'U';
        else if (c == 'C') alpha[i] = 'C';
        else alpha[i] = 'P';
    }
    int x, y;
    for (int i = 0; i < N - 1; ++i) {
        cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    dnc(1);
    cout << ret;
    return 0;
}