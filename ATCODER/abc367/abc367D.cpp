#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll N; 
ll A[200001];
ll M;
ll Asum[200001];
ll modcnt[1000000];
ll tmod[1000000];

void solve() {
	cin >> N >> M;
	for (int i = 1; i <= N; ++i) cin >> A[i];
	++modcnt[0];
	for (int i = 1; i <= N; ++i) {
		Asum[i] = Asum[i - 1] + A[i];
		++modcnt[Asum[i] % M];
	}
	ll tot = Asum[N];
	ll ans = 0;
	for (int i = 0; i < M; ++i) {
		ans += (modcnt[i] - 1) * (modcnt[i]) / 2;
	}
	if (tot % M == 0) --ans;

	ll tmp = tot % M;
	for (int i = 1; i <= N - 1; ++i) {
		ans += tmod[(Asum[i] + M - tmp) % M];
		++tmod[Asum[i] % M];
	}
	cout << ans;
	
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}