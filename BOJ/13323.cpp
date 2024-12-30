#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N;
ll A[1000000];

void solve() {
	cin >> N;
	for (int i = 0; i < N; ++i) cin >> A[i];
	for (int i = 0; i < N; ++i) A[i] -= i;
	priority_queue<ll> pq;
	ll ans = 0;
	for (int i = 0; i < N; ++i) {
		pq.push(A[i]);
		if (pq.top() > A[i]) {
			ans += pq.top() - A[i];
			pq.pop();
			pq.push(A[i]);
		}
	}
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}