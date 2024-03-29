#include <bits/stdc++.h>
using namespace std;

struct Query {
	int s, e, idx;
};

void solve() {
	int N; cin >> N;
	int sqrtN = sqrt(N);
	int A[N + 1];
	for (int i = 1; i <= N; ++i) cin >> A[i];
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
	int s = 1, e = 1;
	int cnt[100001]; int eans = 1;
	int ccnt[100001];
	int ans[M];
	memset(cnt, 0, sizeof(cnt));
	memset(ccnt, 0, sizeof(ccnt));
	cnt[A[1]] = 1; ccnt[1] = 1; ccnt[0] = N - 1;
	for (int i = 0; i < M; ++i) {
		while (s < query[i].s) {
			if (cnt[A[s]] == eans && ccnt[eans] == 1) --eans;
			--ccnt[cnt[A[s]]]; --cnt[A[s]]; ++ccnt[cnt[A[s]]];
			++s;
		}
		while (s > query[i].s) {
			--s;
			if (cnt[A[s]] == eans) ++eans;
			--ccnt[cnt[A[s]]]; ++cnt[A[s]]; ++ccnt[cnt[A[s]]];
		}
		while (e < query[i].e) {
			++e;
			if (cnt[A[e]] == eans) ++eans;
			--ccnt[cnt[A[e]]]; ++cnt[A[e]]; ++ccnt[cnt[A[e]]];
		}
		while (e > query[i].e) {
			if (cnt[A[e]] == eans && ccnt[eans] == 1) --eans;
			--ccnt[cnt[A[e]]]; --cnt[A[e]]; ++ccnt[cnt[A[e]]];
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