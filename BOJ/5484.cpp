#include <bits/stdc++.h>
using namespace std;

int garden[250][250];
int sum[250][250];
int l, w, n, k;
const int MAX = 987654321;
int cache[250][250][2];

int get_val(int w1, int l1, int w2, int l2) {
	int ret = sum[w2][l2];
	if (w1 != 0) ret -= sum[w1 - 1][l2];
	if (l1 != 0) ret -= sum[w2][l1 - 1];
	if (w1 != 0 && l1 != 0) ret += sum[w1 - 1][l1 - 1];
	return ret;
}

int matchCache(int left, int right, int type) {
	int& ret = cache[left][right][type];
	if (ret != -1) return ret;
	ret = MAX;
	int start = 0, end = 0;
	int val;
	while (true) {
		if (type == 0) val = get_val(left, start, right, end);
		else val = get_val(start, left, end, right);
		int lim = type == 0 ? l - 1 : w - 1;
		if (val < k) {
			if (end == lim) break;
			++end;
		} else if (val == k) {
			ret = min(ret, 2 * (right - left + end - start + 2));
			if (start == end) {
				if (end == lim) break;
				else ++end;
			} else ++start;
		} else {
			if (start == end) {
				if (end == lim) break;
				++end;
			}
			else ++start;
		}
	}
	if (left < right) {
		ret = min(ret, matchCache(left + 1, right, type));
		ret = min(ret, matchCache(left, right - 1, type));
	}
	return ret;
}

void solve() {
	cin >> l >> w >> n >> k;
	for (int i = 0; i < n; ++i) {
		int li, wi; cin >> li >> wi;
		--li; --wi;
		++garden[wi][li];
		sum[wi][li] = garden[wi][li];
	}
	memset(cache, -1, sizeof(cache));
	for (int i = 0; i < w; ++i) {
		for (int j = 1; j < l; ++j) {
			sum[i][j] += sum[i][j - 1];
		}
	}
	for (int i = 1; i < w; ++i) {
		for (int j = 0; j < l; ++j) sum[i][j] += sum[i - 1][j];
	}
	int ans = MAX;
	for (int i = 0; i < w - 1; ++i) ans = min(ans, matchCache(0, i, 0) + matchCache(i + 1, w - 1, 0));
	for (int i = 0; i < l - 1; ++i) ans = min(ans, matchCache(0, i, 1) + matchCache(i + 1, l - 1, 1));
	if (ans == MAX) {
		cout << "NO\n";
		return;
	}
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}