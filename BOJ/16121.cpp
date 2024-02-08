#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// centroid 확인
// 서브트리들에 대해 num, sum, sumsum 최신화

int N, M, K;
vector<int> graph[300001];
vector<bool> home(300001, false);
vector<bool> sub(300001, false);
// to centroid
vector<int> sz(300001); vector<int> visited(300001, false);
ll mod = 998244353, ret = 0;
ll home1 = 0, home2 = 0, home3 = 0, sub1 = 0, sub2 = 0, sub3 = 0;

int getSize(int v, int p){
    sz[v] = 1;
    for(auto i: graph[v]) if(i != p && !visited[i]) sz[v] += getSize(i, v);
    return sz[v];
}
int getCent(int v, int p, int csz){
    for(auto i: graph[v]) if(i != p && !visited[i] && sz[i] * 2 > csz) return getCent(i, v, csz);
    return v;
}

void getValue(int v, int p, ll d) {
    if (home[v]) {
        ret += sub3; ret %= mod;
        ret += ((sub2 * (2LL * d)) % mod); ret %= mod;
        ret += ((sub1 * ((d * d) % mod)) % mod); ret %= mod;
    }
    if (sub[v]) {
        ret += home3; ret %= mod;
        ret += ((home2 * ((2LL * d) % mod)) % mod); ret %= mod;
        ret += ((home1 * ((d * d) % mod)) % mod); ret %= mod;
    }
    for (int i: graph[v]) if (!visited[i] && i != p) getValue(i, v, d + 1);
}

void query(ll d, int v) {
    if (home[v]) {
        ++home1; home2 += d; home3 += ((d * d) % mod);
        home2 %= mod; home3 %= mod;
    }
    if (sub[v]) {
        ++sub1; sub2 += d; sub3 += ((d * d) % mod);
        sub2 %= mod; sub3 %= mod;
    }
}

void getQuery(int v, int p, ll d) {
    query(d, v);
    for (int i: graph[v]) if (!visited[i] && i != p) getQuery(i, v, d + 1);
}

void dnc(int v) {
    getSize(v, 0); int csz = sz[v]; int cent = getCent(v, 0, csz); visited[cent] = true;
    home1 = home2 = home3 = sub1 = sub2 = sub3 = 0;
    query(0, cent);
    for (int i: graph[cent]) if (!visited[i]) { getValue(i, cent, 1); getQuery(i, cent, 1);}
    for (int i: graph[cent]) if (!visited[i]) dnc(i);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N; int x, y;
    for (int i = 0; i < N - 1; ++i) {
        cin >> x >> y;
        graph[x].push_back(y); graph[y].push_back(x);
    }
    cin >> M;
    for (int i = 0; i < M; ++i) { cin >> x; home[x] = true; }
    cin >> K;
    for (int i = 0; i < K; ++i) { cin >> x; sub[x] = true; }
    dnc(1);
    cout << ret;
    return 0;
}