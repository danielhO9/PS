#include <bits/stdc++.h>
using namespace std;

int N, T;
int a[200000];

bool possible(int x) {
	deque<int> Q;
	for (int i = N - 1; i >= 0; --i) {
		while (!Q.empty() && Q.size() > x) Q.pop_back();
		int s = a[i];
		if (Q.size() == x) s = min(s, Q.back() - T);
		if (s < 1) return false;
		if (s + T - 1 < a[i]) return false;
		Q.push_front(s);
	}
	return true;
}

void solve() {
	cin >> N >> T;
	for (int i = 0; i < N; ++i) cin >> a[i];
	sort(a, a + N);
	int l = 0, r = N;
	while (l + 1 < r) {
		int mid = (l + r) / 2;
		if (possible(mid)) r = mid;
		else l = mid;
	}
	cout << r;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}