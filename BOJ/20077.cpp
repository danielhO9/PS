#include <bits/stdc++.h>
// #include "wiring.h"
typedef long long LL;
using namespace std;

int n, m, rcnt, bcnt, nr, nb;
LL rsum[1000001], bsum[1000001], cache[1000001];
vector<pair<LL, int>> arr;
map<int, int> M;

LL min_total_length(vector<int> r, vector<int> b) {
	n = r.size(); m = b.size();
	int rindex = 0, bindex = 0, index = 1;
	arr.push_back({0, 0});
	while (1) {
		if (bindex == m || (rindex < n && bindex < m && r[rindex] < b[bindex])) {
			arr.push_back({(LL) r[rindex], 0});
			++index;
			++rindex;
		} else if (rindex == n || (rindex < n && bindex < m && b[bindex] < r[rindex])) {
			arr.push_back({(LL) b[bindex], 1});
			++index;
			++bindex;
		} else if (rindex < n && bindex < m) {
			arr.push_back({(LL) b[bindex], 2});
			++index;
			++rindex; ++bindex;
		}
		if (rindex >= n && bindex >= m) break;
	}
	--index;
	for (int i = 1; i <= index; ++i) {
		rsum[i] = rsum[i - 1]; bsum[i] = bsum[i - 1];
		if (arr[i].second == 0 || arr[i].second == 2) rsum[i] += arr[i].first;
		if (arr[i].second == 1 || arr[i].second == 2) bsum[i] += arr[i].first;
	}
	for (int i = 1; i <= index; ++i) {
		if (arr[i].second == 0 || arr[i].second == 2) ++rcnt;
		if (arr[i].second == 1 || arr[i].second == 2) ++bcnt;
		if (arr[i].second == 0) {
			while (nb + 1 < m && abs(arr[i].first - (LL) b[nb]) >= abs(arr[i].first - (LL) b[nb + 1])) ++nb;
			cache[i] = cache[i - 1] + abs(arr[i].first - (LL) b[nb]);
		} else if (arr[i].second == 1) {
			while (nr + 1 < n && abs(arr[i].first - (LL) r[nr]) >= abs(arr[i].first - r[nr + 1])) ++nr;
			cache[i] = cache[i - 1] + abs(arr[i].first - (LL) r[nr]);
		} else cache[i] = cache[i - 1];
		if ((bcnt == rcnt) || M[bcnt - rcnt] != 0) cache[i] = min(cache[i], cache[M[bcnt - rcnt]] + abs((bsum[i] - bsum[M[bcnt - rcnt]]) - (rsum[i] - rsum[M[bcnt - rcnt]])));
		M[bcnt - rcnt] = i;
	}
	return cache[index];
}
