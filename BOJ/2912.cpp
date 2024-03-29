#include <bits/stdc++.h>
using namespace std;

struct Query {
	int s, e, idx;
};

int cnt[10005], ccnt[300005];
Query query[10005];

void add(int num, int& pans) {
	if (cnt[num] == pans) ++pans;
	--ccnt[cnt[num]];
	++cnt[num];
	++ccnt[cnt[num]];
}

void erase(int num, int& pans) {
	if (cnt[num] == pans && ccnt[pans] == 1) --pans;
	--ccnt[cnt[num]];
	--cnt[num];
	++ccnt[cnt[num]];
}

void solve() {
	int N, C; cin >> N >> C;
	int sqrt_N = sqrt(N);
	int arr[N + 1];
	for (int i = 1; i <= N; ++i) cin >> arr[i];
	int M_QUERY; cin >> M_QUERY;
	for (int i = 0; i < M_QUERY; ++i) {
		cin >> query[i].s >> query[i].e;
		query[i].idx = i;
	}
	sort(query, query + M_QUERY, [sqrt_N](Query& a, Query& b) {
		if (a.s / sqrt_N == b.s / sqrt_N) return a.e < b.e;
		return a.s / sqrt_N < b.s / sqrt_N;
	});
	int s = 1, e = 1, pans = 1;
	memset(cnt, 0, sizeof(cnt));
	memset(ccnt, 0, sizeof(ccnt));
	cnt[arr[1]] = 1; ccnt[1] = 1; ccnt[0] = N - 1;
	random_device rd;
	mt19937 gen(rd());
	string ans[M_QUERY];
	for (int i = 0; i < M_QUERY; ++i) {
		while (s < query[i].s) {
			erase(arr[s], pans);
			++s;
		}
		while (s > query[i].s) {
			--s;
			add(arr[s], pans);
		}
		while (e < query[i].e) {
			++e;
			add(arr[e], pans);
		}
		while (e > query[i].e) {
			erase(arr[e], pans);
			--e;
		}
		if (pans > (query[i].e - query[i].s + 1) / 2) {
			uniform_int_distribution<int> dist(query[i].s, query[i].e);
			while (true) {
				int x = arr[dist(gen)];
				if (cnt[x] == pans) {
					ans[query[i].idx] = "yes ";
					ans[query[i].idx] += to_string(x);
					ans[query[i].idx] += "\n";
					break;
				}
			}
		} else ans[query[i].idx] = "no\n";
	}
	for (int i = 0; i < M_QUERY; ++i) cout << ans[i];
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}