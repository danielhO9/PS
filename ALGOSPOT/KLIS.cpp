#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

int N, cacheLen[501], S[500];
LL cacheCnt[501], K;
vector<int> ans;

int lis(int start) {
	int& ret = cacheLen[start + 1];
	if (ret != -1) return ret;
	ret = 1;
	for (int next = start + 1; next < N; ++next)
		if (start == -1 || S[start] < S[next])
			ret = max(ret, lis(next) + 1);
	return ret;
}

LL count(int start) {
	if (lis(start) == 1) return 1;
	LL& ret = cacheCnt[start + 1];
	if (ret != -1) return ret;
	ret = 0;
	for (int next = start + 1; next < N; ++next) {
		if ((start == -1 || S[start] < S[next]) &&
			lis(start) == lis(next) + 1)
			ret = min((LL) INT32_MAX + 1, ret + count(next));
	}
	return ret;
}

void reconstruct(int start, LL skip) {
	if (start != -1) ans.push_back(S[start]);
	vector<int> followers;
	for (int next = start + 1; next < N; ++next) {
		if ((start == -1 || S[start] < S[next]) &&
			lis(start) == lis(next) + 1)
			followers.push_back(next);
	}
	while (!followers.empty()) {
		int idx = followers.back();
		LL cnt = count(idx);
		if (cnt <= skip) skip -= cnt;
		else {
			reconstruct(idx, skip);
			break;
		}
		followers.pop_back();
	}
}

int main() {
	int C; cin >> C;
	for (int i = 0; i < C; ++i) {
		cin >> N >> K;
		for (int j = 0; j < N; ++j) cin >> S[j];
		memset(cacheCnt, -1, sizeof(cacheCnt));
		memset(cacheLen, -1, sizeof(cacheLen));
		reconstruct(-1, K - 1);
		cout << lis(-1) - 1 << "\n";
		for (auto j: ans) cout << j << " ";
		cout << "\n";
		ans.clear();
	}
}