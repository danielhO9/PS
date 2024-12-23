#include <bits/stdc++.h>
using namespace std;

struct Query {
	int s, e, idx;
};

int N, K;
int A[100001];
deque<int> indices[100001];

vector<Query> query;
vector<int> cnt;
vector<int> cnt_sqrt;
int sqrtN;

void add(int idx, bool last) {
	int dif;
	if (!indices[A[idx]].empty()) {
		dif = indices[A[idx]].back() - indices[A[idx]].front();
		--cnt[dif];
		--cnt_sqrt[dif / sqrtN];
	}

	if (last) indices[A[idx]].push_back(idx);
	else indices[A[idx]].push_front(idx);
	dif = indices[A[idx]].back() - indices[A[idx]].front();
	++cnt[dif];
	++cnt_sqrt[dif / sqrtN];
}

void del(int idx, bool last) {
	int dif = indices[A[idx]].back() - indices[A[idx]].front();
	--cnt[dif];
	--cnt_sqrt[dif / sqrtN];

	assert(!indices[A[idx]].empty());
	if (last) indices[A[idx]].pop_back();
	else indices[A[idx]].pop_front();
	if (indices[A[idx]].empty()) return;
	dif = indices[A[idx]].back() - indices[A[idx]].front();
	++cnt[dif];
	++cnt_sqrt[dif / sqrtN];
}

void solve() {
	cin >> N >> K;
	for (int i = 1; i <= N; ++i) cin >> A[i];
	int M; cin >> M;
	for (int i = 0; i < M; ++i) {
		int l, r; cin >> l >> r;
		query.push_back({l, r, i});
	}
	sqrtN = sqrt(N);
	sort(query.begin(), query.end(), [](Query& a, Query& b) {
		if (a.s / sqrtN == b.s / sqrtN) return a.e < b.e;
		return a.s / sqrtN < b.s / sqrtN;
	});
	cnt.resize(N);
	cnt_sqrt.resize(((N - 1) / sqrtN) + 1);
	vector<int> ans(M);
	int s = 1, e = 1;
	add(1, true);
	for (int i = 0; i < M; ++i) {
		while (e < query[i].e) add(++e, true);
		while (e > query[i].e) del(e--, true);
		while (s < query[i].s) del(s++, false);
		while (s > query[i].s) add(--s, false);
		

		for (int j = (int) cnt_sqrt.size() - 1; j >= 0; --j) {
			if (cnt_sqrt[j] != 0) {
				int val = -1;
				for (int k = j * sqrtN; k < min((j + 1) * sqrtN, N); ++k) {
					if (cnt[k] != 0) val = max(val, k);
				}
				ans[query[i].idx] = val;
				break;
			}
		}
		// for (int j = 0; j < N; ++j) cout << cnt[j] << ' ';
		// cout << '\n';
		// for (auto j: cnt_sqrt) cout << j << ' ';
		// cout << '\n';
		// cout << '\n';
	}
	for (int i = 0; i < M; ++i) cout << ans[i] << '\n';

}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}