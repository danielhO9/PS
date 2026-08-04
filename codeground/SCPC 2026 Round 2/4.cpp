#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

// 1-index
struct Fenwick {
    vector<ll> tree;

    Fenwick() = default;
    Fenwick(int sz) { tree.resize(sz); }
    void update(int i, ll dif) { while (i < tree.size()) { tree[i] += dif; i += (i & -i); } }
    ll query(int i) {
        ll ret = 0;
        while (i > 0) { ret += tree[i]; i -= (i & -i); }
        return ret;
    }
};

struct Pt {
    int x, y;
};

int N, M;
Pt s, e[100000], rec[100000][2];
int arr[2010][2010];
int dis[2010][2010][4];
int ans[100000];
vector<int> x, y;

const int dy[4] = {-1, 1, 0, 0};
const int dx[4] = {0, 0, -1, 1};

void add(vector<int>& v, int c) {
    v.push_back(c);
    v.push_back(c - 1);
    v.push_back(c + 1);
}

void init() {
    cin >> N >> M;
    for (int i = 0; i < N; ++i) cin >> rec[i][0].x >> rec[i][1].x >> rec[i][0].y >> rec[i][1].y;
    cin >> s.x >> s.y;
    for (int i = 0; i < M; ++i) cin >> e[i].x >> e[i].y;
    
    x.clear(); y.clear();
    for (int i = 0; i < N; ++i) {
        add(x, rec[i][0].x);
        add(x, rec[i][1].x);
        add(y, rec[i][0].y);
        add(y, rec[i][1].y);
    }
    add(x, s.x);
    add(y, s.y);
    for (int i = 0; i < M; ++i) {
        add(x, e[i].x);
        add(y, e[i].y);
    }
    sort(x.begin(), x.end());
    sort(y.begin(), y.end());
    x.erase(unique(x.begin(), x.end()), x.end());
    y.erase(unique(y.begin(), y.end()), y.end());
    
    for (int i = 0; i < N; ++i) for (int j = 0; j < 2; ++j) {
        rec[i][j].x = lower_bound(x.begin(), x.end(), rec[i][j].x) - x.begin();
        rec[i][j].y = lower_bound(y.begin(), y.end(), rec[i][j].y) - y.begin();
    }
    s.x = lower_bound(x.begin(), x.end(), s.x) - x.begin();
    s.y = lower_bound(y.begin(), y.end(), s.y) - y.begin();
    for (int i = 0; i < M; ++i) {
        e[i].x = lower_bound(x.begin(), x.end(), e[i].x) - x.begin();
        e[i].y = lower_bound(y.begin(), y.end(), e[i].y) - y.begin();
    }
}

void bfs1() {
    for (int i = 0; i < 2010; ++i) for (int j = 0; j < 2010; ++j) {
        for (int k = 0; k < 4; ++k) {
            dis[i][j][k] = 5000;
        }
    }

    deque<tuple<int, int, int>> dq;
    for (int k = 0; k < 4; ++k) {
        dis[s.x][s.y][k] = 0;
        dq.emplace_back(s.x, s.y, k);
    }

    while (!dq.empty()) {
        auto [cx, cy, dir] = dq.front();
        dq.pop_front();
        for (int ndir = 0; ndir < 4; ++ndir) {
            int nx = cx + dx[ndir];
            int ny = cy + dy[ndir];
            if (nx < 0 || nx >= 2010 || ny < 0 || ny >= 2010 || arr[nx][ny] == 0) continue;
            
            int nval = dis[cx][cy][dir] + (dir == ndir ? 0 : 1);
            if (dis[nx][ny][ndir] <= nval) continue;
            dis[nx][ny][ndir] = nval;
            if (dir == ndir) dq.emplace_front(nx, ny, ndir);
            else dq.emplace_back(nx, ny, ndir);
        }
    }
}

