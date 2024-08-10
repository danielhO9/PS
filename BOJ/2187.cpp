#include <bits/stdc++.h>
using namespace std;

struct point {
	int r, c, s;
};

int N, A, B;
vector<point> v;

bool inRec(int i, int j) {
	if (abs(v[i].r - v[j].r) + 1 <= A && abs(v[i].c - v[j].c) + 1 <= B) return true;
	return false;
}

void solve() {
	cin >> N >> A >> B;
	int ans = 0;
	for (int i = 0; i < N; ++i) {
		int r, c, s; cin >> r >> c >> s;
		v.push_back({r, c, s});
	}
	for (int i = 0; i < v.size(); ++i) {
		for (int j = 0; j < v.size(); ++j) {
			if (inRec(i, j)) {
				ans = max(ans, abs(v[i].s - v[j].s));
			}
		}
	}
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}