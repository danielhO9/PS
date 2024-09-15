#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Point {
	ll x, y;
};

int N;
Point pts[100000];
ll mn[100000];
ll mx[100000];
ll m[100000];

void solve() {
	cin >> N;
	for (int i = 0; i < N; ++i) cin >> pts[i].x >> pts[i].y;
	set<int> s;
	for (int i = 0; i < N; ++i) s.insert(pts[i].x);
	int idx = 0;
	for (auto i: s)
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}