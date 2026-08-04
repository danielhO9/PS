#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

struct Frac {
    ll a, b;
    bool operator<  (const Frac& p) const { return (__int128_t) a * p.b < (__int128_t) b * p.a; }
    bool operator>  (const Frac& p) const { return (__int128_t) a * p.b > (__int128_t) b * p.a; }
	bool operator== (const Frac& p) const { return (__int128_t) a * p.b == (__int128_t) b * p.a; }
    Frac(ll _a, ll _b) {
        a = _a, b = _b;
        if (b < 0) {
            a *= -1;
            b *= -1;
        }
    }
};

const Frac MIN = {(ll) -3e18, 1};

struct Line {
    ll a, b, c;
};

Frac intersect(const Line& l, const Line& r) {
    if (l.a * r.b - r.a * l.b == 0) return MIN;
    return Frac {r.c * l.b - l.c * r.b, l.a * r.b - r.a * l.b};
}

int N;
Line lines[2000];
int arr[2000][2000], ord[2000][2000];

void solve() {
    cin >> N;
    for (int i = 0; i < N; ++i) cin >> lines[i].a >> lines[i].b >> lines[i].c;
    for (int i = 0; i < N; ++i) if (lines[i].b < 0) {
        lines[i].a *= -1;
        lines[i].b *= -1;
        lines[i].c *= -1;
    }
    sort(lines, lines + N, [](const auto& l, const auto& r) {
        return l.a * r.b > r.a * l.b;
    });

    for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) ord[i][j] = -1;
    
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) arr[i][j] = 1;

        vector<pair<Frac, int>> tmp;
        for (int j = 0; j < N; ++j) if (i != j) {
            auto x = intersect(lines[i], lines[j]);
            if (x == MIN) continue;
            tmp.push_back(make_pair(x, j));
        }
        sort(tmp.begin(), tmp.end());
        int cnt = 1;
        for (auto [_, j]: tmp) ord[i][j] = cnt++;
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < i; ++j) {
            if (ord[i][j] == -1) continue;
            arr[i][ord[i][j]] = max(arr[i][ord[i][j]], arr[j][ord[j][i]] + 1);
        }
        for (int j = 1; j < N; ++j) arr[i][j] = max(arr[i][j], arr[i][j - 1]);
    }
    int ans = 0;
    for (int i = 0; i < N; ++i) ans = max(ans, arr[i][N - 1]);
    cout << ans << '\n';
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