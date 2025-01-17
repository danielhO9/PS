#include <bits/stdc++.h>
using namespace std;

vector<int> prime;
bool isPrime[1000000];

void solve() {
	for (int i = 2; i < 1000000; ++i) isPrime[i] = 1;
	for (int i = 2; i < 1000000; ++i) if (isPrime[i]) {
		prime.push_back(i);
		for (int j = i * 2; j < 1000000; j += i) isPrime[j] = false;
	}
	int x; cin >> x;
	int ans = 0;
	while (x > 3) {
		for (auto i: prime) if (isPrime[x - i]) {
			++ans;
			x = (x - i) - i;
			break;
		}
	}
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}