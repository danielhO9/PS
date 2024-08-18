#include <bits/stdc++.h>
using namespace std;

vector<int> getSuffixArray(string& s) {
	int m = 255;
	int n = s.size();
	int t = 1;
	vector<int> group(n + 1), sfx(n), newGroup(n + 1), nxtord(n + 1);
	int cnt[max(m, n) + 1];
	
	for(int i = 0; i < n; ++i) group[i] = s[i];
	
	int pt = 1;
	while (true) {
		// nxtord: i를 group[i + t]로 정렬
		memset(cnt, 0, sizeof(cnt));
		for (int i = 0; i < n; ++i) ++cnt[group[min(i + t, n)]];
		for (int i = 1; i <= n || i <= m; ++i) cnt[i] += cnt[i - 1];
		for (int i = 0; i < n; ++i) nxtord[--cnt[group[min(i + t, n)]]] = i;

		// nxtord가 큰 i부터 뒤에서 채움
		memset(cnt, 0, sizeof(cnt));
		for (int i = 0; i < n; ++i) ++cnt[group[i]];
		for (int i = 1; i <= n || i <= m; ++i) cnt[i] += cnt[i - 1];
		for (int i = n - 1; i >= 0; --i) sfx[--cnt[group[nxtord[i]]]] = nxtord[i];

		if(pt == n) break;
		pt = 1; newGroup[sfx[0]] = 1;
		for(int i = 1; i < n; ++i){
			if(group[sfx[i - 1]] != group[sfx[i]] || group[min(sfx[i - 1] + t, n)] != group[min(sfx[i] + t, n)]) ++pt;
			newGroup[sfx[i]] = pt;
		}
		group = vector<int>(newGroup.begin(), newGroup.end());
		t *= 2;
	}
	return sfx;
}

vector<int> getLcp(const string& s, const vector<int>& sfx) {
	const int MAX_N = s.size();
	vector<int> inv(MAX_N), lcp(MAX_N);
	for (int i = 0; i < MAX_N; ++i) inv[sfx[i]] = i;
	int h = 0;
	for(int i = 0; i < MAX_N; ++i){
		if(inv[i]){
			int prv = sfx[inv[i] - 1];
			while(s[prv + h] == s[i + h]) ++h;
			lcp[inv[i]] = h;
		}
		h = max(h - 1, 0);
	}
	return lcp;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	string s; cin >> s;
	vector<int> sfx = getSuffixArray(s);
	vector<int> lcp = getLcp(s, sfx);
	for (int i = 0; i < s.size(); ++i) cout << sfx[i] + 1 << ' ';
	cout << '\n';
	cout << "x ";
	for (int i = 1; i < s.size(); ++i) cout << lcp[i] << ' ';
}