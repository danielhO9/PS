#include <bits/stdc++.h>
using namespace std;
typedef unsigned long ull;

const vector<vector<ull>> alist = {
	{2, 7, 61},
	{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}
};

ull pow(ull a, ull b, ull MOD) {
	a %= MOD;
	if (b == 0) return 1;
	ull half = pow(a, b / 2, MOD);
	half = (half * half) % MOD;
	if (b % 2 == 0) return half;
	else return (half * a) % MOD;
}

// int -> type 0
// ull -> type 1
bool miullerRabin(ull n, int t) {
	if (t == 1 && n < 40) {
		for (auto i: alist[t]) if (i == n) return true;
		return false;
	}
	for (int i = 0; i < alist[t].size(); ++i) {
		if (alist[t][i] == n) return true;
		ull k = n - 1;
		while (true) {
			ull tmp = pow(alist[t][i], k, n);
			if (tmp == n - 1) break;
			if (k % 2 == 1) {
				if (tmp == 1) break;
				else return false;
			}
			k /= 2;
		}
	}
	return true;
}