#include <bits/stdc++.h>
using namespace std;
int n, w[10001], cache[2][10001];
vector<int> graph[10001];
vector<int> ans;

int matchCache(int id, int p, int v) {
    int& ret = cache[id][v];
    if (ret != -1) return ret;
    if (id == 0) {
        ret = w[v];
        for (int i: graph[v]) if (i != p) ret += matchCache(1, v, i);
    } else {
        ret = 0;
        for (int i: graph[v]) if (i != p) ret += max(matchCache(0, v, i), matchCache(1, v, i));
    }
    return ret;
}

void getAns(int id, int p, int v) {
    if (id == 0) {
        ans.push_back(v);
        for (int i: graph[v]) if (i != p) getAns(1, v, i);
    } else {
        for (int i: graph[v]) if (i != p) {
            if (matchCache(0, v, i) > matchCache(1, v, i)) getAns(0, v, i);
            else getAns(1, v, i);
        }
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> w[i];
    int x, y;
    for (int i = 0; i < n - 1; ++i) {
        cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    memset(cache, -1, sizeof(cache));
    cout << max(matchCache(0, 0, 1), matchCache(1, 0, 1)) << "\n";
    if (matchCache(0, 0, 1) > matchCache(1, 0, 1)) getAns(0, 0, 1);
    else getAns(1, 0, 1);
    sort(ans.begin(), ans.end());
    for (int i: ans) cout << i << " ";
    return 0;
}