#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;

int N, K;
int a[100];
int cache[100001];
int ncache[100001];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N >> K;
	for (int i = 0; i < N; ++i) cin >> a[i];
	for (int i = 0; i < N; ++i) {
		if (i == 0) {
			for (int j = 0; j <= a[i]; ++j) cache[j] = 1;
			continue;
		}
		
		int sum = 0;
		for (int j = 0; j <= a[i]; ++j) {
			sum += cache[j]; sum %= MOD;
			ncache[j] = sum;
		}
		for (int j = a[i] + 1; j <= K; ++j) {
			sum += cache[j]; sum %= MOD;
			sum -= cache[j - a[i] - 1]; sum += MOD; sum %= MOD;
			ncache[j] = sum;
		}
		swap(cache, ncache);
	}
	cout << cache[K];
}