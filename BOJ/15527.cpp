#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

LL N, d[200000], g[200000], S, ans;
priority_queue<LL> L;
priority_queue<LL, vector<LL>, greater<>> R;


int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N;
	for (int i = 1; i < N; ++i) cin >> d[i];
	for (int i = 0; i < N; ++i) cin >> g[i];
	L.push(g[0]); R.push(g[0]);
	for (int i = 1; i < N; ++i) {
		S += d[i];
		ans += i * d[i];
		if (R.top() + S > g[i]) {
			L.push(g[i] + S); L.push(g[i] + S);
			R.push(L.top() - 2 * S);
			L.pop();
		} else {
			R.push(g[i] - S); R.push(g[i] - S);
			L.push(R.top() + 2 * S);
			R.pop();
		}
	}
	while (!L.empty()) {
		ans += L.top() - S;
		L.pop();
	}
	cout << ans;
}