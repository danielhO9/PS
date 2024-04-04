#include <bits/stdc++.h>
using namespace std;

vector<int> suffixArray(const string& s) {
	const int MAX_N = s.size();
	vector<int> sfx(MAX_N);
	int m = 26;
	vector<int> cnt(max(MAX_N, m), 0), ord(MAX_N,0), pord(MAX_N,0);

	for (int i = 0; i < MAX_N; ++i) ++cnt[ord[i] = s[i] - 'a'];
	for (int i = 1; i < m; ++i) cnt[i] += cnt[i - 1];
	for (int i = MAX_N - 1; i >= 0; --i) sfx[--cnt[ord[i]]] = i;
	int now = 1, idx = 0;
	while (true) {
		if (idx == MAX_N - 1) break;
		m = idx + 1; idx = 0;
		for (int i = MAX_N - now; i < MAX_N; ++i) pord[idx++] = i;
		for (int i = 0; i < MAX_N; ++i) if (sfx[i] >= now) pord[idx++] = sfx[i] - now;
		for (int i = 0; i < m; ++i) cnt[i] = 0;
		for (int i = 0; i < MAX_N; ++i) ++cnt[ord[pord[i]]];
		for (int i = 1; i < m; ++i) cnt[i] += cnt[i - 1];
		for (int i = MAX_N - 1; i >= 0; --i) sfx[--cnt[ord[pord[i]]]] = pord[i];
		
		pord = vector<int>(ord.begin(), ord.end()); idx = 0;
		ord[sfx[0]] = 0;
		for (int i = 1; i < MAX_N; ++i) {
			if (sfx[i - 1] + now >= MAX_N || sfx[i] + now >= MAX_N || pord[sfx[i - 1]] != pord[sfx[i]] || pord[sfx[i - 1] + now] != pord[sfx[i] + now]) ++idx;
			ord[sfx[i]] = idx;
		}
		now *= 2;
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
	vector<int> sfx = suffixArray(s);
	vector<int> lcp = getLcp(s, sfx);
	for (int i = 0; i < s.size(); ++i) cout << sfx[i] + 1 << ' ';
	cout << '\n';
	cout << "x ";
	for (int i = 1; i < s.size(); ++i) cout << lcp[i] << ' ';
}