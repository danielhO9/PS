#include <bits/stdc++.h>
using namespace std;
vector<int> sz(10001);
vector<vector<int>> graph(10001);
vector<bool> cent(10001, false);
int N;

int getSize(int v, int p) {
    sz[v] = 1;
    for (auto i : graph[v]) if(i != p) sz[v] += getSize(i, v);
    return sz[v];
}

void getCent(int v, int p) {
    int sum = N - 1; bool avail = true;
    for(auto i : graph[v]) {
        if (i != p && sz[i] * 2 > N) {
            avail = false; break;
        } else if (i != p && sz[i] * 2 <= N) {
            sum -= sz[i];
        }
    }
    if (avail && sum * 2 <= N) cent[v] = true;
    for (auto i: graph[v]) {
        if (i != p) getCent(i, v);
    }
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
    getSize(1, 0);
    getCent(1, 0);
    for (int i = 1; i <= N; ++i) {
        if (cent[i]) cout << i << "\n";
    }
    return 0;
}