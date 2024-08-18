#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N, Q;
int A[200001];
int B[200001];
const ll MOD = 1e9 + 9;

ll xpow[200001];
ll a[200000];
ll b[200000];

struct Query {
	int s, e, idx;
};

void solve() {
	cin >> N >> Q;
	for (int i = 1; i <= N; ++i) cin >> A[i];
	for (int i = 1; i <= N; ++i) cin >> B[i];
	xpow[1] = 524287;
	for (int i = 2; i <= N; ++i) {
		xpow[i] = xpow[i - 1] * 524287;
		xpow[i] %= MOD;
	}
	int sqrtN = sqrt(N);

	vector<Query> queryA(Q), queryB(Q);
	for (int i = 0; i < Q; ++i) {
		cin >> queryA[i].s >> queryA[i].e >> queryB[i].s >> queryB[i].e;
		queryA[i].idx = i;
		queryB[i].idx = i;
	}
	sort(queryA.begin(), queryA.end(), [sqrtN](Query& a, Query& b) {
		if (a.s / sqrtN == b.s / sqrtN) return a.e < b.e;
		return a.s / sqrtN < b.s / sqrtN;
	});
	sort(queryB.begin(), queryB.end(), [sqrtN](Query& a, Query& b) {
		if (a.s / sqrtN == b.s / sqrtN) return a.e < b.e;
		return a.s / sqrtN < b.s / sqrtN;
	});

	int s = queryA[0].s, e = queryA[0].e;
	ll cnt[200001]; ll eans = 0;
	memset(cnt, 0, sizeof(cnt));
	for (int i = s; i <= e; ++i) {
		++cnt[A[i]];
	}
	ll tmp = 524287;
	for (int i = 1; i <= N; ++i) {
		eans += tmp * cnt[i];
		eans %= MOD;
		tmp *= 524287; tmp %= MOD;
	}
	
	for (int i = 0; i < Q; ++i) {
		while (s < queryA[i].s) {
			--cnt[A[s]];
			eans -= xpow[A[s]];
			eans += MOD;
			eans %= MOD;
			++s;
		}
		while (s > queryA[i].s) {
			--s;
			eans += xpow[A[s]];
			eans %= MOD;
			++cnt[A[s]];
		}
		while (e < queryA[i].e) {
			++e;
			eans += xpow[A[e]];
			eans %= MOD;
			++cnt[A[e]];
		}
		while (e > queryA[i].e) {
			--cnt[A[e]];
			eans -= xpow[A[e]];
			eans += MOD;
			eans %= MOD;
			--e;
		}
		a[queryA[i].idx] = eans;
	}

	s = queryA[0].s, e = queryA[0].e;
	eans = 0;
	memset(cnt, 0, sizeof(cnt));
	for (int i = s; i <= e; ++i) {
		++cnt[B[i]];
	}
	tmp = 524287;
	for (int i = 1; i <= N; ++i) {
		eans += tmp * cnt[i];
		eans %= MOD;
		tmp *= 524287; tmp %= MOD;
	}
	
	for (int i = 0; i < Q; ++i) {
		while (s < queryB[i].s) {
			--cnt[B[s]];
			eans -= xpow[B[s]];
			eans += MOD;
			eans %= MOD;
			++s;
		}
		while (s > queryB[i].s) {
			--s;
			eans += xpow[B[s]];
			eans %= MOD;
			++cnt[B[s]];
		}
		while (e < queryB[i].e) {
			++e;
			eans += xpow[B[e]];
			eans %= MOD;
			++cnt[B[e]];
		}
		while (e > queryB[i].e) {
			--cnt[B[e]];
			eans -= xpow[B[e]];
			eans += MOD;
			eans %= MOD;
			--e;
		}
		b[queryB[i].idx] = eans;
	}
	for (int i = 0; i < Q; ++i) {
		if (a[i] == b[i]) cout << "Yes\n";
		else cout << "No\n";
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}