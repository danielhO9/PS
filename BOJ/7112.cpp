#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool isPrime[501];
vector<int> prime;
int ch[501][100];
int cnt[100];

void init() {
	for (int i = 2; i <= 500; ++i) isPrime[i] = 1;
	for (int i = 2; i <= 500; ++i) {
		if (!isPrime[i]) continue;
		prime.push_back(i);
		for (int j = i * 2; j <= 500; j += i) isPrime[j] = 0;
	}
	for (int i = 2; i <= 500; ++i) {
		for (int j = 0; j < prime.size(); ++j) ch[i][j] = ch[i - 1][j];
		int num = i;
		for (int j = 0; j < prime.size(); ++j) {
			while (num % prime[j] == 0) {
				++ch[i][j];
				num /= prime[j];
			}
			ch[i][j] = ch[i][j] % 2;
		}
	}
}

int k;
int cntsum = 0;
vector<int> nums;
vector<int> ans;
bool used[501];

void generate(int x) {
	if (ans.size()) return;
	if (nums.size() == x) {
		if (cntsum == 0) {
			for (auto i: nums) ans.push_back(i);
			for (auto i: ans) cout << i << ' ';
		}
		return;
	}
	for (int i = 1; i <= k; ++i) if (!used[i]) {
		if (ans.size()) return;

		nums.push_back(i);
		used[i] = true;
		for (int j = 0; j < prime.size(); ++j) {
			cntsum -= cnt[j];
			cnt[j] ^= ch[i][j];
			cntsum += cnt[j];
		}

		generate(x);

		nums.pop_back();
		used[i] = false;
		for (int j = 0; j < prime.size(); ++j) {
			cntsum -= cnt[j];
			cnt[j] ^= ch[i][j];
			cntsum += cnt[j];
		}
	}
}

void solve() {
	cin >> k;
	for (int i = 1; i <= k; ++i) {
		for (int j = 0; j < prime.size(); ++j) {
			cnt[j] ^= ch[i][j];
		}
	}
	for (int i = 0; i < prime.size(); ++i) cntsum += cnt[i];
	if (cntsum == 0) return;
	for (int i = 1; i <= k; ++i) {
		if (ans.size()) return;
		generate(i);
	}
	for (auto i: ans) cout << i << ' ';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	init();
	solve();
}