void group1() {
    memset(arr, 0, sizeof(arr));
    for (int i = 0; i < N; ++i) {
        ++arr[rec[i][0].x][rec[i][0].y];
        --arr[rec[i][1].x + 1][rec[i][0].y];
        --arr[rec[i][0].x][rec[i][1].y + 1];
        ++arr[rec[i][1].x + 1][rec[i][1].y + 1];
    }
    for (int i = 0; i < 2010; ++i) {
        for (int j = 1; j < 2010; ++j) arr[i][j] += arr[i][j - 1];
    }
    for (int j = 0; j < 2010; ++j) {
        for (int i = 1; i < 2010; ++i) arr[i][j] += arr[i - 1][j];
    }
    for (int i = 0; i < 2010; ++i) for (int j = 0; j < 2010; ++j) for (int k = 0; k < 4; ++k)
        dis[i][j][k] = 5000;

    deque<pair<Pt, int>> q;
    bfs1();

    for (int i = 0; i < M; ++i) {
        int ans = 5000;
        for (int j = 0; j < 4; ++j) ans = min(ans, dis[e[i].x][e[i].y][j]);
        if (ans == 5000) cout << -1 << ' ';
        else cout << ans << ' ';
    }
    cout << '\n';
}

void bfs2(map<tuple<int, int, int>, int>& dm) {
    deque<tuple<int, int, int>> dq;
    for (int k = 0; k < 4; ++k) {
        dm[{s.x, s.y, k}] = 0;
        dq.emplace_back(s.x, s.y, k);
    }

    while (!dq.empty()) {
        auto [cx, cy, dir] = dq.front();
        dq.pop_front();
        for (int ndir = 0; ndir < 4; ++ndir) {
            int nx = cx + dx[ndir];
            int ny = cy + dy[ndir];
            if (dm.find({nx, ny, 0}) == dm.end()) continue;
            
            int nval = dm[{cx,cy,dir}] + (dir == ndir ? 0 : 1);
            if (dm[{nx,ny,ndir}] <= nval) continue;
            dm[{nx,ny,ndir}] = nval;
            if (dir == ndir) dq.emplace_front(nx, ny, ndir);
            else dq.emplace_back(nx, ny, ndir);
        }
    }
}

void group2() {
    map<tuple<int, int, int>, int> dm;
    for (int i = 0; i < N; ++i) for (int j = 0; j < 4; ++j) {
        dm[{rec[i][0].x, rec[i][0].y, j}] = 100000;
    }

    bfs2(dm);

    for (int i = 0; i < M; ++i) {
        int ans = 100000;
        for (int j = 0; j < 4; ++j) ans = min(ans, dm[{e[i].x, e[i].y, j}]);
        if (ans == 100000) cout << -1 << ' ';
        else cout << ans << ' ';
    }
    cout << '\n';
}

void solve() {
    init();

    bool g2 = true;
    for (int i = 0; i < N; ++i) {
        if (rec[i][0].x != rec[i][1].x) g2 = false;
        if (rec[i][0].y != rec[i][1].y) g2 = false;
    }
    if (g2) return group2();

    if (x.size() < 2010 && y.size() < 2010) 
        return group1();
    

    vector<tuple<int, int, int>> v;
    for (int i = 0; i < N; ++i) {
        v.emplace_back(rec[i][0].x, -2, rec[i][0].y);
        v.emplace_back(rec[i][0].x, -1, rec[i][1].y + 1);
        v.emplace_back(rec[i][1].x + 1, -1, rec[i][0].y);
        v.emplace_back(rec[i][1].x + 1, -2, rec[i][1].y + 1);
    }
    for (int i = 0; i < M; ++i) ans[i] = 2;
    for (int i = 0; i < M; ++i) {
        if (s.x == e[i].x || s.y == e[i].y) ans[i] = 0;
        else {
            v.emplace_back(s.x, i, e[i].y);
            v.emplace_back(e[i].x, i, s.y);
        }
    }
    sort(v.begin(), v.end());
    Fenwick seg {(int) y.size() + 1};
    for (auto [x, t, y]: v) {
        if (t >= 0) {
            if (seg.query(y + 1)) ans[t] = 1;
        } else {
            if (t == -2) seg.update(y + 1, 1);
            else seg.update(y + 1, -1);
        }
    }
    
    for (int i = 0; i < M; ++i) cout << ans[i] << ' ';
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    for (int i = 1; i <= t; ++i) {
        cout << "Case #" << i << '\n';
        solve();
        cout.flush();
    }
}