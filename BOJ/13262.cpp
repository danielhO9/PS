#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int MAX_M, MAX_N;
vector<ll> dp_before, dp_cur;

ll cost[5001][5001];
int A[5001];

ll C(int i, int j) {
	return cost[i][j];
}

void compute(int l, int r, int optl, int optr) {
    if (l > r)
        return;

    int mid = (l + r) >> 1;
    pair<ll, int> best = {LLONG_MIN, -1};

    for (int k = optl; k <= min(mid, optr); k++) {
        best = max(best, {(k ? dp_before[k - 1] : 0) + C(k, mid), k});
    }

    dp_cur[mid] = best.first;
    int opt = best.second;

    compute(l, mid - 1, optl, opt);
    compute(mid + 1, r, opt, optr);
}

void solve() {
	int N, K; cin >> N >> K;
	for (int i = 1; i <= N; ++i) cin >> A[i];

	for (int i = 1; i <= N; ++i) {
		cost[i][i] = A[i];
		for (int j = i + 1; j <= N; ++j) {
			cost[i][j] = cost[i][j - 1] | A[j];
		}
	}

	MAX_M = K;
	MAX_N = N;
    dp_before.assign(MAX_N + 1,0);
    dp_cur.assign(MAX_N + 1,0);

    for (int i = 1; i <= MAX_N; i++)
        dp_before[i] = C(1, i);

    for (int i = 1; i < MAX_M; i++) {
        compute(1, MAX_N, 1, MAX_N);
        dp_before = dp_cur;
    }

    cout << dp_before[MAX_N];
}

// https://cp-algorithms.com/dynamic_programming/divide-and-conquer-dp.html

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}