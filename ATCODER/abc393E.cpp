#include <bits/stdc++.h>
using namespace std;

int K, N;
int A[1200000];
vector<int> fact[1000001];
int cnt[1000001];

void init() {
	for (int i = 1000000; i >= 1; --i) {
		for (int j = i; j <= 1000000; j += i) fact[j].push_back(i);
	}
}

void solve() {
	init();
	cin >> N >> K;
	for (int i = 0; i < N; ++i) cin >> A[i];
	for (int i = 0; i < N; ++i) {
		for (auto j: fact[A[i]]) ++cnt[j];
	}
	for (int i = 0; i < N; ++i) {
		for (auto j: fact[A[i]]) if (cnt[j] >= K) {
			cout << j << '\n';
			break;
		}
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}