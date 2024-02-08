#include <bits/stdc++.h>
using namespace std;
int N;
vector<int> arr;
int cache[1001];

int matchCache(int x) {
	int& ret = cache[x];
	if (ret != -1) return ret;
	ret = 1;
	for (int i = x + 1; i <= N; ++i) if (arr[i] > arr[x]) ret = max(ret, matchCache(i) + 1);
	return ret;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N; arr.push_back(0); int t;
	for (int i = 0; i < N; ++i) {
		cin >> t; arr.push_back(t);
	}
	memset(cache, -1, sizeof(cache));
	cout << matchCache(0) - 1;
}