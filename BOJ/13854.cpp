#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef complex<double> base;

LL N;
bool prime[100001];
vector<int> graph[100001];
int sz[100001]; bool visited[100001];
LL ans[100001]; LL result = 0;

void fft(vector<base> &a, bool inv) {
    int n = (int) a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        while (!((j ^= bit) & bit)) bit >>= 1;
        if (i < j) swap(a[i], a[j]);
    }
    for (int i = 1; i < n; i <<= 1) {
        double x = inv ? M_PI / i : -M_PI / i;
        base w = {cos(x), sin(x)};
        for (int j = 0; j < n; j += i << 1) {
            base th = {1, 0};
            for (int k = 0; k < i; k++) {
                base tmp = a[i + j + k] * th;
                a[i + j + k] = a[j + k] - tmp;
                a[j + k] += tmp;
                th *= w;
            }
        }
    }
    if (inv) {
        for (int i = 0; i < n; i++) {
            a[i] /= n;
        }
    }
}

vector<LL> multiply(vector<int> &A, vector<int> &B) {
    vector<base> a(A.begin(), A.end()), b(B.begin(), B.end());
    int n = (int) max(a.size(), b.size());
    int size = a.size() + b.size();
    int i = 0;
    while ((1 << i) < (n << 1)) i++;
    n = 1 << i;
    a.resize(n);
    b.resize(n);
    fft(a, false);
    fft(b, false);
    for (int i = 0; i < n; i++) {
        a[i] *= b[i];
    }
    fft(a, true);
    vector<LL> ret;
    for (auto i = 0; i < size - 1; ++i) ret.push_back((LL) round(a[i].real()));
    return ret;
}

void getPrime() {
    fill_n(prime, 100001, 1);
    prime[0] = prime[1] = 0;
    for (int i = 2; i <= N; ++i) {
        if (prime[i]) {
            int j = i * 2;
            while (j <= N) { prime[j] = false; j += i; }
        }
    }
}

int getSize(int v, int p){
    sz[v] = 1;
    for(auto i: graph[v]) if(i != p && !visited[i]) sz[v] += getSize(i, v);
    return sz[v];
}

int getCent(int v, int p, int csz){
    for(auto i: graph[v]) if(i != p && !visited[i] && sz[i] * 2 > csz) return getCent(i, v, csz);
    return v;
}

vector<int> root, tmp; int depth;

void dfs(int v, int p, int d, bool rd) {
    depth = max(depth, d); if (rd) ++tmp[d];
    for (auto i: graph[v]) if (i != p && !visited[i]) dfs(i, v, d + 1, rd);
}

void solution(int v) {
    getSize(v, 0); int csz = sz[v]; int cent = getCent(v, 0, csz); visited[cent] = true;

    root.clear(); root.resize(1); root[0] = 1; root.reserve(sz[cent] + 1);
    tmp.reserve(sz[cent] + 1);
    sort(graph[cent].begin(), graph[cent].end(), [&](int a, int b){ return sz[a] < sz[b]; });
    for (int i: graph[cent]) if (!visited[i]) {
        depth = 0; dfs(i, cent, 1, false);
        tmp.clear(); tmp.resize(depth + 1, 0); dfs(i, cent, 1, true);
        auto cal = multiply(root, tmp);
        for (int j = 1; j < cal.size(); ++j) ans[j] += cal[j];
        if (root.size() <= depth) root.resize(depth + 1, 0);
        for (int j = 0; j <= depth; ++j) root[j] += tmp[j];
    }
    for (auto i: graph[cent]) if (!visited[i]) solution(i);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N;
    getPrime();
    int x, y;
    for (int i = 0; i < N - 1; ++i) {
        cin >> x >> y;
        graph[x].push_back(y); graph[y].push_back(x);
    }
    solution(1);
    for (int i = 0; i < N; ++i) if (prime[i]) result += ans[i];
    cout << fixed; cout.precision(10);
    cout << 1.0 * result / (N * (N - 1) / 2);
    return 0;
}