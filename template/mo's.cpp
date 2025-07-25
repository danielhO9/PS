#include <bits/stdc++.h>
using namespace std;

int N, sqrtN, M;

struct Query {
	int s, e, idx;
};

void add(int idx, bool last) {
	
}

void del(int idx, bool last) {
	
}

void solve() {
	vector<Query> query;
	sqrtN = sqrt(N);
	sort(query.begin(), query.end(), [](const Query& a, const Query& b) {
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
	}
	for (int i = 0; i < M; ++i) cout << ans[i] << '\n';

}