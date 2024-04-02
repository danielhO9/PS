#include <bits/stdc++.h>
using namespace std;

// S[i...], S의 공통 prefix length
vector<int> getZ(const string& S) {
	const int n = S.size();
	int l = 0, r = 0;
	vector<int> z(n, 0);
	z[0] = n;
	for (int i = 1; i < n; ++i) {
		if (i <= r) z[i] = min(r - i, z[i - l]);
		while (S[i + z[i]] == S[z[i]]) ++z[i];
		if (i > r) l = i;
		r = max(r, i + z[i] - 1);
	}
	return z;
}