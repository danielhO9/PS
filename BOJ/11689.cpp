#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

LL n, ans;
bool prime[1000000];

void getPrime() {
	for (LL i = 2; i < 1000000; ++i) {
		if (prime[i]) {
			if (n % i == 0) {
				while (n % i == 0) n /= i;
				ans /= i;
				ans *= (i - 1);
			}
			for (int j = 2; j < 1000000 / i; ++j) prime[j * i] = 0;
		}
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	ans = n;
	for (int i = 2; i < 1000000; ++i) prime[i] = 1;
	getPrime();
	if (n != 1) { ans /= n; ans *= (n - 1); }
	cout << ans;
}