#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Query {
	int s, e, idx;
};

void solve() {
	int N, M; cin >> N >> M;
	int sqrtN = sqrt(N);
	ll A[N + 1];
	for (int i = 1; i <= N; ++i) cin >> A[i];
	vector<Query> query(M);
	for (int i = 0; i < M; ++i) {
		cin >> query[i].s >> query[i].e;
		query[i].idx = i;
	}
	sort(query.begin(), query.end(), [sqrtN](Query& a, Query& b) {
		if (a.s / sqrtN == b.s / sqrtN) return a.e < b.e;
		return a.s / sqrtN < b.s / sqrtN;
	});
	int s = query[0].s, e = query[0].e;
	ll cnt[1000001]; ll eans = 0;
	ll ans[M];
	memset(cnt, 0, sizeof(cnt));
	for (int i = s; i <= e; ++i) {
		++cnt[A[i]];
		eans += (2 * cnt[A[i]] - 1) * A[i];
	}
	for (int i = 0; i < M; ++i) {
		while (s < query[i].s) {
			eans -= (2 * cnt[A[s]] - 1) * A[s];
			--cnt[A[s]];
			++s;
		}
		while (s > query[i].s) {
			--s;
			++cnt[A[s]];
			eans += (2 * cnt[A[s]] - 1) * A[s];
		}
		while (e < query[i].e) {
			++e;
			++cnt[A[e]];
			eans += (2 * cnt[A[e]] - 1) * A[e];
		}
		while (e > query[i].e) {
			eans -= (2 * cnt[A[e]] - 1) * A[e];
			--cnt[A[e]];
			--e;
		}
		ans[query[i].idx] = eans;
	}
	for (int i = 0; i < M; ++i) cout << ans[i] << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}