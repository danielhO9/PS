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
vector<ll> xcor;
unordered_map<ll, ll> m;
ll ans[100001];

void solve() {
	cin >> N;
	for (int i = 0; i < N; ++i) cin >> pts[i].x >> pts[i].y;
	set<int> s;
	for (int i = 0; i < N; ++i) s.insert(pts[i].x);
	for (auto i: s) {
		xcor.push_back(i);
		m[i] = xcor.size();
	}
	for (int i = 0; i < N; ++i) {
		mn[m[pts[i].x]] = min(mn[m[pts[i].x]], pts[i].y);
		mx[m[pts[i].x]] = max(mx[m[pts[i].x]], pts[i].y);
	}
	int sz = xcor.size();
	ans[0] = 0ll;
	vector<ll> lo, hi;
	for (int i = 1; i <= sz; ++i) {
		
	}

}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}