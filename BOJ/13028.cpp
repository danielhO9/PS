#include <bits/stdc++.h>
using namespace std;

int N, sqrtN, M;
int A[100000];
int cnt[100001];
int cur = 0;

struct Query {
	int s, e, idx;
};

vector<Query> query;

void add(int idx, bool last) {
	--idx;
    ++cnt[A[idx]];
    if (cnt[A[idx]] == 3) ++cur;
}

void del(int idx, bool last) {
	--idx;
    --cnt[A[idx]];
    if (cnt[A[idx]] == 2) --cur;
}

void solve() {
    cin >> N >> M;
    for (int i = 0; i < N; ++i) cin >> A[i];
    for (int i = 0; i < M; ++i) {
        int x, y; cin >> x >> y;
        query.push_back({x, y, i});
    }
	sqrtN = sqrt(N);
	sort(query.begin(), query.end(), [](Query& a, Query& b) {
		if (a.s / sqrtN == b.s / sqrtN) return a.e < b.e;
		return a.s / sqrtN < b.s / sqrtN;
	});

	vector<int> ans(M);
	int s = 1, e = 1;
	add(1, true);
	for (int i = 0; i < M; ++i) {
		while (e < query[i].e) add(++e, true);
		while (e > query[i].e) del(e--, true);
		while (s < query[i].s) del(s++, false);
		while (s > query[i].s) add(--s, false);
        ans[query[i].idx] = cur;
	}
	for (int i = 0; i < M; ++i) cout << ans[i] << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}