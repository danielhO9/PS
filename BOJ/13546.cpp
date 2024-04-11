#include <bits/stdc++.h>
using namespace std;

struct Query {
	int s, e, idx;
};

void solve() {
	int N; cin >> N;
	int sqrtN = sqrt(N);
	int A[N + 1]; for (int i = 1; i <= N; ++i) cin >> A[i];
	int M; cin >> M;
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
	int cnt[1000001]; int eans = 0;
	int ans[M];
	memset(cnt, 0, sizeof(cnt));
	for (int i = s; i <= e; ++i) {
		if (cnt[A[i]] == 0) ++eans;
		++cnt[A[i]];
	}
	for (int i = 0; i < M; ++i) {
		while (s < query[i].s) {
			--cnt[A[s]];
			if (cnt[A[s]] == 0) --eans;
			++s;
		}
		while (s > query[i].s) {
			--s;
			if (cnt[A[s]] == 0) ++eans;
			++cnt[A[s]];
		}
		while (e < query[i].e) {
			++e;
			if (cnt[A[e]] == 0) ++eans;
			++cnt[A[e]];
		}
		while (e > query[i].e) {
			--cnt[A[e]];
			if (cnt[A[e]] == 0) --eans;
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