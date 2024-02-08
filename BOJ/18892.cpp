#include <bits/stdc++.h>
using namespace std;

int N, cacheLen[501], S[500];
int cacheCnt[501], K;
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

int count(int start) {
	if (lis(start) == 1) return 1;
	int& ret = cacheCnt[start + 1];
	if (ret != -1) return ret;
	ret = 0;
	for (int next = start + 1; next < N; ++next) {
		if ((start == -1 || S[start] < S[next]) &&
			lis(start) == lis(next) + 1)
			ret = min((int) 1e9 + 1, ret + count(next));
	}
	return ret;
}

void reconstruct(int start, int skip) {
	if (count(start) <= skip) return;
	if (start != -1) ans.push_back(S[start]);
	vector<int> followers;
	for (int next = start + 1; next < N; ++next) {
		if ((start == -1 || S[start] < S[next]) &&
			lis(start) == lis(next) + 1)
			followers.push_back(next);
	}
	while (!followers.empty()) {
		int idx = followers.back();
		int cnt = count(idx);
		if (cnt <= skip) skip -= cnt;
		else {
			reconstruct(idx, skip);
			break;
		}
		followers.pop_back();
	}
}

int main() {
	cin >> N >> K;
	for (int j = 0; j < N; ++j) cin >> S[j];
	memset(cacheCnt, -1, sizeof(cacheCnt));
	memset(cacheLen, -1, sizeof(cacheLen));
	reconstruct(-1, K - 1);
	if (!ans.empty()) for (auto j: ans) cout << j << " ";
	else cout << -1;
}