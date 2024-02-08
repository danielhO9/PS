#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

int s, t, scnt, tcnt, ns, nt;
LL ssum[1000001], tsum[1000001], cache[1000001], S[500000], T[500000];
vector<pair<LL, int>> arr;
map<int, int> M;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> s >> t;
	for (int i = 0; i < s; ++i) cin >> S[i];
	for (int i = 0; i < t; ++i) cin >> T[i];
	int sindex = 0, tindex = 0, index = 1;
	arr.push_back({0, 0});
	while (1) {
		if (tindex == t || (sindex < s && tindex < t && S[sindex] < T[tindex])) {
			arr.push_back({S[sindex], 0});
			++index;
			++sindex;
		} else if (sindex == s || (sindex < s && tindex < t && T[tindex] < S[sindex])) {
			arr.push_back({T[tindex], 1});
			++index;
			++tindex;
		} else if (sindex < s && tindex < t) {
			arr.push_back({T[tindex], 2});
			++index;
			++sindex; ++tindex;
		}
		if (sindex >= s && tindex >= t) break;
	}
	--index;
	for (int i = 1; i <= index; ++i) {
		ssum[i] = ssum[i - 1]; tsum[i] = tsum[i - 1];
		if (arr[i].second == 0 || arr[i].second == 2) ssum[i] += arr[i].first;
		if (arr[i].second == 1 || arr[i].second == 2) tsum[i] += arr[i].first;
	}
	for (int i = 1; i <= index; ++i) {
		if (arr[i].second == 0 || arr[i].second == 2) ++scnt;
		if (arr[i].second == 1 || arr[i].second == 2) ++tcnt;
		if (arr[i].second == 0) {
			while (nt + 1 < t && abs(arr[i].first - T[nt]) >= abs(arr[i].first - T[nt + 1])) ++nt;
			cache[i] = cache[i - 1] + abs(arr[i].first - T[nt]);
		} else if (arr[i].second == 1) {
			while (ns + 1 < s && abs(arr[i].first - S[ns]) >= abs(arr[i].first - S[ns + 1])) ++ns;
			cache[i] = cache[i - 1] + abs(arr[i].first - S[ns]);
		} else cache[i] = cache[i - 1];
		if ((tcnt == scnt) || M[tcnt - scnt] != 0) cache[i] = min(cache[i], cache[M[tcnt - scnt]] + abs((tsum[i] - tsum[M[tcnt - scnt]]) - (ssum[i] - ssum[M[tcnt - scnt]])));
		M[tcnt - scnt] = i;
	}
	cout << cache[index];
}